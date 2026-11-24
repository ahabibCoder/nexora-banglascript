#pragma once
#include "ast/AST.hpp"
#include "ast/Statements.hpp"
#include <string>
#include <vector>

namespace banglascript {

struct Parameter {
    DataType type;
    std::string name;
    SourceSpan span;

    Parameter(DataType t, std::string n, SourceSpan sp = SourceSpan())
        : type(t), name(std::move(n)), span(std::move(sp)) {}
};

class FunctionDecl : public ASTNode {
public:
    FunctionDecl(DataType returnType, std::string name, std::vector<Parameter> params,
                 std::unique_ptr<BlockStmt> body, SourceSpan span = SourceSpan())
        : ASTNode(ASTNodeType::FunctionDecl, std::move(span)),
          returnType_(returnType), name_(std::move(name)),
          parameters_(std::move(params)), body_(std::move(body)) {}

    DataType getReturnType() const { return returnType_; }
    void setReturnType(DataType t) { returnType_ = t; }
    const std::string& getName() const { return name_; }
    const std::vector<Parameter>& getParameters() const { return parameters_; }
    BlockStmt* getBody() const { return body_.get(); }

    void accept(ASTVisitor& visitor) override;

private:
    DataType returnType_;
    std::string name_;
    std::vector<Parameter> parameters_;
    std::unique_ptr<BlockStmt> body_;
};

using FunctionDeclPtr = std::unique_ptr<FunctionDecl>;

class Program : public ASTNode {
public:
    explicit Program(SourceSpan span = SourceSpan())
        : ASTNode(ASTNodeType::Program, std::move(span)) {}

    void addFunction(FunctionDeclPtr fn) {
        functions_.push_back(std::move(fn));
    }

    void addStatement(StmtPtr stmt) {
        statements_.push_back(std::move(stmt));
    }

    const std::vector<FunctionDeclPtr>& getFunctions() const { return functions_; }
    const std::vector<StmtPtr>& getStatements() const { return statements_; }

    void accept(ASTVisitor& visitor) override;

private:
    std::vector<FunctionDeclPtr> functions_;
    std::vector<StmtPtr> statements_;
};

using ProgramPtr = std::unique_ptr<Program>;

} // namespace banglascript
