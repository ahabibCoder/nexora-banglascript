#include "ast/ASTPrettyPrinter.hpp"
#include "ast/Declarations.hpp"
#include "ast/Expressions.hpp"
#include "ast/Statements.hpp"

namespace banglascript {

void ASTPrettyPrinter::print(ASTNode& root) {
    indent_ = "";
    root.accept(*this);
}

void ASTPrettyPrinter::printIndent(bool isLast) {
    out_ << indent_ << (isLast ? "└── " : "├── ");
}

void ASTPrettyPrinter::pushIndent(bool isLast) {
    indent_ += (isLast ? "    " : "│   ");
}

void ASTPrettyPrinter::popIndent() {
    if (indent_.length() >= 4) {
        indent_.erase(indent_.length() - 4);
    }
}

void ASTPrettyPrinter::visit(Program& node) {
    out_ << "Program\n";
    size_t total = node.getFunctions().size() + node.getStatements().size();
    size_t count = 0;

    for (const auto& fn : node.getFunctions()) {
        count++;
        bool isLast = (count == total);
        printIndent(isLast);
        pushIndent(isLast);
        fn->accept(*this);
        popIndent();
    }

    for (const auto& stmt : node.getStatements()) {
        count++;
        bool isLast = (count == total);
        printIndent(isLast);
        pushIndent(isLast);
        stmt->accept(*this);
        popIndent();
    }
}

void ASTPrettyPrinter::visit(FunctionDecl& node) {
    out_ << "FunctionDecl: " << node.getName() << " -> " << dataTypeToString(node.getReturnType()) << "(";
    for (size_t i = 0; i < node.getParameters().size(); ++i) {
        if (i > 0) out_ << ", ";
        out_ << dataTypeToString(node.getParameters()[i].type) << " " << node.getParameters()[i].name;
    }
    out_ << ")\n";

    if (node.getBody()) {
        printIndent(true);
        pushIndent(true);
        node.getBody()->accept(*this);
        popIndent();
    }
}

void ASTPrettyPrinter::visit(VarDeclStmt& node) {
    out_ << "VarDecl: " << dataTypeToString(node.getVarType()) << " " << node.getName() << "\n";
    if (node.hasInitializer()) {
        printIndent(true);
        pushIndent(true);
        node.getInitializer()->accept(*this);
        popIndent();
    }
}

void ASTPrettyPrinter::visit(BlockStmt& node) {
    out_ << "BlockStmt (" << node.getStatements().size() << " statements)\n";
    for (size_t i = 0; i < node.getStatements().size(); ++i) {
        bool isLast = (i == node.getStatements().size() - 1);
        printIndent(isLast);
        pushIndent(isLast);
        node.getStatements()[i]->accept(*this);
        popIndent();
    }
}

void ASTPrettyPrinter::visit(ExprStmt& node) {
    out_ << "ExprStmt\n";
    if (node.getExpression()) {
        printIndent(true);
        pushIndent(true);
        node.getExpression()->accept(*this);
        popIndent();
    }
}

void ASTPrettyPrinter::visit(IfStmt& node) {
    out_ << "IfStmt\n";

    printIndent(false);
    out_ << "Condition:\n";
    pushIndent(false);
    printIndent(true);
    pushIndent(true);
    node.getCondition()->accept(*this);
    popIndent();
    popIndent();

    bool hasElse = node.hasElseBranch();
    printIndent(!hasElse);
    out_ << "Then:\n";
    pushIndent(!hasElse);
    printIndent(true);
    pushIndent(true);
    node.getThenBranch()->accept(*this);
    popIndent();
    popIndent();

    if (hasElse) {
        printIndent(true);
        out_ << "Else:\n";
        pushIndent(true);
        printIndent(true);
        pushIndent(true);
        node.getElseBranch()->accept(*this);
        popIndent();
        popIndent();
    }
}

void ASTPrettyPrinter::visit(WhileStmt& node) {
    out_ << "WhileStmt (jotokhon)\n";

    printIndent(false);
    out_ << "Condition:\n";
    pushIndent(false);
    printIndent(true);
    pushIndent(true);
    node.getCondition()->accept(*this);
    popIndent();
    popIndent();

    printIndent(true);
    out_ << "Body:\n";
    pushIndent(true);
    printIndent(true);
    pushIndent(true);
    node.getBody()->accept(*this);
    popIndent();
    popIndent();
}

void ASTPrettyPrinter::visit(BreakStmt&) {
    out_ << "BreakStmt (bondho)\n";
}

void ASTPrettyPrinter::visit(ContinueStmt&) {
    out_ << "ContinueStmt (chaliyejao)\n";
}

void ASTPrettyPrinter::visit(ReturnStmt& node) {
    out_ << "ReturnStmt (ferot)\n";
    if (node.hasValue()) {
        printIndent(true);
        pushIndent(true);
        node.getValue()->accept(*this);
        popIndent();
    }
}

void ASTPrettyPrinter::visit(PrintStmt& node) {
    out_ << "PrintStmt (dekhao)\n";
    if (node.getExpression()) {
        printIndent(true);
        pushIndent(true);
        node.getExpression()->accept(*this);
        popIndent();
    }
}

void ASTPrettyPrinter::visit(InputStmt& node) {
    out_ << "InputStmt (nao): " << node.getTarget() << "\n";
}

void ASTPrettyPrinter::visit(LiteralExpr& node) {
    out_ << "LiteralExpr: ";
    std::visit([this](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, bool>) {
            out_ << (arg ? "true" : "false");
        } else if constexpr (std::is_same_v<T, std::string>) {
            out_ << "\"" << arg << "\"";
        } else {
            out_ << arg;
        }
    }, node.getValue());
    out_ << " [" << dataTypeToString(node.getInferredType()) << "]\n";
}

void ASTPrettyPrinter::visit(VariableExpr& node) {
    out_ << "VariableExpr: " << node.getName()
         << " [" << dataTypeToString(node.getInferredType()) << "]\n";
}

void ASTPrettyPrinter::visit(BinaryExpr& node) {
    out_ << "BinaryExpr (" << binaryOpToString(node.getOp()) << ")\n";

    printIndent(false);
    pushIndent(false);
    node.getLeft()->accept(*this);
    popIndent();

    printIndent(true);
    pushIndent(true);
    node.getRight()->accept(*this);
    popIndent();
}

void ASTPrettyPrinter::visit(UnaryExpr& node) {
    out_ << "UnaryExpr (" << unaryOpToString(node.getOp()) << ")\n";
    printIndent(true);
    pushIndent(true);
    node.getOperand()->accept(*this);
    popIndent();
}

void ASTPrettyPrinter::visit(CallExpr& node) {
    out_ << "CallExpr: " << node.getCallee() << " (" << node.getArguments().size() << " args)\n";
    for (size_t i = 0; i < node.getArguments().size(); ++i) {
        bool isLast = (i == node.getArguments().size() - 1);
        printIndent(isLast);
        pushIndent(isLast);
        node.getArguments()[i]->accept(*this);
        popIndent();
    }
}

void ASTPrettyPrinter::visit(AssignExpr& node) {
    out_ << "AssignExpr: " << node.getTarget() << " =\n";
    printIndent(true);
    pushIndent(true);
    node.getValue()->accept(*this);
    popIndent();
}

void ASTPrettyPrinter::visit(InputExpr& node) {
    out_ << "InputExpr (nao)\n";
    if (node.hasPrompt()) {
        printIndent(true);
        pushIndent(true);
        node.getPrompt()->accept(*this);
        popIndent();
    }
}

} // namespace banglascript
