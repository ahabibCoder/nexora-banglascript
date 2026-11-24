#include "VirtualMachine.hpp"
#include <cctype>

namespace banglascript {

RuntimeValue VirtualMachine::parseLiteral(const std::string& token) {
    if (token.empty()) return RuntimeValue();

    // String literal enclosed in quotes
    if (token.length() >= 2 && token.front() == '"' && token.back() == '"') {
        return RuntimeValue(token.substr(1, token.length() - 2));
    }

    if (token == "true") return RuntimeValue(true);
    if (token == "false") return RuntimeValue(false);

    // Number literal
    bool hasDot = (token.find('.') != std::string::npos);
    bool isNumeric = true;
    size_t start = (token[0] == '-' || token[0] == '+') ? 1 : 0;
    if (start == token.length()) isNumeric = false;

    for (size_t i = start; i < token.length(); ++i) {
        if (!isdigit(static_cast<unsigned char>(token[i])) && token[i] != '.') {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric) {
        try {
            if (hasDot) {
                return RuntimeValue(std::stod(token));
            } else {
                return RuntimeValue(std::stoll(token));
            }
        } catch (...) {
            // fallback
        }
    }

    return RuntimeValue();
}

RuntimeValue VirtualMachine::resolveValue(const std::string& token) {
    if (token.empty()) return RuntimeValue();

    // Check if it's a literal directly
    if ((token.length() >= 2 && token.front() == '"' && token.back() == '"') ||
        token == "true" || token == "false" ||
        isdigit(static_cast<unsigned char>(token[0])) ||
        ((token[0] == '-' || token[0] == '+') && token.length() > 1 && isdigit(static_cast<unsigned char>(token[1])))) {
        return parseLiteral(token);
    }

    // Look in current function call frame first
    if (!callStack_.empty()) {
        auto& locals = callStack_.top().locals;
        auto it = locals.find(token);
        if (it != locals.end()) {
            return it->second;
        }
    }

    // Look in globals
    auto it = globals_.find(token);
    if (it != globals_.end()) {
        return it->second;
    }

    // Default uninitialized
    return RuntimeValue(0);
}

void VirtualMachine::assignValue(const std::string& varName, const RuntimeValue& val) {
    if (varName.empty()) return;

    if (!callStack_.empty()) {
        // If inside function and already in globals (and not in locals), update global, else local
        auto& locals = callStack_.top().locals;
        if (locals.find(varName) != locals.end() || globals_.find(varName) == globals_.end()) {
            locals[varName] = val;
            return;
        }
    }

    globals_[varName] = val;
}

int VirtualMachine::execute(const TACProgram& program) {
    globals_.clear();
    while (!callStack_.empty()) callStack_.pop();
    paramQueue_.clear();
    labelIndices_.clear();
    functionIndices_.clear();

    // Pre-scan labels and function entry points
    for (size_t i = 0; i < program.size(); ++i) {
        const auto& inst = program[i];
        if (inst.op == Opcode::Label) {
            labelIndices_[inst.result] = i;
        } else if (inst.op == Opcode::FuncBegin) {
            functionIndices_[inst.result] = i;
        }
    }

    size_t pc = 0;
    size_t instructionCount = 0;

    try {
        while (pc < program.size()) {
            if (++instructionCount > maxInstructions_) {
                err_ << "\033[1;31mRuntime Error: Maximum instruction limit ("
                     << maxInstructions_ << ") exceeded. Possible infinite loop detected.\033[0m\n";
                return 1;
            }

            const auto& inst = program[pc];

            switch (inst.op) {
                case Opcode::Halt:
                    return 0;

                case Opcode::Label:
                case Opcode::FuncBegin:
                    pc++;
                    break;

                case Opcode::FuncEnd: {
                    // Function ended without explicit return
                    if (!callStack_.empty()) {
                        size_t returnPC = callStack_.top().returnPC;
                        callStack_.pop();
                        pc = returnPC;
                    } else {
                        pc++;
                    }
                    break;
                }

                case Opcode::Assign: {
                    if (inst.arg1.rfind("__param__", 0) == 0) {
                        // Parameter binding from queue
                        std::string paramName = inst.arg1.substr(9);
                        if (!paramQueue_.empty()) {
                            RuntimeValue argVal = paramQueue_.front();
                            paramQueue_.erase(paramQueue_.begin());
                            assignValue(inst.result, argVal);
                        }
                    } else {
                        RuntimeValue val = resolveValue(inst.arg1);
                        assignValue(inst.result, val);
                    }
                    pc++;
                    break;
                }

                case Opcode::Add: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, v1 + v2);
                    pc++;
                    break;
                }

                case Opcode::Sub: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, v1 - v2);
                    pc++;
                    break;
                }

                case Opcode::Mul: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, v1 * v2);
                    pc++;
                    break;
                }

                case Opcode::Div: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, v1 / v2);
                    pc++;
                    break;
                }

                case Opcode::Mod: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, v1 % v2);
                    pc++;
                    break;
                }

                case Opcode::Neg: {
                    RuntimeValue v = resolveValue(inst.arg1);
                    assignValue(inst.result, -v);
                    pc++;
                    break;
                }

                case Opcode::Not: {
                    RuntimeValue v = resolveValue(inst.arg1);
                    assignValue(inst.result, !v);
                    pc++;
                    break;
                }

                case Opcode::Equal: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, RuntimeValue(v1 == v2));
                    pc++;
                    break;
                }

                case Opcode::NotEqual: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, RuntimeValue(v1 != v2));
                    pc++;
                    break;
                }

                case Opcode::Less: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, RuntimeValue(v1 < v2));
                    pc++;
                    break;
                }

                case Opcode::LessEq: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, RuntimeValue(v1 <= v2));
                    pc++;
                    break;
                }

                case Opcode::Greater: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, RuntimeValue(v1 > v2));
                    pc++;
                    break;
                }

                case Opcode::GreaterEq: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, RuntimeValue(v1 >= v2));
                    pc++;
                    break;
                }

                case Opcode::And: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, RuntimeValue(v1.asBool() && v2.asBool()));
                    pc++;
                    break;
                }

                case Opcode::Or: {
                    RuntimeValue v1 = resolveValue(inst.arg1);
                    RuntimeValue v2 = resolveValue(inst.arg2);
                    assignValue(inst.result, RuntimeValue(v1.asBool() || v2.asBool()));
                    pc++;
                    break;
                }

                case Opcode::Jump: {
                    auto it = labelIndices_.find(inst.result);
                    if (it == labelIndices_.end()) {
                        err_ << "Runtime Error: Jump to undefined label '" << inst.result << "'\n";
                        return 1;
                    }
                    pc = it->second;
                    break;
                }

                case Opcode::JumpIfTrue: {
                    RuntimeValue cond = resolveValue(inst.arg1);
                    if (cond.asBool()) {
                        auto it = labelIndices_.find(inst.result);
                        if (it == labelIndices_.end()) {
                            err_ << "Runtime Error: Jump to undefined label '" << inst.result << "'\n";
                            return 1;
                        }
                        pc = it->second;
                    } else {
                        pc++;
                    }
                    break;
                }

                case Opcode::JumpIfFalse: {
                    RuntimeValue cond = resolveValue(inst.arg1);
                    if (!cond.asBool()) {
                        auto it = labelIndices_.find(inst.result);
                        if (it == labelIndices_.end()) {
                            err_ << "Runtime Error: Jump to undefined label '" << inst.result << "'\n";
                            return 1;
                        }
                        pc = it->second;
                    } else {
                        pc++;
                    }
                    break;
                }

                case Opcode::Param: {
                    paramQueue_.push_back(resolveValue(inst.arg1));
                    pc++;
                    break;
                }

                case Opcode::Call: {
                    if (callStack_.size() >= maxRecursionDepth_) {
                        err_ << "\033[1;31mRuntime Error: Stack Overflow! Recursion depth ("
                             << maxRecursionDepth_ << ") exceeded in function '" << inst.arg1 << "'.\033[0m\n";
                        return 1;
                    }

                    auto it = functionIndices_.find(inst.arg1);
                    if (it == functionIndices_.end()) {
                        err_ << "Runtime Error: Call to undefined function '" << inst.arg1 << "'\n";
                        return 1;
                    }

                    CallFrame frame;
                    frame.functionName = inst.arg1;
                    frame.returnPC = pc + 1;
                    frame.returnTarget = inst.result;
                    callStack_.push(std::move(frame));

                    pc = it->second + 1; // Step past FuncBegin
                    break;
                }

                case Opcode::Return: {
                    RuntimeValue retVal;
                    if (!inst.arg1.empty()) {
                        retVal = resolveValue(inst.arg1);
                    }

                    if (!callStack_.empty()) {
                        CallFrame frame = std::move(callStack_.top());
                        callStack_.pop();

                        if (!frame.returnTarget.empty()) {
                            assignValue(frame.returnTarget, retVal);
                        }
                        pc = frame.returnPC;
                    } else {
                        // Top level return -> exit
                        return 0;
                    }
                    break;
                }

                case Opcode::Print: {
                    RuntimeValue val = resolveValue(inst.arg1);
                    out_ << val.toString() << "\n";
                    pc++;
                    break;
                }

                case Opcode::Input: {
                    std::string line;
                    if (std::getline(in_, line)) {
                        assignValue(inst.result, parseLiteral(line));
                    }
                    pc++;
                    break;
                }
            }
        }
    } catch (const std::exception& e) {
        err_ << "\033[1;31mRuntime Exception: " << e.what() << "\033[0m\n";
        return 1;
    }

    return 0;
}

} // namespace banglascript
