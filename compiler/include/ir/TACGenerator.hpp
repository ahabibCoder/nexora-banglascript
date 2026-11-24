#pragma once
#include "ast/ASTVisitor.hpp"
#include "ast/Declarations.hpp"
#include "ast/Expressions.hpp"
#include "ast/Statements.hpp"
#include "ir/Instruction.hpp"
#include <string>
#include <vector>
#include <stack>

namespace banglascript {

class TACGenerator : public ASTVisitor {
public:
    TACGenerator() = default;

    TACProgram generate(Program& program);

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

    const TACProgram& getInstructions() const { return instructions_; }

private:
    TACProgram instructions_;
    size_t tempCounter_{0};
    size_t labelCounter_{0};
    std::string lastResult_;
    std::stack<std::string> breakStack_;
    std::stack<std::string> continueStack_;

    std::string newTemp();
    std::string newLabel();
    void emit(Opcode op, std::string a1 = "", std::string a2 = "", std::string res = "", DataType t = DataType::Unknown);
};

} // namespace banglascript
