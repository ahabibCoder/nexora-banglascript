#pragma once
#include "ast/AST.hpp"
#include "ast/Expressions.hpp"
#include <string>
#include <vector>

namespace banglascript {

class StatementNode : public ASTNode {
public:
    explicit StatementNode(ASTNodeType type, SourceSpan span = SourceSpan())
        : ASTNode(type, std::move(span)) {}
};

using StmtPtr = std::unique_ptr<StatementNode>;

class ExprStmt : public StatementNode {
public:
    explicit ExprStmt(ExprPtr expr, SourceSpan span = SourceSpan())
        : StatementNode(ASTNodeType::ExprStmt, std::move(span)), expression_(std::move(expr)) {}

    ExpressionNode* getExpression() const { return expression_.get(); }

    void accept(ASTVisitor& visitor) override;

private:
    ExprPtr expression_;
};

class BlockStmt : public StatementNode {
public:
    explicit BlockStmt(std::vector<StmtPtr> stmts, SourceSpan span = SourceSpan())
        : StatementNode(ASTNodeType::BlockStmt, std::move(span)), statements_(std::move(stmts)) {}

    const std::vector<StmtPtr>& getStatements() const { return statements_; }

    void accept(ASTVisitor& visitor) override;

private:
    std::vector<StmtPtr> statements_;
};

class VarDeclStmt : public StatementNode {
public:
    VarDeclStmt(DataType type, std::string name, ExprPtr init = nullptr, SourceSpan span = SourceSpan())
        : StatementNode(ASTNodeType::VarDecl, std::move(span)),
          varType_(type), name_(std::move(name)), initializer_(std::move(init)) {}

    DataType getVarType() const { return varType_; }
    const std::string& getName() const { return name_; }
    ExpressionNode* getInitializer() const { return initializer_.get(); }
    bool hasInitializer() const { return initializer_ != nullptr; }

    void accept(ASTVisitor& visitor) override;

private:
    DataType varType_;
    std::string name_;
    ExprPtr initializer_;
};

class IfStmt : public StatementNode {
public:
    IfStmt(ExprPtr condition, StmtPtr thenBranch, StmtPtr elseBranch = nullptr, SourceSpan span = SourceSpan())
        : StatementNode(ASTNodeType::IfStmt, std::move(span)),
          condition_(std::move(condition)), thenBranch_(std::move(thenBranch)), elseBranch_(std::move(elseBranch)) {}

    ExpressionNode* getCondition() const { return condition_.get(); }
    StatementNode* getThenBranch() const { return thenBranch_.get(); }
    StatementNode* getElseBranch() const { return elseBranch_.get(); }
    bool hasElseBranch() const { return elseBranch_ != nullptr; }

    void accept(ASTVisitor& visitor) override;

private:
    ExprPtr condition_;
    StmtPtr thenBranch_;
    StmtPtr elseBranch_;
};

class WhileStmt : public StatementNode {
public:
    WhileStmt(ExprPtr condition, StmtPtr body, SourceSpan span = SourceSpan())
        : StatementNode(ASTNodeType::WhileStmt, std::move(span)),
          condition_(std::move(condition)), body_(std::move(body)) {}

    ExpressionNode* getCondition() const { return condition_.get(); }
    StatementNode* getBody() const { return body_.get(); }

    void accept(ASTVisitor& visitor) override;

private:
    ExprPtr condition_;
    StmtPtr body_;
};

class BreakStmt : public StatementNode {
public:
    explicit BreakStmt(SourceSpan span = SourceSpan())
        : StatementNode(ASTNodeType::BreakStmt, std::move(span)) {}

    void accept(ASTVisitor& visitor) override;
};

class ContinueStmt : public StatementNode {
public:
    explicit ContinueStmt(SourceSpan span = SourceSpan())
        : StatementNode(ASTNodeType::ContinueStmt, std::move(span)) {}

    void accept(ASTVisitor& visitor) override;
};

class ReturnStmt : public StatementNode {
public:
    explicit ReturnStmt(ExprPtr value = nullptr, SourceSpan span = SourceSpan())
        : StatementNode(ASTNodeType::ReturnStmt, std::move(span)), value_(std::move(value)) {}

    ExpressionNode* getValue() const { return value_.get(); }
    bool hasValue() const { return value_ != nullptr; }

    void accept(ASTVisitor& visitor) override;

private:
    ExprPtr value_;
};

class PrintStmt : public StatementNode {
public:
    explicit PrintStmt(ExprPtr expr, SourceSpan span = SourceSpan())
        : StatementNode(ASTNodeType::PrintStmt, std::move(span)), expression_(std::move(expr)) {}

    ExpressionNode* getExpression() const { return expression_.get(); }

    void accept(ASTVisitor& visitor) override;

private:
    ExprPtr expression_;
};

class InputStmt : public StatementNode {
public:
    explicit InputStmt(std::string target, SourceSpan span = SourceSpan())
        : StatementNode(ASTNodeType::InputStmt, std::move(span)), target_(std::move(target)) {}

    const std::string& getTarget() const { return target_; }

    void accept(ASTVisitor& visitor) override;

private:
    std::string target_;
};

} // namespace banglascript
