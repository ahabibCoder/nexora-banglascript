%code top {
#include <iostream>
#include <string>
#include <vector>
#include <memory>
}

%code requires {
#include "ast/AST.hpp"
#include "ast/Expressions.hpp"
#include "ast/Statements.hpp"
#include "ast/Declarations.hpp"

namespace banglascript {
    class Driver;
}
}

%parse-param { banglascript::Driver& driver }
%parse-param { void* yyscanner }
%lex-param   { void* yyscanner }

%{
#include "parser/Driver.hpp"
%}

%union {
    int64_t int_val;
    double float_val;
    char* str_val;
    bool bool_val;
    banglascript::DataType data_type;
    banglascript::BinaryOp bin_op;
    banglascript::ASTNode* ast_node;
    banglascript::ExpressionNode* expr_node;
    banglascript::StatementNode* stmt_node;
    banglascript::FunctionDecl* func_node;
    std::vector<banglascript::StmtPtr>* stmt_list;
    std::vector<banglascript::ExprPtr>* expr_list;
    std::vector<banglascript::Parameter>* param_list;
}

%code provides {
    int yylex(YYSTYPE* yylval_param, YYLTYPE* yyloc_param, void* yyscanner);
    void yyerror(YYLTYPE* yyloc_param, banglascript::Driver& driver, void* yyscanner, const char* msg);
}

%define api.pure
%define parse.error verbose
%locations

/* Tokens */
%token <int_val>   TOKEN_INT_LITERAL
%token <float_val> TOKEN_FLOAT_LITERAL
%token <str_val>   TOKEN_STRING_LITERAL
%token <str_val>   TOKEN_IDENTIFIER

%token TOKEN_TYPE_SONKHA   "sonkha"
%token TOKEN_TYPE_DOSOMIK  "dosomik"
%token TOKEN_TYPE_BAKYA    "bakya"
%token TOKEN_TYPE_SOTTI    "sotti"
%token TOKEN_TYPE_SHUNNO   "shunno"

%token TOKEN_JODI          "jodi"
%token TOKEN_NAHOLE        "nahole"
%token TOKEN_JOTOKHON      "jotokhon"
%token TOKEN_BONDHO        "bondho"
%token TOKEN_CHALIYEJAO    "chaliyejao"
%token TOKEN_KAJ           "kaj"
%token TOKEN_FEROT         "ferot"
%token TOKEN_DEKHAO        "dekhao"
%token TOKEN_NAO           "nao"
%token TOKEN_TRUE          "true"
%token TOKEN_FALSE         "false"

%token TOKEN_PLUS          "+"
%token TOKEN_MINUS         "-"
%token TOKEN_STAR          "*"
%token TOKEN_SLASH         "/"
%token TOKEN_PERCENT       "%"
%token TOKEN_ASSIGN        "="
%token TOKEN_EQ            "=="
%token TOKEN_NEQ           "!="
%token TOKEN_LT            "<"
%token TOKEN_LE            "<="
%token TOKEN_GT            ">"
%token TOKEN_GE            ">="
%token TOKEN_AND           "&&"
%token TOKEN_OR            "||"
%token TOKEN_NOT           "!"

%token TOKEN_LPAREN        "("
%token TOKEN_RPAREN        ")"
%token TOKEN_LBRACE        "{"
%token TOKEN_RBRACE        "}"
%token TOKEN_COMMA         ","
%token TOKEN_SEMICOLON     ";"

/* Precedence */
%nonassoc LOWER_THAN_ELSE
%nonassoc TOKEN_NAHOLE
%right TOKEN_ASSIGN
%left TOKEN_OR
%left TOKEN_AND
%left TOKEN_EQ TOKEN_NEQ
%left TOKEN_LT TOKEN_LE TOKEN_GT TOKEN_GE
%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_STAR TOKEN_SLASH TOKEN_PERCENT
%right TOKEN_NOT UMINUS

/* Nonterminal types */
%type <data_type>  type
%type <param_list> param_list params
%type <expr_list>  arg_list args
%type <stmt_list>  statement_list
%type <func_node>  function_decl
%type <stmt_node>  statement var_decl if_statement while_statement break_statement continue_statement return_statement print_statement input_statement expr_statement block
%type <expr_node>  expression

%start root

%%

root
    : items
    ;

items
    : /* empty */
    | items item
    ;

