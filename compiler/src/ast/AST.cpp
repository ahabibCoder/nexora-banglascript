#include "ast/AST.hpp"
#include "ast/Expressions.hpp"
#include "ast/Statements.hpp"
#include "ast/Declarations.hpp"
#include "ast/ASTVisitor.hpp"

namespace banglascript {

void LiteralExpr::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void VariableExpr::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void BinaryExpr::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void UnaryExpr::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void CallExpr::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void AssignExpr::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void InputExpr::accept(ASTVisitor& visitor) { visitor.visit(*this); }

void ExprStmt::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void BlockStmt::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void VarDeclStmt::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void IfStmt::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void WhileStmt::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void BreakStmt::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void ContinueStmt::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void ReturnStmt::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void PrintStmt::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void InputStmt::accept(ASTVisitor& visitor) { visitor.visit(*this); }

void FunctionDecl::accept(ASTVisitor& visitor) { visitor.visit(*this); }
void Program::accept(ASTVisitor& visitor) { visitor.visit(*this); }

} // namespace banglascript
