/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GENERATED_PARSER_TAB_HPP_INCLUDED
# define YY_YY_GENERATED_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 8 "parser/parser.y"

#include "ast/AST.hpp"
#include "ast/Expressions.hpp"
#include "ast/Statements.hpp"
#include "ast/Declarations.hpp"

namespace banglascript {
    class Driver;
}

#line 60 "generated/parser.tab.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_INT_LITERAL = 258,       /* TOKEN_INT_LITERAL  */
    TOKEN_FLOAT_LITERAL = 259,     /* TOKEN_FLOAT_LITERAL  */
    TOKEN_STRING_LITERAL = 260,    /* TOKEN_STRING_LITERAL  */
    TOKEN_IDENTIFIER = 261,        /* TOKEN_IDENTIFIER  */
    TOKEN_TYPE_SONKHA = 262,       /* "sonkha"  */
    TOKEN_TYPE_DOSOMIK = 263,      /* "dosomik"  */
    TOKEN_TYPE_BAKYA = 264,        /* "bakya"  */
    TOKEN_TYPE_SOTTI = 265,        /* "sotti"  */
    TOKEN_TYPE_SHUNNO = 266,       /* "shunno"  */
    TOKEN_JODI = 267,              /* "jodi"  */
    TOKEN_NAHOLE = 268,            /* "nahole"  */
    TOKEN_JOTOKHON = 269,          /* "jotokhon"  */
    TOKEN_BONDHO = 270,            /* "bondho"  */
    TOKEN_CHALIYEJAO = 271,        /* "chaliyejao"  */
    TOKEN_KAJ = 272,               /* "kaj"  */
    TOKEN_FEROT = 273,             /* "ferot"  */
    TOKEN_DEKHAO = 274,            /* "dekhao"  */
    TOKEN_NAO = 275,               /* "nao"  */
    TOKEN_TRUE = 276,              /* "true"  */
    TOKEN_FALSE = 277,             /* "false"  */
    TOKEN_PLUS = 278,              /* "+"  */
    TOKEN_MINUS = 279,             /* "-"  */
    TOKEN_STAR = 280,              /* "*"  */
    TOKEN_SLASH = 281,             /* "/"  */
    TOKEN_PERCENT = 282,           /* "%"  */
    TOKEN_ASSIGN = 283,            /* "="  */
    TOKEN_EQ = 284,                /* "=="  */
    TOKEN_NEQ = 285,               /* "!="  */
    TOKEN_LT = 286,                /* "<"  */
    TOKEN_LE = 287,                /* "<="  */
    TOKEN_GT = 288,                /* ">"  */
    TOKEN_GE = 289,                /* ">="  */
    TOKEN_AND = 290,               /* "&&"  */
    TOKEN_OR = 291,                /* "||"  */
    TOKEN_NOT = 292,               /* "!"  */
    TOKEN_LPAREN = 293,            /* "("  */
    TOKEN_RPAREN = 294,            /* ")"  */
    TOKEN_LBRACE = 295,            /* "{"  */
    TOKEN_RBRACE = 296,            /* "}"  */
    TOKEN_COMMA = 297,             /* ","  */
    TOKEN_SEMICOLON = 298,         /* ";"  */
    LOWER_THAN_ELSE = 299,         /* LOWER_THAN_ELSE  */
    UMINUS = 300                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "parser/parser.y"

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

#line 138 "generated/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (banglascript::Driver& driver, void* yyscanner);

/* "%code provides" blocks.  */
#line 43 "parser/parser.y"

    int yylex(YYSTYPE* yylval_param, YYLTYPE* yyloc_param, void* yyscanner);
    void yyerror(YYLTYPE* yyloc_param, banglascript::Driver& driver, void* yyscanner, const char* msg);

#line 171 "generated/parser.tab.hpp"

#endif /* !YY_YY_GENERATED_PARSER_TAB_HPP_INCLUDED  */
