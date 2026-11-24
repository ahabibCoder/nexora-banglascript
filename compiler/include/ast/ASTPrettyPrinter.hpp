#pragma once
#include "ast/ASTVisitor.hpp"
#include "ast/AST.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace banglascript {

class ASTPrettyPrinter : public ASTVisitor {
public:
    explicit ASTPrettyPrinter(std::ostream& out = std::cout) : out_(out) {}

    void print(ASTNode& root);

    void visit(Program& node) override;
    void visit(FunctionDecl& node) override;
    void visit(VarDeclStmt& node) override;
    void visit(BlockStmt& node) override;
    void visit(ExprStmt& node) override;
    void visit(IfStmt& node) override;
    void visit(WhileStmt& node) override;
    void visit(BreakStmt& node) override;
    void visit(ContinueStmt& node) override;
    void visit(ReturnStmt& node) override;
    void visit(PrintStmt& node) override;
    void visit(InputStmt& node) override;
    void visit(LiteralExpr& node) override;
    void visit(VariableExpr& node) override;
    void visit(BinaryExpr& node) override;
    void visit(UnaryExpr& node) override;
    void visit(CallExpr& node) override;
    void visit(AssignExpr& node) override;

private:
    std::ostream& out_;
    std::string indent_;

    void printIndent(bool isLast);
    void pushIndent(bool isLast);
    void popIndent();
};

} // namespace banglascript