item
    : function_decl
      {
          driver.getAST()->addFunction(banglascript::FunctionDeclPtr($1));
      }
    | statement
      {
          driver.getAST()->addStatement(banglascript::StmtPtr($1));
      }
    ;

type
    : TOKEN_TYPE_SONKHA   { $$ = banglascript::DataType::Sonkha; }
    | TOKEN_TYPE_DOSOMIK  { $$ = banglascript::DataType::Dosomik; }
    | TOKEN_TYPE_BAKYA    { $$ = banglascript::DataType::Bakya; }
    | TOKEN_TYPE_SOTTI    { $$ = banglascript::DataType::Sotti; }
    | TOKEN_TYPE_SHUNNO   { $$ = banglascript::DataType::Shunno; }
    ;

function_decl
    : TOKEN_KAJ type TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN block
      {
          std::string name($3);
          free($3);
          auto body = std::unique_ptr<banglascript::BlockStmt>(static_cast<banglascript::BlockStmt*>($7));
          auto fn = new banglascript::FunctionDecl($2, name, *$5, std::move(body));
          delete $5;
          $$ = fn;
      }
    | TOKEN_KAJ TOKEN_IDENTIFIER TOKEN_LPAREN param_list TOKEN_RPAREN block
      {
          std::string name($2);
          free($2);
          auto body = std::unique_ptr<banglascript::BlockStmt>(static_cast<banglascript::BlockStmt*>($6));
          auto fn = new banglascript::FunctionDecl(banglascript::DataType::Sonkha, name, *$4, std::move(body));
          delete $4;
          $$ = fn;
      }
    ;

param_list
    : /* empty */  { $$ = new std::vector<banglascript::Parameter>(); }
    | params       { $$ = $1; }
    ;

params
    : type TOKEN_IDENTIFIER
      {
          auto list = new std::vector<banglascript::Parameter>();
          list->emplace_back($1, std::string($2));
          free($2);
          $$ = list;
      }
    | params TOKEN_COMMA type TOKEN_IDENTIFIER
      {
          $1->emplace_back($3, std::string($4));
          free($4);
          $$ = $1;
      }
    ;

statement
    : var_decl
    | if_statement
    | while_statement
    | break_statement
    | continue_statement
    | return_statement
    | print_statement
    | input_statement
    | expr_statement
    | block
    ;

var_decl
    : type TOKEN_IDENTIFIER TOKEN_SEMICOLON
      {
          std::string name($2);
          free($2);
          $$ = new banglascript::VarDeclStmt($1, name, nullptr);
      }
    | type TOKEN_IDENTIFIER TOKEN_ASSIGN expression TOKEN_SEMICOLON
      {
          std::string name($2);
          free($2);
          $$ = new banglascript::VarDeclStmt($1, name, banglascript::ExprPtr($4));
      }
    ;

if_statement
    : TOKEN_JODI TOKEN_LPAREN expression TOKEN_RPAREN statement %prec LOWER_THAN_ELSE
      {
          $$ = new banglascript::IfStmt(banglascript::ExprPtr($3), banglascript::StmtPtr($5), nullptr);
      }
    | TOKEN_JODI TOKEN_LPAREN expression TOKEN_RPAREN statement TOKEN_NAHOLE statement
      {
          $$ = new banglascript::IfStmt(banglascript::ExprPtr($3), banglascript::StmtPtr($5), banglascript::StmtPtr($7));
      }
    ;

while_statement
    : TOKEN_JOTOKHON TOKEN_LPAREN expression TOKEN_RPAREN statement
      {
          $$ = new banglascript::WhileStmt(banglascript::ExprPtr($3), banglascript::StmtPtr($5));
      }
    ;

break_statement
    : TOKEN_BONDHO TOKEN_SEMICOLON
      {
          $$ = new banglascript::BreakStmt();
      }
    ;

continue_statement
    : TOKEN_CHALIYEJAO TOKEN_SEMICOLON
      {
          $$ = new banglascript::ContinueStmt();
      }
    ;

return_statement
    : TOKEN_FEROT TOKEN_SEMICOLON
      {
          $$ = new banglascript::ReturnStmt(nullptr);
      }
    | TOKEN_FEROT expression TOKEN_SEMICOLON
      {
          $$ = new banglascript::ReturnStmt(banglascript::ExprPtr($2));
      }
    ;

print_statement
    : TOKEN_DEKHAO TOKEN_LPAREN expression TOKEN_RPAREN TOKEN_SEMICOLON
      {
          $$ = new banglascript::PrintStmt(banglascript::ExprPtr($3));
      }
    ;

