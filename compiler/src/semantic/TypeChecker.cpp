#include "semantic/TypeChecker.hpp"

namespace banglascript {

bool TypeChecker::check(Program& program) {
    symbolTable_.reset();
    currentFunctionReturnType_ = DataType::Shunno;
    insideFunction_ = false;
    loopDepth_ = 0;

    program.accept(*this);
    return !diagnostics_.hasErrors();
}

bool TypeChecker::typesCompatible(DataType expected, DataType actual) {
    if (expected == actual) return true;
    // Allow integer promotion to float
    if (expected == DataType::Dosomik && actual == DataType::Sonkha) return true;
    return false;
}

DataType TypeChecker::resolveNumericType(DataType left, DataType right) {
    if (left == DataType::Dosomik || right == DataType::Dosomik) {
        return DataType::Dosomik;
    }
    return DataType::Sonkha;
}

void TypeChecker::visit(Program& node) {
    // Pass 1: Register function signatures in global scope
    for (const auto& fn : node.getFunctions()) {
        auto existing = symbolTable_.lookupCurrentScope(fn->getName());
        if (existing.has_value()) {
            diagnostics_.error(fn->getSpan(), "Redeclaration of function '" + fn->getName() + "'");
            continue;
        }

        Symbol fnSym(fn->getName(), fn->getReturnType(), SymbolCategory::Function, 0, fn->getSpan().start);
        fnSym.returnType = fn->getReturnType();
        for (const auto& p : fn->getParameters()) {
            fnSym.parameterTypes.push_back(p.type);
        }
        symbolTable_.insert(fnSym);
    }

    // Pass 2: Check function bodies
    for (const auto& fn : node.getFunctions()) {
        fn->accept(*this);
    }

    // Pass 3: Check global top-level statements
    for (const auto& stmt : node.getStatements()) {
        stmt->accept(*this);
    }
}

void TypeChecker::visit(FunctionDecl& node) {
    insideFunction_ = true;
    currentFunctionReturnType_ = node.getReturnType();

    symbolTable_.enterScope();

    // Register parameters in function scope
    for (const auto& p : node.getParameters()) {
        auto existing = symbolTable_.lookupCurrentScope(p.name);
        if (existing.has_value()) {
            diagnostics_.error(p.span, "Duplicate parameter name '" + p.name + "' in function '" + node.getName() + "'");
        } else {
            Symbol paramSym(p.name, p.type, SymbolCategory::Parameter, symbolTable_.getCurrentLevel(), p.span.start);
            symbolTable_.insert(paramSym);
        }
    }

    if (node.getBody()) {
        for (const auto& stmt : node.getBody()->getStatements()) {
            stmt->accept(*this);
        }
    }

    symbolTable_.exitScope();
    insideFunction_ = false;
    currentFunctionReturnType_ = DataType::Shunno;
}

void TypeChecker::visit(VarDeclStmt& node) {
    auto existing = symbolTable_.lookupCurrentScope(node.getName());
    if (existing.has_value()) {
        diagnostics_.error(node.getSpan(), "Variable '" + node.getName() + "' is already declared in this scope");
        return;
    }

    if (node.hasInitializer()) {
        node.getInitializer()->accept(*this);
        DataType initType = node.getInitializer()->getInferredType();
        if (!typesCompatible(node.getVarType(), initType)) {
            diagnostics_.error(node.getSpan(),
                "Cannot initialize variable '" + node.getName() + "' of type '" +
                dataTypeToString(node.getVarType()) + "' with value of type '" +
                dataTypeToString(initType) + "'");
        }
    }

    Symbol sym(node.getName(), node.getVarType(), SymbolCategory::Variable,
               symbolTable_.getCurrentLevel(), node.getSpan().start);
    symbolTable_.insert(sym);
}

void TypeChecker::visit(BlockStmt& node) {
    symbolTable_.enterScope();
    for (const auto& stmt : node.getStatements()) {
        stmt->accept(*this);
    }
    symbolTable_.exitScope();
}

void TypeChecker::visit(ExprStmt& node) {
    if (node.getExpression()) {
        node.getExpression()->accept(*this);
    }
}

void TypeChecker::visit(IfStmt& node) {
    node.getCondition()->accept(*this);
    if (node.getCondition()->getInferredType() != DataType::Sotti) {
        diagnostics_.error(node.getCondition()->getSpan(),
            "Condition in 'jodi' statement must evaluate to 'sotti' (boolean), got '" +
            dataTypeToString(node.getCondition()->getInferredType()) + "'");
    }

    if (node.getThenBranch()) {
        node.getThenBranch()->accept(*this);
    }

    if (node.hasElseBranch()) {
        node.getElseBranch()->accept(*this);
    }
}

void TypeChecker::visit(WhileStmt& node) {
    node.getCondition()->accept(*this);
    if (node.getCondition()->getInferredType() != DataType::Sotti) {
        diagnostics_.error(node.getCondition()->getSpan(),
            "Condition in 'jotokhon' loop must evaluate to 'sotti' (boolean), got '" +
            dataTypeToString(node.getCondition()->getInferredType()) + "'");
    }

    loopDepth_++;
    if (node.getBody()) {
        node.getBody()->accept(*this);
    }
    loopDepth_--;
}

void TypeChecker::visit(BreakStmt& node) {
    if (loopDepth_ == 0) {
        diagnostics_.error(node.getSpan(), "'bondho' (break) cannot be used outside of a loop");
    }
}

void TypeChecker::visit(ContinueStmt& node) {
    if (loopDepth_ == 0) {
        diagnostics_.error(node.getSpan(), "'chaliyejao' (continue) cannot be used outside of a loop");
    }
}

void TypeChecker::visit(ReturnStmt& node) {
    if (!insideFunction_) {
        // Top-level return is allowed without value or as exit code
        if (node.hasValue()) {
            node.getValue()->accept(*this);
        }
        return;
    }

    if (node.hasValue()) {
        node.getValue()->accept(*this);
        DataType actual = node.getValue()->getInferredType();
        if (!typesCompatible(currentFunctionReturnType_, actual)) {
            diagnostics_.error(node.getSpan(),
                "Function specifies return type '" + dataTypeToString(currentFunctionReturnType_) +
                "' but returned value of type '" + dataTypeToString(actual) + "'");
        }
    } else {
        if (currentFunctionReturnType_ != DataType::Shunno) {
            diagnostics_.error(node.getSpan(),
                "Non-void function must return a value of type '" +
                dataTypeToString(currentFunctionReturnType_) + "'");
        }
    }
}

void TypeChecker::visit(PrintStmt& node) {
    if (node.getExpression()) {
        node.getExpression()->accept(*this);
    }
}

void TypeChecker::visit(InputStmt& node) {
    auto sym = symbolTable_.lookup(node.getTarget());
    if (!sym.has_value()) {
        diagnostics_.error(node.getSpan(), "Undeclared variable '" + node.getTarget() + "' in 'nao' input statement");
    } else if (sym->category == SymbolCategory::Function) {
        diagnostics_.error(node.getSpan(), "Cannot read input into function symbol '" + node.getTarget() + "'");
    }
}

void TypeChecker::visit(LiteralExpr& /*node*/) {
    // Literal type is already set upon construction
}

void TypeChecker::visit(VariableExpr& node) {
    auto sym = symbolTable_.lookup(node.getName());
    if (!sym.has_value()) {
        diagnostics_.error(node.getSpan(), "Undeclared variable '" + node.getName() + "'");
        node.setInferredType(DataType::Unknown);
    } else {
        node.setInferredType(sym->type);
    }
}

void TypeChecker::visit(BinaryExpr& node) {
    node.getLeft()->accept(*this);
    node.getRight()->accept(*this);

    DataType lType = node.getLeft()->getInferredType();
    DataType rType = node.getRight()->getInferredType();

    switch (node.getOp()) {
        case BinaryOp::Add:
            if (lType == DataType::Bakya || rType == DataType::Bakya) {
                // String concatenation
                node.setInferredType(DataType::Bakya);
            } else if (isNumericType(lType) && isNumericType(rType)) {
                node.setInferredType(resolveNumericType(lType, rType));
            } else {
                diagnostics_.error(node.getSpan(),
                    "Operator '+' is not supported between types '" +
                    dataTypeToString(lType) + "' and '" + dataTypeToString(rType) + "'");
                node.setInferredType(DataType::Unknown);
            }
            break;

        case BinaryOp::Subtract:
        case BinaryOp::Multiply:
        case BinaryOp::Divide:
        case BinaryOp::Modulo:
            if (isNumericType(lType) && isNumericType(rType)) {
                if (node.getOp() == BinaryOp::Modulo) {
                    if (lType != DataType::Sonkha || rType != DataType::Sonkha) {
                        diagnostics_.error(node.getSpan(), "Modulo operator '%' requires integer ('sonkha') operands");
                    }
                    node.setInferredType(DataType::Sonkha);
                } else {
                    node.setInferredType(resolveNumericType(lType, rType));
                }
            } else {
                diagnostics_.error(node.getSpan(),
                    "Arithmetic operator '" + binaryOpToString(node.getOp()) +
                    "' requires numeric operands ('sonkha' or 'dosomik'), got '" +
                    dataTypeToString(lType) + "' and '" + dataTypeToString(rType) + "'");
                node.setInferredType(DataType::Unknown);
            }
            break;

        case BinaryOp::Equal:
        case BinaryOp::NotEqual:
            node.setInferredType(DataType::Sotti);
            break;

        case BinaryOp::Less:
        case BinaryOp::LessEq:
        case BinaryOp::Greater:
        case BinaryOp::GreaterEq:
            if (!isNumericType(lType) || !isNumericType(rType)) {
                diagnostics_.error(node.getSpan(),
                    "Relational operator '" + binaryOpToString(node.getOp()) +
                    "' requires numeric operands, got '" +
                    dataTypeToString(lType) + "' and '" + dataTypeToString(rType) + "'");
            }
            node.setInferredType(DataType::Sotti);
            break;

        case BinaryOp::LogicalAnd:
        case BinaryOp::LogicalOr:
            if (lType != DataType::Sotti || rType != DataType::Sotti) {
                diagnostics_.error(node.getSpan(),
                    "Logical operator '" + binaryOpToString(node.getOp()) +
                    "' requires boolean ('sotti') operands, got '" +
                    dataTypeToString(lType) + "' and '" + dataTypeToString(rType) + "'");
            }
            node.setInferredType(DataType::Sotti);
            break;
    }
}

void TypeChecker::visit(UnaryExpr& node) {
    node.getOperand()->accept(*this);
    DataType opType = node.getOperand()->getInferredType();

    if (node.getOp() == UnaryOp::Negate) {
        if (!isNumericType(opType)) {
            diagnostics_.error(node.getSpan(),
                "Unary negation '-' requires numeric operand, got '" + dataTypeToString(opType) + "'");
            node.setInferredType(DataType::Unknown);
        } else {
            node.setInferredType(opType);
        }
    } else if (node.getOp() == UnaryOp::LogicalNot) {
        if (opType != DataType::Sotti) {
            diagnostics_.error(node.getSpan(),
                "Logical NOT '!' requires boolean ('sotti') operand, got '" + dataTypeToString(opType) + "'");
            node.setInferredType(DataType::Unknown);
        } else {
            node.setInferredType(DataType::Sotti);
        }
    }
}

void TypeChecker::visit(CallExpr& node) {
    auto sym = symbolTable_.lookup(node.getCallee());
    if (!sym.has_value() || sym->category != SymbolCategory::Function) {
        diagnostics_.error(node.getSpan(), "Undeclared function '" + node.getCallee() + "'");
        node.setInferredType(DataType::Unknown);
        return;
    }

    if (node.getArguments().size() != sym->parameterTypes.size()) {
        diagnostics_.error(node.getSpan(),
            "Function '" + node.getCallee() + "' expects " +
            std::to_string(sym->parameterTypes.size()) + " arguments, but " +
            std::to_string(node.getArguments().size()) + " were provided");
    }

    size_t checkCount = std::min(node.getArguments().size(), sym->parameterTypes.size());
    for (size_t i = 0; i < checkCount; ++i) {
        node.getArguments()[i]->accept(*this);
        DataType argType = node.getArguments()[i]->getInferredType();
        DataType paramType = sym->parameterTypes[i];
        if (!typesCompatible(paramType, argType)) {
            diagnostics_.error(node.getArguments()[i]->getSpan(),
                "Argument " + std::to_string(i + 1) + " of function '" + node.getCallee() +
                "' expects type '" + dataTypeToString(paramType) + "', but got '" +
                dataTypeToString(argType) + "'");
        }
    }

    node.setInferredType(sym->returnType);
}

void TypeChecker::visit(AssignExpr& node) {
    auto sym = symbolTable_.lookup(node.getTarget());
    if (!sym.has_value()) {
        diagnostics_.error(node.getSpan(), "Undeclared variable '" + node.getTarget() + "' in assignment");
        node.setInferredType(DataType::Unknown);
        return;
    }

    node.getValue()->accept(*this);
    DataType valType = node.getValue()->getInferredType();

    if (!typesCompatible(sym->type, valType)) {
        diagnostics_.error(node.getSpan(),
            "Cannot assign value of type '" + dataTypeToString(valType) +
            "' to variable '" + node.getTarget() + "' of type '" + dataTypeToString(sym->type) + "'");
    }

    node.setInferredType(sym->type);
}

} // namespace banglascript
