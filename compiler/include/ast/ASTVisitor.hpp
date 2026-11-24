#pragma once
#include <iostream>
#include <string>

namespace banglascript {

class Program;
class FunctionDecl;
class VarDeclStmt;
class BlockStmt;
class ExprStmt;
class IfStmt;
class WhileStmt;
class BreakStmt;
class ContinueStmt;
class ReturnStmt;
class PrintStmt;
class InputStmt;
class LiteralExpr;
class VariableExpr;
class BinaryExpr;
class UnaryExpr;
class CallExpr;
class AssignExpr;
class InputExpr;

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual void visit(Program& node) = 0;
    virtual void visit(FunctionDecl& node) = 0;
    virtual void visit(VarDeclStmt& node) = 0;
    virtual void visit(BlockStmt& node) = 0;
    virtual void visit(ExprStmt& node) = 0;
    virtual void visit(IfStmt& node) = 0;
    virtual void visit(WhileStmt& node) = 0;
    virtual void visit(BreakStmt& node) = 0;
    virtual void visit(ContinueStmt& node) = 0;
    virtual void visit(ReturnStmt& node) = 0;
    virtual void visit(PrintStmt& node) = 0;
    virtual void visit(InputStmt& node) = 0;
    virtual void visit(LiteralExpr& node) = 0;
    virtual void visit(VariableExpr& node) = 0;
    virtual void visit(BinaryExpr& node) = 0;
    virtual void visit(UnaryExpr& node) = 0;
    virtual void visit(CallExpr& node) = 0;
    virtual void visit(AssignExpr& node) = 0;
    virtual void visit(InputExpr& node) = 0;
};

} // namespace banglascript
