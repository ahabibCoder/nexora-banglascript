#include "ir/TACGenerator.hpp"
#include <iomanip>

namespace banglascript {

std::string TACGenerator::newTemp() {
    return "t" + std::to_string(tempCounter_++);
}

std::string TACGenerator::newLabel() {
    return "L" + std::to_string(labelCounter_++);
}

void TACGenerator::emit(Opcode op, std::string a1, std::string a2, std::string res, DataType t) {
    instructions_.emplace_back(op, std::move(a1), std::move(a2), std::move(res), t);
}

TACProgram TACGenerator::generate(Program& program) {
    instructions_.clear();
    tempCounter_ = 0;
    labelCounter_ = 0;
    lastResult_.clear();
    while (!breakStack_.empty()) breakStack_.pop();
    while (!continueStack_.empty()) continueStack_.pop();

    program.accept(*this);
    return instructions_;
}

void TACGenerator::visit(Program& node) {
    // 1. Emit top-level main program statements first
    for (const auto& stmt : node.getStatements()) {
        stmt->accept(*this);
    }
    emit(Opcode::Halt);

    // 2. Emit functions
    for (const auto& fn : node.getFunctions()) {
        fn->accept(*this);
    }
}

void TACGenerator::visit(FunctionDecl& node) {
    emit(Opcode::FuncBegin, "", "", node.getName());

    // Parameters are popped / bound in order by caller/callee convention
    for (const auto& p : node.getParameters()) {
        emit(Opcode::Assign, "__param__" + p.name, "", p.name, p.type);
    }

    if (node.getBody()) {
        for (const auto& stmt : node.getBody()->getStatements()) {
            stmt->accept(*this);
        }
    }

    // Default implicit return if void
    if (node.getReturnType() == DataType::Shunno) {
        emit(Opcode::Return);
    }
    emit(Opcode::FuncEnd, "", "", node.getName());
}

void TACGenerator::visit(VarDeclStmt& node) {
    if (node.hasInitializer()) {
        node.getInitializer()->accept(*this);
        emit(Opcode::Assign, lastResult_, "", node.getName(), node.getVarType());
    }
}

void TACGenerator::visit(BlockStmt& node) {
    for (const auto& stmt : node.getStatements()) {
        stmt->accept(*this);
    }
}

void TACGenerator::visit(ExprStmt& node) {
    if (node.getExpression()) {
        node.getExpression()->accept(*this);
    }
}

void TACGenerator::visit(IfStmt& node) {
    node.getCondition()->accept(*this);
    std::string condRes = lastResult_;

    std::string elseLabel = newLabel();
    std::string endLabel = newLabel();

    if (node.hasElseBranch()) {
        emit(Opcode::JumpIfFalse, condRes, "", elseLabel);
        node.getThenBranch()->accept(*this);
        emit(Opcode::Jump, "", "", endLabel);

        emit(Opcode::Label, "", "", elseLabel);
        node.getElseBranch()->accept(*this);
        emit(Opcode::Label, "", "", endLabel);
    } else {
        emit(Opcode::JumpIfFalse, condRes, "", endLabel);
        node.getThenBranch()->accept(*this);
        emit(Opcode::Label, "", "", endLabel);
    }
}

void TACGenerator::visit(WhileStmt& node) {
    std::string startLabel = newLabel();
    std::string endLabel = newLabel();

    breakStack_.push(endLabel);
    continueStack_.push(startLabel);

    emit(Opcode::Label, "", "", startLabel);
    node.getCondition()->accept(*this);
    emit(Opcode::JumpIfFalse, lastResult_, "", endLabel);

    if (node.getBody()) {
        node.getBody()->accept(*this);
    }

    emit(Opcode::Jump, "", "", startLabel);
    emit(Opcode::Label, "", "", endLabel);

    breakStack_.pop();
    continueStack_.pop();
}

void TACGenerator::visit(BreakStmt&) {
    if (!breakStack_.empty()) {
        emit(Opcode::Jump, "", "", breakStack_.top());
    }
}

void TACGenerator::visit(ContinueStmt&) {
    if (!continueStack_.empty()) {
        emit(Opcode::Jump, "", "", continueStack_.top());
    }
}

void TACGenerator::visit(ReturnStmt& node) {
    if (node.hasValue()) {
        node.getValue()->accept(*this);
        emit(Opcode::Return, lastResult_);
    } else {
        emit(Opcode::Return);
    }
}

void TACGenerator::visit(PrintStmt& node) {
    if (node.getExpression()) {
        node.getExpression()->accept(*this);
        emit(Opcode::Print, lastResult_, "", "", node.getExpression()->getInferredType());
    }
}

void TACGenerator::visit(InputStmt& node) {
    emit(Opcode::Input, "", "", node.getTarget());
}

void TACGenerator::visit(LiteralExpr& node) {
    std::string valStr;
    std::visit([&valStr](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, bool>) {
            valStr = arg ? "true" : "false";
        } else if constexpr (std::is_same_v<T, std::string>) {
            valStr = "\"" + arg + "\"";
        } else if constexpr (std::is_same_v<T, double>) {
            std::ostringstream ss;
            ss << arg;
            valStr = ss.str();
            if (valStr.find('.') == std::string::npos) valStr += ".0";
        } else {
            valStr = std::to_string(arg);
        }
    }, node.getValue());

