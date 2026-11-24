#pragma once
#include "ast/AST.hpp"
#include <string>
#include <vector>
#include <variant>

namespace banglascript {

enum class BinaryOp {
    Add,      // +
    Subtract, // -
    Multiply, // *
    Divide,   // /
    Modulo,   // %
    Equal,    // ==
    NotEqual, // !=
    Less,     // <
    LessEq,   // <=
    Greater,  // >
    GreaterEq,// >=
    LogicalAnd, // &&, ebong
    LogicalOr   // ||, othoba
};

inline std::string binaryOpToString(BinaryOp op) {
    switch (op) {
        case BinaryOp::Add:       return "+";
        case BinaryOp::Subtract:  return "-";
        case BinaryOp::Multiply:  return "*";
        case BinaryOp::Divide:    return "/";
        case BinaryOp::Modulo:    return "%";
        case BinaryOp::Equal:     return "==";
        case BinaryOp::NotEqual:  return "!=";
        case BinaryOp::Less:      return "<";
        case BinaryOp::LessEq:    return "<=";
        case BinaryOp::Greater:   return ">";
        case BinaryOp::GreaterEq: return ">=";
        case BinaryOp::LogicalAnd:return "&&";
        case BinaryOp::LogicalOr: return "||";
    }
    return "?";
}

enum class UnaryOp {
    Negate,    // -
    LogicalNot // !
};

inline std::string unaryOpToString(UnaryOp op) {
    switch (op) {
        case UnaryOp::Negate:     return "-";
        case UnaryOp::LogicalNot: return "!";
    }
    return "?";
}

class ExpressionNode : public ASTNode {
public:
    explicit ExpressionNode(ASTNodeType type, SourceSpan span = SourceSpan())
        : ASTNode(type, std::move(span)), inferredType_(DataType::Unknown) {}

    DataType getInferredType() const { return inferredType_; }
    void setInferredType(DataType t) { inferredType_ = t; }

private:
    DataType inferredType_;
};

using ExprPtr = std::unique_ptr<ExpressionNode>;

class LiteralExpr : public ExpressionNode {
public:
    using LiteralValue = std::variant<int64_t, double, std::string, bool>;

    LiteralExpr(LiteralValue val, DataType type, SourceSpan span = SourceSpan())
        : ExpressionNode(ASTNodeType::LiteralExpr, std::move(span)), value_(std::move(val)) {
        setInferredType(type);
    }

    const LiteralValue& getValue() const { return value_; }

    void accept(ASTVisitor& visitor) override;

private:
    LiteralValue value_;
};

class VariableExpr : public ExpressionNode {
public:
    VariableExpr(std::string name, SourceSpan span = SourceSpan())
        : ExpressionNode(ASTNodeType::VariableExpr, std::move(span)), name_(std::move(name)) {}

    const std::string& getName() const { return name_; }

    void accept(ASTVisitor& visitor) override;

private:
    std::string name_;
};

class BinaryExpr : public ExpressionNode {
public:
    BinaryExpr(BinaryOp op, ExprPtr left, ExprPtr right, SourceSpan span = SourceSpan())
        : ExpressionNode(ASTNodeType::BinaryExpr, std::move(span)),
          op_(op), left_(std::move(left)), right_(std::move(right)) {}

    BinaryOp getOp() const { return op_; }
    ExpressionNode* getLeft() const { return left_.get(); }
    ExpressionNode* getRight() const { return right_.get(); }

    void accept(ASTVisitor& visitor) override;

private:
    BinaryOp op_;
    ExprPtr left_;
    ExprPtr right_;
};

class UnaryExpr : public ExpressionNode {
public:
    UnaryExpr(UnaryOp op, ExprPtr operand, SourceSpan span = SourceSpan())
        : ExpressionNode(ASTNodeType::UnaryExpr, std::move(span)),
          op_(op), operand_(std::move(operand)) {}

    UnaryOp getOp() const { return op_; }
    ExpressionNode* getOperand() const { return operand_.get(); }

    void accept(ASTVisitor& visitor) override;

private:
    UnaryOp op_;
    ExprPtr operand_;
};

class CallExpr : public ExpressionNode {
public:
    CallExpr(std::string callee, std::vector<ExprPtr> args, SourceSpan span = SourceSpan())
        : ExpressionNode(ASTNodeType::CallExpr, std::move(span)),
          callee_(std::move(callee)), arguments_(std::move(args)) {}

    const std::string& getCallee() const { return callee_; }
    const std::vector<ExprPtr>& getArguments() const { return arguments_; }

    void accept(ASTVisitor& visitor) override;

private:
    std::string callee_;
    std::vector<ExprPtr> arguments_;
};

class AssignExpr : public ExpressionNode {
public:
    AssignExpr(std::string target, ExprPtr value, SourceSpan span = SourceSpan())
        : ExpressionNode(ASTNodeType::AssignExpr, std::move(span)),
          target_(std::move(target)), value_(std::move(value)) {}

    const std::string& getTarget() const { return target_; }
    ExpressionNode* getValue() const { return value_.get(); }

    void accept(ASTVisitor& visitor) override;

private:
    std::string target_;
    ExprPtr value_;
};

class InputExpr : public ExpressionNode {
public:
    explicit InputExpr(ExprPtr prompt = nullptr, SourceSpan span = SourceSpan())
        : ExpressionNode(ASTNodeType::InputExpr, std::move(span)), prompt_(std::move(prompt)) {
        setInferredType(DataType::Sonkha);
    }

    ExpressionNode* getPrompt() const { return prompt_.get(); }
    bool hasPrompt() const { return prompt_ != nullptr; }

    void accept(ASTVisitor& visitor) override;

private:
    ExprPtr prompt_;
};

} // namespace banglascript
