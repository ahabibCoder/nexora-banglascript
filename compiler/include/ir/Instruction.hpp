#pragma once
#include "common/Types.hpp"
#include <string>
#include <vector>
#include <sstream>

namespace banglascript {

enum class Opcode {
    // Arithmetic
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Neg,

    // Relational
    Equal,
    NotEqual,
    Less,
    LessEq,
    Greater,
    GreaterEq,

    // Logical
    Not,
    And,
    Or,

    // Data movement
    Assign,

    // Control Flow
    Label,
    Jump,
    JumpIfTrue,
    JumpIfFalse,

    // Functions
    Param,
    Call,
    Return,
    FuncBegin,
    FuncEnd,

    // I/O
    Print,
    Input,

    // Halt
    Halt
};

inline std::string opcodeToString(Opcode op) {
    switch (op) {
        case Opcode::Add:         return "ADD";
        case Opcode::Sub:         return "SUB";
        case Opcode::Mul:         return "MUL";
        case Opcode::Div:         return "DIV";
        case Opcode::Mod:         return "MOD";
        case Opcode::Neg:         return "NEG";
        case Opcode::Equal:       return "EQ";
        case Opcode::NotEqual:    return "NEQ";
        case Opcode::Less:        return "LT";
        case Opcode::LessEq:      return "LE";
        case Opcode::Greater:     return "GT";
        case Opcode::GreaterEq:   return "GE";
        case Opcode::Not:         return "NOT";
        case Opcode::And:         return "AND";
        case Opcode::Or:          return "OR";
        case Opcode::Assign:      return "ASSIGN";
        case Opcode::Label:       return "LABEL";
        case Opcode::Jump:        return "JUMP";
        case Opcode::JumpIfTrue:  return "JUMP_IF_TRUE";
        case Opcode::JumpIfFalse: return "JUMP_IF_FALSE";
        case Opcode::Param:       return "PARAM";
        case Opcode::Call:        return "CALL";
        case Opcode::Return:      return "RETURN";
        case Opcode::FuncBegin:   return "FUNC_BEGIN";
        case Opcode::FuncEnd:     return "FUNC_END";
        case Opcode::Print:       return "PRINT";
        case Opcode::Input:       return "INPUT";
        case Opcode::Halt:        return "HALT";
    }
    return "UNKNOWN";
}

struct TACInstruction {
    Opcode op{Opcode::Halt};
    std::string arg1;
    std::string arg2;
    std::string result;
    DataType type{DataType::Unknown};

    TACInstruction() = default;
    TACInstruction(Opcode o, std::string a1 = "", std::string a2 = "", std::string res = "", DataType t = DataType::Unknown)
        : op(o), arg1(std::move(a1)), arg2(std::move(a2)), result(std::move(res)), type(t) {}

    std::string toString() const {
        std::ostringstream ss;
        switch (op) {
            case Opcode::Label:
                ss << result << ":";
                break;
            case Opcode::Assign:
                ss << "  " << result << " = " << arg1;
                break;
            case Opcode::Add:
            case Opcode::Sub:
            case Opcode::Mul:
            case Opcode::Div:
            case Opcode::Mod:
                ss << "  " << result << " = " << arg1 << " "
                   << (op == Opcode::Add ? "+" : op == Opcode::Sub ? "-" : op == Opcode::Mul ? "*" : op == Opcode::Div ? "/" : "%")
                   << " " << arg2;
                break;
            case Opcode::Equal:
            case Opcode::NotEqual:
            case Opcode::Less:
            case Opcode::LessEq:
            case Opcode::Greater:
            case Opcode::GreaterEq:
                ss << "  " << result << " = " << arg1 << " "
                   << (op == Opcode::Equal ? "==" : op == Opcode::NotEqual ? "!=" : op == Opcode::Less ? "<" : op == Opcode::LessEq ? "<=" : op == Opcode::Greater ? ">" : ">=")
                   << " " << arg2;
                break;
            case Opcode::Neg:
                ss << "  " << result << " = -" << arg1;
                break;
            case Opcode::Not:
                ss << "  " << result << " = !" << arg1;
                break;
            case Opcode::Jump:
                ss << "  goto " << result;
                break;
            case Opcode::JumpIfTrue:
                ss << "  if " << arg1 << " goto " << result;
                break;
            case Opcode::JumpIfFalse:
                ss << "  if_false " << arg1 << " goto " << result;
                break;
            case Opcode::Param:
                ss << "  param " << arg1;
                break;
            case Opcode::Call:
                if (!result.empty()) {
                    ss << "  " << result << " = call " << arg1 << ", " << arg2;
                } else {
                    ss << "  call " << arg1 << ", " << arg2;
                }
                break;
            case Opcode::Return:
                if (!arg1.empty()) {
                    ss << "  return " << arg1;
                } else {
                    ss << "  return";
                }
                break;
            case Opcode::FuncBegin:
                ss << "\nfunction " << result << ":";
                break;
            case Opcode::FuncEnd:
                ss << "end function " << result << "\n";
                break;
            case Opcode::Print:
                ss << "  print " << arg1;
                break;
            case Opcode::Input:
                ss << "  input " << result;
                break;
            case Opcode::Halt:
                ss << "  halt";
                break;
            default:
                ss << "  " << opcodeToString(op) << " " << arg1 << ", " << arg2 << " -> " << result;
                break;
        }
        return ss.str();
    }
};

using TACProgram = std::vector<TACInstruction>;

} // namespace banglascript