    std::string temp = newTemp();
    emit(Opcode::Assign, valStr, "", temp, node.getInferredType());
    lastResult_ = temp;
}

void TACGenerator::visit(VariableExpr& node) {
    lastResult_ = node.getName();
}

void TACGenerator::visit(BinaryExpr& node) {
    node.getLeft()->accept(*this);
    std::string leftRes = lastResult_;

    node.getRight()->accept(*this);
    std::string rightRes = lastResult_;

    std::string temp = newTemp();
    Opcode op = Opcode::Add;
    switch (node.getOp()) {
        case BinaryOp::Add:        op = Opcode::Add; break;
        case BinaryOp::Subtract:   op = Opcode::Sub; break;
        case BinaryOp::Multiply:   op = Opcode::Mul; break;
        case BinaryOp::Divide:     op = Opcode::Div; break;
        case BinaryOp::Modulo:     op = Opcode::Mod; break;
        case BinaryOp::Equal:      op = Opcode::Equal; break;
        case BinaryOp::NotEqual:   op = Opcode::NotEqual; break;
        case BinaryOp::Less:       op = Opcode::Less; break;
        case BinaryOp::LessEq:     op = Opcode::LessEq; break;
        case BinaryOp::Greater:    op = Opcode::Greater; break;
        case BinaryOp::GreaterEq:  op = Opcode::GreaterEq; break;
        case BinaryOp::LogicalAnd: op = Opcode::And; break;
        case BinaryOp::LogicalOr:  op = Opcode::Or; break;
    }

    emit(op, leftRes, rightRes, temp, node.getInferredType());
    lastResult_ = temp;
}

void TACGenerator::visit(UnaryExpr& node) {
    node.getOperand()->accept(*this);
    std::string opRes = lastResult_;

    std::string temp = newTemp();
    Opcode op = (node.getOp() == UnaryOp::Negate) ? Opcode::Neg : Opcode::Not;
    emit(op, opRes, "", temp, node.getInferredType());
    lastResult_ = temp;
}

void TACGenerator::visit(CallExpr& node) {
    std::vector<std::string> argResults;
    for (const auto& arg : node.getArguments()) {
        arg->accept(*this);
        argResults.push_back(lastResult_);
    }

    for (const auto& argRes : argResults) {
        emit(Opcode::Param, argRes);
    }

    std::string temp = newTemp();
    emit(Opcode::Call, node.getCallee(), std::to_string(argResults.size()), temp, node.getInferredType());
    lastResult_ = temp;
}

void TACGenerator::visit(AssignExpr& node) {
    node.getValue()->accept(*this);
    emit(Opcode::Assign, lastResult_, "", node.getTarget(), node.getInferredType());
    lastResult_ = node.getTarget();
}

} // namespace banglascript
