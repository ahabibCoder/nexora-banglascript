#pragma once
#include "common/Position.hpp"
#include "common/Types.hpp"
#include <memory>
#include <string>
#include <vector>

namespace banglascript {

class ASTVisitor;

enum class ASTNodeType {
    Program,
    // Declarations
    VarDecl,
    FunctionDecl,
    // Statements
    BlockStmt,
    ExprStmt,
    IfStmt,
    WhileStmt,
    BreakStmt,
    ContinueStmt,
    ReturnStmt,
    PrintStmt,
    InputStmt,
    // Expressions
    LiteralExpr,
    VariableExpr,
    BinaryExpr,
    UnaryExpr,
    CallExpr,
    AssignExpr,
    InputExpr
};

class ASTNode {
public:
    explicit ASTNode(ASTNodeType type, SourceSpan span = SourceSpan())
        : nodeType_(type), span_(std::move(span)) {}
    virtual ~ASTNode() = default;

    ASTNodeType getNodeType() const { return nodeType_; }
    const SourceSpan& getSpan() const { return span_; }
    void setSpan(SourceSpan sp) { span_ = std::move(sp); }

    virtual void accept(ASTVisitor& visitor) = 0;

private:
    ASTNodeType nodeType_;
    SourceSpan span_;
};

using ASTNodePtr = std::unique_ptr<ASTNode>;

} // namespace banglascript
