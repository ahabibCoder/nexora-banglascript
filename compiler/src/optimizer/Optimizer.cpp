#include "optimizer/Optimizer.hpp"
#include <unordered_set>
#include <sstream>

namespace banglascript {

bool TACOptimizer::isIntegerLiteral(const std::string& str, int64_t& outVal) {
    if (str.empty()) return false;
    size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
    if (start == str.length()) return false;
    for (size_t i = start; i < str.length(); ++i) {
        if (!isdigit(static_cast<unsigned char>(str[i]))) return false;
    }
    try {
        outVal = std::stoll(str);
        return true;
    } catch (...) {
        return false;
    }
}

bool TACOptimizer::isDoubleLiteral(const std::string& str, double& outVal) {
    if (str.empty() || str.find('.') == std::string::npos) return false;
    try {
        size_t idx = 0;
        outVal = std::stod(str, &idx);
        return idx == str.length();
    } catch (...) {
        return false;
    }
}

bool TACOptimizer::isBooleanLiteral(const std::string& str, bool& outVal) {
    if (str == "true") { outVal = true; return true; }
    if (str == "false") { outVal = false; return true; }
    return false;
}

TACProgram TACOptimizer::optimize(const TACProgram& original) {
    TACProgram program = original;

    bool changed = true;
    int iteration = 0;
    while (changed && iteration < 10) {
        changed = false;
        changed |= constantFoldingPass(program);
        changed |= constantPropagationPass(program);
        changed |= deadCodeEliminationPass(program);
        iteration++;
    }

    return program;
}

bool TACOptimizer::constantFoldingPass(TACProgram& program) {
    bool modified = false;

    for (auto& inst : program) {
        int64_t i1 = 0, i2 = 0;
        double d1 = 0.0, d2 = 0.0;

        if (inst.op == Opcode::Add || inst.op == Opcode::Sub ||
            inst.op == Opcode::Mul || inst.op == Opcode::Div || inst.op == Opcode::Mod) {
            
            if (isIntegerLiteral(inst.arg1, i1) && isIntegerLiteral(inst.arg2, i2)) {
                int64_t res = 0;
                bool ok = true;
                if (inst.op == Opcode::Add) res = i1 + i2;
                else if (inst.op == Opcode::Sub) res = i1 - i2;
                else if (inst.op == Opcode::Mul) res = i1 * i2;
                else if (inst.op == Opcode::Div) { if (i2 != 0) res = i1 / i2; else ok = false; }
                else if (inst.op == Opcode::Mod) { if (i2 != 0) res = i1 % i2; else ok = false; }

                if (ok) {
                    inst.op = Opcode::Assign;
                    inst.arg1 = std::to_string(res);
                    inst.arg2 = "";
                    modified = true;
                }
            } else if ((isDoubleLiteral(inst.arg1, d1) || isIntegerLiteral(inst.arg1, i1)) &&
                       (isDoubleLiteral(inst.arg2, d2) || isIntegerLiteral(inst.arg2, i2))) {
                double val1 = isDoubleLiteral(inst.arg1, d1) ? d1 : static_cast<double>(i1);
                double val2 = isDoubleLiteral(inst.arg2, d2) ? d2 : static_cast<double>(i2);
                double res = 0.0;
                bool ok = true;

                if (inst.op == Opcode::Add) res = val1 + val2;
                else if (inst.op == Opcode::Sub) res = val1 - val2;
                else if (inst.op == Opcode::Mul) res = val1 * val2;
                else if (inst.op == Opcode::Div) { if (val2 != 0.0) res = val1 / val2; else ok = false; }
                else ok = false;

                if (ok) {
                    inst.op = Opcode::Assign;
                    std::ostringstream ss;
                    ss << res;
                    std::string str = ss.str();
                    if (str.find('.') == std::string::npos) str += ".0";
                    inst.arg1 = str;
                    inst.arg2 = "";
                    modified = true;
                }
            }
        }
    }

    return modified;
}

bool TACOptimizer::constantPropagationPass(TACProgram& program) {
    bool modified = false;
    std::unordered_map<std::string, std::string> knownConstants;

    for (auto& inst : program) {
        if (inst.op == Opcode::Label || inst.op == Opcode::FuncBegin ||
            inst.op == Opcode::Jump || inst.op == Opcode::JumpIfTrue || inst.op == Opcode::JumpIfFalse) {
            // Invalidate across control flow jumps for conservative safety
            knownConstants.clear();
            continue;
        }

        // Propagate in arg1
        if (!inst.arg1.empty() && knownConstants.find(inst.arg1) != knownConstants.end()) {
            inst.arg1 = knownConstants[inst.arg1];
            modified = true;
        }

        // Propagate in arg2
        if (!inst.arg2.empty() && knownConstants.find(inst.arg2) != knownConstants.end()) {
            inst.arg2 = knownConstants[inst.arg2];
            modified = true;
        }

        // If assignment of constant to temporary (t0, t1, ...)
        if (inst.op == Opcode::Assign && !inst.result.empty() && inst.result[0] == 't') {
            int64_t ival; double dval; bool bval;
            if (isIntegerLiteral(inst.arg1, ival) || isDoubleLiteral(inst.arg1, dval) ||
                isBooleanLiteral(inst.arg1, bval) ||
                (inst.arg1.length() >= 2 && inst.arg1.front() == '"' && inst.arg1.back() == '"')) {
                knownConstants[inst.result] = inst.arg1;
            }
        } else if (!inst.result.empty()) {
            knownConstants.erase(inst.result);
        }
    }

    return modified;
}

bool TACOptimizer::deadCodeEliminationPass(TACProgram& program) {
    bool modified = false;
    TACProgram newProgram;
    bool unreachable = false;

    for (const auto& inst : program) {
        if (inst.op == Opcode::Label || inst.op == Opcode::FuncBegin || inst.op == Opcode::FuncEnd) {
            unreachable = false;
        }

        if (unreachable) {
            modified = true;
            continue; // Skip unreachable instructions after return or unconditional jump
        }

        newProgram.push_back(inst);

        if (inst.op == Opcode::Jump || inst.op == Opcode::Return || inst.op == Opcode::Halt) {
            unreachable = true;
        }
    }

    program = std::move(newProgram);
    return modified;
}

} // namespace banglascript
