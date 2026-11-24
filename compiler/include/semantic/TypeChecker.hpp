#pragma once
#include "ast/ASTVisitor.hpp"
#include "ast/Declarations.hpp"
#include "ast/Expressions.hpp"
#include "ast/Statements.hpp"
#include "semantic/SymbolTable.hpp"
#include "common/Diagnostics.hpp"
#include <string>
#include <vector>

namespace banglascript {

class TypeChecker : public ASTVisitor {
public:
    explicit TypeChecker(DiagnosticsEngine& diagnostics)
        : diagnostics_(diagnostics) {}

    bool check(Program& program);

    const SymbolTable& getSymbolTable() const { return symbolTable_; }
    SymbolTable& getSymbolTable() { return symbolTable_; }

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
    void visit(InputExpr& node) override;

private:
    DiagnosticsEngine& diagnostics_;
    SymbolTable symbolTable_;
    DataType currentFunctionReturnType_{DataType::Shunno};
    bool insideFunction_{false};
    uint32_t loopDepth_{0};

    bool typesCompatible(DataType expected, DataType actual);
    DataType resolveNumericType(DataType left, DataType right);
};

} // namespace banglascript