input_statement
    : TOKEN_NAO TOKEN_LPAREN TOKEN_IDENTIFIER TOKEN_RPAREN TOKEN_SEMICOLON
      {
          std::string target($3);
          free($3);
          $$ = new banglascript::InputStmt(target);
      }
    ;

expr_statement
    : expression TOKEN_SEMICOLON
      {
          $$ = new banglascript::ExprStmt(banglascript::ExprPtr($1));
      }
    ;

block
    : TOKEN_LBRACE statement_list TOKEN_RBRACE
      {
          $$ = new banglascript::BlockStmt(std::move(*$2));
          delete $2;
      }
    ;

statement_list
    : /* empty */
      {
          $$ = new std::vector<banglascript::StmtPtr>();
      }
    | statement_list statement
      {
          $1->push_back(banglascript::StmtPtr($2));
          $$ = $1;
      }
    ;

expression
    : TOKEN_IDENTIFIER TOKEN_ASSIGN expression
      {
          std::string target($1);
          free($1);
          $$ = new banglascript::AssignExpr(target, banglascript::ExprPtr($3));
      }
    | expression TOKEN_PLUS expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::Add, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_MINUS expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::Subtract, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_STAR expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::Multiply, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_SLASH expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::Divide, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_PERCENT expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::Modulo, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_EQ expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::Equal, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_NEQ expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::NotEqual, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_LT expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::Less, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_LE expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::LessEq, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_GT expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::Greater, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_GE expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::GreaterEq, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_AND expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::LogicalAnd, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | expression TOKEN_OR expression
      {
          $$ = new banglascript::BinaryExpr(banglascript::BinaryOp::LogicalOr, banglascript::ExprPtr($1), banglascript::ExprPtr($3));
      }
    | TOKEN_MINUS expression %prec UMINUS
      {
          $$ = new banglascript::UnaryExpr(banglascript::UnaryOp::Negate, banglascript::ExprPtr($2));
      }
    | TOKEN_NOT expression
      {
          $$ = new banglascript::UnaryExpr(banglascript::UnaryOp::LogicalNot, banglascript::ExprPtr($2));
      }
    | TOKEN_IDENTIFIER TOKEN_LPAREN arg_list TOKEN_RPAREN
      {
          std::string callee($1);
          free($1);
          $$ = new banglascript::CallExpr(callee, std::move(*$3));
          delete $3;
      }
    | TOKEN_LPAREN expression TOKEN_RPAREN
      {
          $$ = $2;
      }
    | TOKEN_IDENTIFIER
      {
          std::string name($1);
          free($1);
          $$ = new banglascript::VariableExpr(name);
      }
    | TOKEN_INT_LITERAL
      {
          $$ = new banglascript::LiteralExpr($1, banglascript::DataType::Sonkha);
      }
    | TOKEN_FLOAT_LITERAL
      {
          $$ = new banglascript::LiteralExpr($1, banglascript::DataType::Dosomik);
      }
    | TOKEN_STRING_LITERAL
      {
          std::string str($1);
          free($1);
          $$ = new banglascript::LiteralExpr(str, banglascript::DataType::Bakya);
      }
    | TOKEN_TRUE
      {
          $$ = new banglascript::LiteralExpr(true, banglascript::DataType::Sotti);
      }
    | TOKEN_FALSE
      {
          $$ = new banglascript::LiteralExpr(false, banglascript::DataType::Sotti);
      }
    ;

arg_list
    : /* empty */ { $$ = new std::vector<banglascript::ExprPtr>(); }
    | args        { $$ = $1; }
    ;

args
    : expression
      {
          auto list = new std::vector<banglascript::ExprPtr>();
          list->push_back(banglascript::ExprPtr($1));
          $$ = list;
      }
    | args TOKEN_COMMA expression
      {
          $1->push_back(banglascript::ExprPtr($3));
          $$ = $1;
      }
    ;

%%

void yyerror(YYLTYPE* loc, banglascript::Driver& driver, void* yyscanner, const char* msg) {
    (void)yyscanner;
    banglascript::SourcePosition pos(driver.getFilename(), loc ? loc->first_line : 1, loc ? loc->first_column : 1);
    driver.getDiagnostics().error(banglascript::SourceSpan(pos), msg);
}
