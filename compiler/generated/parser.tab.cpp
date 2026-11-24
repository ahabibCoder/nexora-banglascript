/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 1 "parser/parser.y"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#line 75 "generated/parser.tab.cpp"



/* First part of user prologue.  */
#line 23 "parser/parser.y"

#include "parser/Driver.hpp"

#line 84 "generated/parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_INT_LITERAL = 3,          /* TOKEN_INT_LITERAL  */
  YYSYMBOL_TOKEN_FLOAT_LITERAL = 4,        /* TOKEN_FLOAT_LITERAL  */
  YYSYMBOL_TOKEN_STRING_LITERAL = 5,       /* TOKEN_STRING_LITERAL  */
  YYSYMBOL_TOKEN_IDENTIFIER = 6,           /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_TYPE_SONKHA = 7,          /* "sonkha"  */
  YYSYMBOL_TOKEN_TYPE_DOSOMIK = 8,         /* "dosomik"  */
  YYSYMBOL_TOKEN_TYPE_BAKYA = 9,           /* "bakya"  */
  YYSYMBOL_TOKEN_TYPE_SOTTI = 10,          /* "sotti"  */
  YYSYMBOL_TOKEN_TYPE_SHUNNO = 11,         /* "shunno"  */
  YYSYMBOL_TOKEN_JODI = 12,                /* "jodi"  */
  YYSYMBOL_TOKEN_NAHOLE = 13,              /* "nahole"  */
  YYSYMBOL_TOKEN_JOTOKHON = 14,            /* "jotokhon"  */
  YYSYMBOL_TOKEN_BONDHO = 15,              /* "bondho"  */
  YYSYMBOL_TOKEN_CHALIYEJAO = 16,          /* "chaliyejao"  */
  YYSYMBOL_TOKEN_KAJ = 17,                 /* "kaj"  */
  YYSYMBOL_TOKEN_FEROT = 18,               /* "ferot"  */
  YYSYMBOL_TOKEN_DEKHAO = 19,              /* "dekhao"  */
  YYSYMBOL_TOKEN_NAO = 20,                 /* "nao"  */
  YYSYMBOL_TOKEN_TRUE = 21,                /* "true"  */
  YYSYMBOL_TOKEN_FALSE = 22,               /* "false"  */
  YYSYMBOL_TOKEN_PLUS = 23,                /* "+"  */
  YYSYMBOL_TOKEN_MINUS = 24,               /* "-"  */
  YYSYMBOL_TOKEN_STAR = 25,                /* "*"  */
  YYSYMBOL_TOKEN_SLASH = 26,               /* "/"  */
  YYSYMBOL_TOKEN_PERCENT = 27,             /* "%"  */
  YYSYMBOL_TOKEN_ASSIGN = 28,              /* "="  */
  YYSYMBOL_TOKEN_EQ = 29,                  /* "=="  */
  YYSYMBOL_TOKEN_NEQ = 30,                 /* "!="  */
  YYSYMBOL_TOKEN_LT = 31,                  /* "<"  */
  YYSYMBOL_TOKEN_LE = 32,                  /* "<="  */
  YYSYMBOL_TOKEN_GT = 33,                  /* ">"  */
  YYSYMBOL_TOKEN_GE = 34,                  /* ">="  */
  YYSYMBOL_TOKEN_AND = 35,                 /* "&&"  */
  YYSYMBOL_TOKEN_OR = 36,                  /* "||"  */
  YYSYMBOL_TOKEN_NOT = 37,                 /* "!"  */
  YYSYMBOL_TOKEN_LPAREN = 38,              /* "("  */
  YYSYMBOL_TOKEN_RPAREN = 39,              /* ")"  */
  YYSYMBOL_TOKEN_LBRACE = 40,              /* "{"  */
  YYSYMBOL_TOKEN_RBRACE = 41,              /* "}"  */
  YYSYMBOL_TOKEN_COMMA = 42,               /* ","  */
  YYSYMBOL_TOKEN_SEMICOLON = 43,           /* ";"  */
  YYSYMBOL_LOWER_THAN_ELSE = 44,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_UMINUS = 45,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_root = 47,                      /* root  */
  YYSYMBOL_items = 48,                     /* items  */
  YYSYMBOL_item = 49,                      /* item  */
  YYSYMBOL_type = 50,                      /* type  */
  YYSYMBOL_function_decl = 51,             /* function_decl  */
  YYSYMBOL_param_list = 52,                /* param_list  */
  YYSYMBOL_params = 53,                    /* params  */
  YYSYMBOL_statement = 54,                 /* statement  */
  YYSYMBOL_var_decl = 55,                  /* var_decl  */
  YYSYMBOL_if_statement = 56,              /* if_statement  */
  YYSYMBOL_while_statement = 57,           /* while_statement  */
  YYSYMBOL_break_statement = 58,           /* break_statement  */
  YYSYMBOL_continue_statement = 59,        /* continue_statement  */
  YYSYMBOL_return_statement = 60,          /* return_statement  */
  YYSYMBOL_print_statement = 61,           /* print_statement  */
  YYSYMBOL_input_statement = 62,           /* input_statement  */
  YYSYMBOL_expr_statement = 63,            /* expr_statement  */
  YYSYMBOL_block = 64,                     /* block  */
  YYSYMBOL_statement_list = 65,            /* statement_list  */
  YYSYMBOL_expression = 66,                /* expression  */
  YYSYMBOL_arg_list = 67,                  /* arg_list  */
  YYSYMBOL_args = 68                       /* args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   358

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   300


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   125,   125,   129,   130,   134,   138,   145,   146,   147,
     148,   149,   153,   162,   174,   175,   179,   186,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   208,   214,
     223,   227,   234,   241,   248,   255,   259,   266,   273,   282,
     289,   298,   301,   309,   315,   319,   323,   327,   331,   335,
     339,   343,   347,   351,   355,   359,   363,   367,   371,   375,
     382,   386,   392,   396,   400,   406,   410,   417,   418,   422,
     428
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_INT_LITERAL",
  "TOKEN_FLOAT_LITERAL", "TOKEN_STRING_LITERAL", "TOKEN_IDENTIFIER",
  "\"sonkha\"", "\"dosomik\"", "\"bakya\"", "\"sotti\"", "\"shunno\"",
  "\"jodi\"", "\"nahole\"", "\"jotokhon\"", "\"bondho\"", "\"chaliyejao\"",
  "\"kaj\"", "\"ferot\"", "\"dekhao\"", "\"nao\"", "\"true\"", "\"false\"",
  "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"%\"", "\"=\"", "\"==\"", "\"!=\"",
  "\"<\"", "\"<=\"", "\">\"", "\">=\"", "\"&&\"", "\"||\"", "\"!\"",
  "\"(\"", "\")\"", "\"{\"", "\"}\"", "\",\"", "\";\"", "LOWER_THAN_ELSE",
  "UMINUS", "$accept", "root", "items", "item", "type", "function_decl",
  "param_list", "params", "statement", "var_decl", "if_statement",
  "while_statement", "break_statement", "continue_statement",
  "return_statement", "print_statement", "input_statement",
  "expr_statement", "block", "statement_list", "expression", "arg_list",
  "args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-107)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -107,    12,   140,  -107,  -107,  -107,  -107,   -15,  -107,  -107,
    -107,  -107,  -107,   -24,   -23,   -18,   -13,   159,    60,    18,
      21,  -107,  -107,     0,     0,     0,  -107,  -107,    54,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,   196,     0,     0,     0,     0,  -107,  -107,    23,    61,
    -107,   211,     0,    62,  -107,  -107,   241,   101,   -27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -107,   309,   309,    30,    28,   258,   275,   164,
      34,  -107,   292,    35,  -107,  -107,  -107,     0,  -107,    -8,
      -8,  -107,  -107,  -107,     8,     8,   180,   180,   180,   180,
     103,   323,  -107,     0,   178,   178,    67,    36,    37,   164,
      40,    42,   226,   309,    64,  -107,  -107,    38,   164,    41,
    -107,  -107,  -107,   178,  -107,    80,    38,  -107,  -107,  -107
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    62,    63,    64,    61,     7,     8,
       9,    10,    11,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,     0,     0,     0,    41,     4,     0,     5,
       6,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,     0,     0,    67,     0,     0,    33,    34,     0,     0,
      35,     0,     0,     0,    57,    58,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    39,    43,    69,     0,    68,     0,     0,    14,
       0,    36,     0,     0,    60,    40,    42,     0,    28,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    59,     0,     0,     0,     0,     0,    15,    14,
       0,     0,     0,    70,    30,    32,    16,     0,     0,     0,
      37,    38,    29,     0,    13,     0,     0,    31,    17,    12
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -107,  -107,  -107,  -107,   -17,  -107,   -21,  -107,   -47,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -106,  -107,
     -16,  -107,  -107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    27,    28,    29,   107,   108,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    57,
      41,    75,    76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,    87,    51,     4,     5,     6,     7,    54,    55,    56,
      86,   124,     3,    42,    44,    45,    88,    61,    62,    63,
     129,    21,    22,    43,    23,    46,    73,    74,    77,    78,
      47,    59,    60,    61,    62,    63,    82,    24,    25,    66,
      67,    68,    69,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,    52,   114,   115,    53,
      58,    79,   106,     4,     5,     6,     7,    80,    83,   102,
     103,   112,   109,   116,   111,   117,   127,   123,    26,   118,
     126,    21,    22,   120,    23,   121,   128,   113,   119,     0,
       0,     0,   106,     0,     0,     0,     0,    24,    25,     0,
       0,   125,     0,    50,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,    14,    15,    16,     0,    18,
      19,    20,    21,    22,     0,    23,    59,    60,    61,    62,
      63,     0,    64,    65,    66,    67,    68,    69,    24,    25,
       0,    26,    85,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,    14,    15,    16,    17,    18,    19,
      20,    21,    22,     0,    23,    48,     8,     9,    10,    11,
      12,     8,     9,    10,    11,    12,     0,    24,    25,     0,
      26,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     0,    14,    15,    16,     0,    18,    19,    20,    21,
      22,     0,    23,    59,    60,    61,    62,    63,     0,     0,
       0,     0,     0,     0,     0,    24,    25,     0,    26,    59,
      60,    61,    62,    63,     0,    64,    65,    66,    67,    68,
      69,    70,    71,     0,    59,    60,    61,    62,    63,    72,
      64,    65,    66,    67,    68,    69,    70,    71,     0,    59,
      60,    61,    62,    63,    81,    64,    65,    66,    67,    68,
      69,    70,    71,     0,    59,    60,    61,    62,    63,   122,
      64,    65,    66,    67,    68,    69,    70,    71,     0,     0,
      84,    59,    60,    61,    62,    63,     0,    64,    65,    66,
      67,    68,    69,    70,    71,     0,     0,   104,    59,    60,
      61,    62,    63,     0,    64,    65,    66,    67,    68,    69,
      70,    71,     0,     0,   105,    59,    60,    61,    62,    63,
       0,    64,    65,    66,    67,    68,    69,    70,    71,     0,
       0,   110,    59,    60,    61,    62,    63,     0,    64,    65,
      66,    67,    68,    69,    70,    71,    59,    60,    61,    62,
      63,     0,    64,    65,    66,    67,    68,    69,    70
};

static const yytype_int8 yycheck[] =
{
      17,    28,    18,     3,     4,     5,     6,    23,    24,    25,
      57,   117,     0,    28,    38,    38,    43,    25,    26,    27,
     126,    21,    22,    38,    24,    43,    42,    43,    44,    45,
      43,    23,    24,    25,    26,    27,    52,    37,    38,    31,
      32,    33,    34,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    38,   104,   105,    38,
       6,    38,    79,     3,     4,     5,     6,     6,     6,    39,
      42,    87,    38,     6,    39,    39,   123,    13,    40,    42,
      39,    21,    22,    43,    24,    43,     6,   103,   109,    -1,
      -1,    -1,   109,    -1,    -1,    -1,    -1,    37,    38,    -1,
      -1,   118,    -1,    43,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    14,    15,    16,    -1,    18,
      19,    20,    21,    22,    -1,    24,    23,    24,    25,    26,
      27,    -1,    29,    30,    31,    32,    33,    34,    37,    38,
      -1,    40,    41,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,     6,     7,     8,     9,    10,
      11,     7,     8,     9,    10,    11,    -1,    37,    38,    -1,
      40,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    14,    15,    16,    -1,    18,    19,    20,    21,
      22,    -1,    24,    23,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,    23,
      24,    25,    26,    27,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    23,    24,    25,    26,    27,    43,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    23,
      24,    25,    26,    27,    43,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    23,    24,    25,    26,    27,    43,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    23,    24,    25,    26,    27,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    23,    24,
      25,    26,    27,    -1,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    23,    24,    25,    26,    27,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    23,    24,    25,    26,    27,    -1,    29,    30,
      31,    32,    33,    34,    35,    36,    23,    24,    25,    26,
      27,    -1,    29,    30,    31,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    47,    48,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    24,    37,    38,    40,    49,    50,    51,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    66,    28,    38,    38,    38,    43,    43,     6,    50,
      43,    66,    38,    38,    66,    66,    66,    65,     6,    23,
      24,    25,    26,    27,    29,    30,    31,    32,    33,    34,
      35,    36,    43,    66,    66,    67,    68,    66,    66,    38,
       6,    43,    66,     6,    39,    41,    54,    28,    43,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    39,    42,    39,    39,    50,    52,    53,    38,
      39,    39,    66,    66,    54,    54,     6,    39,    42,    52,
      43,    43,    43,    13,    64,    50,    39,    54,     6,    64
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    50,    50,    50,
      50,    50,    51,    51,    52,    52,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    55,    55,
      56,    56,    57,    58,    59,    60,    60,    61,    62,    63,
      64,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    67,    67,    68,
      68
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     7,     6,     0,     1,     2,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     5,
       5,     7,     5,     2,     2,     2,     3,     5,     5,     2,
       3,     0,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     4,
       3,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, driver, yyscanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, driver, yyscanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, banglascript::Driver& driver, void* yyscanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (driver);
  YY_USE (yyscanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, banglascript::Driver& driver, void* yyscanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, driver, yyscanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, banglascript::Driver& driver, void* yyscanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), driver, yyscanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, driver, yyscanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, banglascript::Driver& driver, void* yyscanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (driver);
  YY_USE (yyscanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (banglascript::Driver& driver, void* yyscanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, yyscanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 5: /* item: function_decl  */
#line 135 "parser/parser.y"
      {
          driver.getAST()->addFunction(banglascript::FunctionDeclPtr((yyvsp[0].func_node)));
      }
#line 1674 "generated/parser.tab.cpp"
    break;

  case 6: /* item: statement  */
#line 139 "parser/parser.y"
      {
          driver.getAST()->addStatement(banglascript::StmtPtr((yyvsp[0].stmt_node)));
      }
#line 1682 "generated/parser.tab.cpp"
    break;

  case 7: /* type: "sonkha"  */
#line 145 "parser/parser.y"
                          { (yyval.data_type) = banglascript::DataType::Sonkha; }
#line 1688 "generated/parser.tab.cpp"
    break;

  case 8: /* type: "dosomik"  */
#line 146 "parser/parser.y"
                          { (yyval.data_type) = banglascript::DataType::Dosomik; }
#line 1694 "generated/parser.tab.cpp"
    break;

  case 9: /* type: "bakya"  */
#line 147 "parser/parser.y"
                          { (yyval.data_type) = banglascript::DataType::Bakya; }
#line 1700 "generated/parser.tab.cpp"
    break;

  case 10: /* type: "sotti"  */
#line 148 "parser/parser.y"
                          { (yyval.data_type) = banglascript::DataType::Sotti; }
#line 1706 "generated/parser.tab.cpp"
    break;

  case 11: /* type: "shunno"  */
#line 149 "parser/parser.y"
                          { (yyval.data_type) = banglascript::DataType::Shunno; }
#line 1712 "generated/parser.tab.cpp"
    break;

  case 12: /* function_decl: "kaj" type TOKEN_IDENTIFIER "(" param_list ")" block  */
#line 154 "parser/parser.y"
      {
          std::string name((yyvsp[-4].str_val));
          free((yyvsp[-4].str_val));
          auto body = std::unique_ptr<banglascript::BlockStmt>(static_cast<banglascript::BlockStmt*>((yyvsp[0].stmt_node)));
          auto fn = new banglascript::FunctionDecl((yyvsp[-5].data_type), name, *(yyvsp[-2].param_list), std::move(body));
          delete (yyvsp[-2].param_list);
          (yyval.func_node) = fn;
      }
#line 1725 "generated/parser.tab.cpp"
    break;

  case 13: /* function_decl: "kaj" TOKEN_IDENTIFIER "(" param_list ")" block  */
#line 163 "parser/parser.y"
      {
          std::string name((yyvsp[-4].str_val));
          free((yyvsp[-4].str_val));
          auto body = std::unique_ptr<banglascript::BlockStmt>(static_cast<banglascript::BlockStmt*>((yyvsp[0].stmt_node)));
          auto fn = new banglascript::FunctionDecl(banglascript::DataType::Sonkha, name, *(yyvsp[-2].param_list), std::move(body));
          delete (yyvsp[-2].param_list);
          (yyval.func_node) = fn;
      }
#line 1738 "generated/parser.tab.cpp"
    break;

  case 14: /* param_list: %empty  */
#line 174 "parser/parser.y"
                   { (yyval.param_list) = new std::vector<banglascript::Parameter>(); }
#line 1744 "generated/parser.tab.cpp"
    break;

  case 15: /* param_list: params  */
#line 175 "parser/parser.y"
                   { (yyval.param_list) = (yyvsp[0].param_list); }
#line 1750 "generated/parser.tab.cpp"
    break;

  case 16: /* params: type TOKEN_IDENTIFIER  */
#line 180 "parser/parser.y"
      {
          auto list = new std::vector<banglascript::Parameter>();
          list->emplace_back((yyvsp[-1].data_type), std::string((yyvsp[0].str_val)));
          free((yyvsp[0].str_val));
          (yyval.param_list) = list;
      }
#line 1761 "generated/parser.tab.cpp"
    break;

  case 17: /* params: params "," type TOKEN_IDENTIFIER  */
#line 187 "parser/parser.y"
      {
          (yyvsp[-3].param_list)->emplace_back((yyvsp[-1].data_type), std::string((yyvsp[0].str_val)));
          free((yyvsp[0].str_val));
          (yyval.param_list) = (yyvsp[-3].param_list);
      }
#line 1771 "generated/parser.tab.cpp"
    break;

  case 28: /* var_decl: type TOKEN_IDENTIFIER ";"  */
#line 209 "parser/parser.y"
      {
          std::string name((yyvsp[-1].str_val));
          free((yyvsp[-1].str_val));
          (yyval.stmt_node) = new banglascript::VarDeclStmt((yyvsp[-2].data_type), name, nullptr);
      }
#line 1781 "generated/parser.tab.cpp"
    break;

  case 29: /* var_decl: type TOKEN_IDENTIFIER "=" expression ";"  */
#line 215 "parser/parser.y"
      {
          std::string name((yyvsp[-3].str_val));
          free((yyvsp[-3].str_val));
          (yyval.stmt_node) = new banglascript::VarDeclStmt((yyvsp[-4].data_type), name, banglascript::ExprPtr((yyvsp[-1].expr_node)));
      }
#line 1791 "generated/parser.tab.cpp"
    break;

  case 30: /* if_statement: "jodi" "(" expression ")" statement  */
#line 224 "parser/parser.y"
      {
          (yyval.stmt_node) = new banglascript::IfStmt(banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::StmtPtr((yyvsp[0].stmt_node)), nullptr);
      }
#line 1799 "generated/parser.tab.cpp"
    break;

  case 31: /* if_statement: "jodi" "(" expression ")" statement "nahole" statement  */
#line 228 "parser/parser.y"
      {
          (yyval.stmt_node) = new banglascript::IfStmt(banglascript::ExprPtr((yyvsp[-4].expr_node)), banglascript::StmtPtr((yyvsp[-2].stmt_node)), banglascript::StmtPtr((yyvsp[0].stmt_node)));
      }
#line 1807 "generated/parser.tab.cpp"
    break;

  case 32: /* while_statement: "jotokhon" "(" expression ")" statement  */
#line 235 "parser/parser.y"
      {
          (yyval.stmt_node) = new banglascript::WhileStmt(banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::StmtPtr((yyvsp[0].stmt_node)));
      }
#line 1815 "generated/parser.tab.cpp"
    break;

  case 33: /* break_statement: "bondho" ";"  */
#line 242 "parser/parser.y"
      {
          (yyval.stmt_node) = new banglascript::BreakStmt();
      }
#line 1823 "generated/parser.tab.cpp"
    break;

  case 34: /* continue_statement: "chaliyejao" ";"  */
#line 249 "parser/parser.y"
      {
          (yyval.stmt_node) = new banglascript::ContinueStmt();
      }
#line 1831 "generated/parser.tab.cpp"
    break;

  case 35: /* return_statement: "ferot" ";"  */
#line 256 "parser/parser.y"
      {
          (yyval.stmt_node) = new banglascript::ReturnStmt(nullptr);
      }
#line 1839 "generated/parser.tab.cpp"
    break;

  case 36: /* return_statement: "ferot" expression ";"  */
#line 260 "parser/parser.y"
      {
          (yyval.stmt_node) = new banglascript::ReturnStmt(banglascript::ExprPtr((yyvsp[-1].expr_node)));
      }
#line 1847 "generated/parser.tab.cpp"
    break;

  case 37: /* print_statement: "dekhao" "(" expression ")" ";"  */
#line 267 "parser/parser.y"
      {
          (yyval.stmt_node) = new banglascript::PrintStmt(banglascript::ExprPtr((yyvsp[-2].expr_node)));
      }
#line 1855 "generated/parser.tab.cpp"
    break;

  case 38: /* input_statement: "nao" "(" TOKEN_IDENTIFIER ")" ";"  */
#line 274 "parser/parser.y"
      {
          std::string target((yyvsp[-2].str_val));
          free((yyvsp[-2].str_val));
          (yyval.stmt_node) = new banglascript::InputStmt(target);
      }
#line 1865 "generated/parser.tab.cpp"
    break;

  case 39: /* expr_statement: expression ";"  */
#line 283 "parser/parser.y"
      {
          (yyval.stmt_node) = new banglascript::ExprStmt(banglascript::ExprPtr((yyvsp[-1].expr_node)));
      }
#line 1873 "generated/parser.tab.cpp"
    break;

  case 40: /* block: "{" statement_list "}"  */
#line 290 "parser/parser.y"
      {
          (yyval.stmt_node) = new banglascript::BlockStmt(std::move(*(yyvsp[-1].stmt_list)));
          delete (yyvsp[-1].stmt_list);
      }
#line 1882 "generated/parser.tab.cpp"
    break;

  case 41: /* statement_list: %empty  */
#line 298 "parser/parser.y"
      {
          (yyval.stmt_list) = new std::vector<banglascript::StmtPtr>();
      }
#line 1890 "generated/parser.tab.cpp"
    break;

  case 42: /* statement_list: statement_list statement  */
#line 302 "parser/parser.y"
      {
          (yyvsp[-1].stmt_list)->push_back(banglascript::StmtPtr((yyvsp[0].stmt_node)));
          (yyval.stmt_list) = (yyvsp[-1].stmt_list);
      }
#line 1899 "generated/parser.tab.cpp"
    break;

  case 43: /* expression: TOKEN_IDENTIFIER "=" expression  */
#line 310 "parser/parser.y"
      {
          std::string target((yyvsp[-2].str_val));
          free((yyvsp[-2].str_val));
          (yyval.expr_node) = new banglascript::AssignExpr(target, banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1909 "generated/parser.tab.cpp"
    break;

  case 44: /* expression: expression "+" expression  */
#line 316 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::Add, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1917 "generated/parser.tab.cpp"
    break;

  case 45: /* expression: expression "-" expression  */
#line 320 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::Subtract, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1925 "generated/parser.tab.cpp"
    break;

  case 46: /* expression: expression "*" expression  */
#line 324 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::Multiply, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1933 "generated/parser.tab.cpp"
    break;

  case 47: /* expression: expression "/" expression  */
#line 328 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::Divide, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1941 "generated/parser.tab.cpp"
    break;

  case 48: /* expression: expression "%" expression  */
#line 332 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::Modulo, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1949 "generated/parser.tab.cpp"
    break;

  case 49: /* expression: expression "==" expression  */
#line 336 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::Equal, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1957 "generated/parser.tab.cpp"
    break;

  case 50: /* expression: expression "!=" expression  */
#line 340 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::NotEqual, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1965 "generated/parser.tab.cpp"
    break;

  case 51: /* expression: expression "<" expression  */
#line 344 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::Less, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1973 "generated/parser.tab.cpp"
    break;

  case 52: /* expression: expression "<=" expression  */
#line 348 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::LessEq, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1981 "generated/parser.tab.cpp"
    break;

  case 53: /* expression: expression ">" expression  */
#line 352 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::Greater, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1989 "generated/parser.tab.cpp"
    break;

  case 54: /* expression: expression ">=" expression  */
#line 356 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::GreaterEq, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 1997 "generated/parser.tab.cpp"
    break;

  case 55: /* expression: expression "&&" expression  */
#line 360 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::LogicalAnd, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 2005 "generated/parser.tab.cpp"
    break;

  case 56: /* expression: expression "||" expression  */
#line 364 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::BinaryExpr(banglascript::BinaryOp::LogicalOr, banglascript::ExprPtr((yyvsp[-2].expr_node)), banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 2013 "generated/parser.tab.cpp"
    break;

  case 57: /* expression: "-" expression  */
#line 368 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::UnaryExpr(banglascript::UnaryOp::Negate, banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 2021 "generated/parser.tab.cpp"
    break;

  case 58: /* expression: "!" expression  */
#line 372 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::UnaryExpr(banglascript::UnaryOp::LogicalNot, banglascript::ExprPtr((yyvsp[0].expr_node)));
      }
#line 2029 "generated/parser.tab.cpp"
    break;

  case 59: /* expression: TOKEN_IDENTIFIER "(" arg_list ")"  */
#line 376 "parser/parser.y"
      {
          std::string callee((yyvsp[-3].str_val));
          free((yyvsp[-3].str_val));
          (yyval.expr_node) = new banglascript::CallExpr(callee, std::move(*(yyvsp[-1].expr_list)));
          delete (yyvsp[-1].expr_list);
      }
#line 2040 "generated/parser.tab.cpp"
    break;

  case 60: /* expression: "(" expression ")"  */
#line 383 "parser/parser.y"
      {
          (yyval.expr_node) = (yyvsp[-1].expr_node);
      }
#line 2048 "generated/parser.tab.cpp"
    break;

  case 61: /* expression: TOKEN_IDENTIFIER  */
#line 387 "parser/parser.y"
      {
          std::string name((yyvsp[0].str_val));
          free((yyvsp[0].str_val));
          (yyval.expr_node) = new banglascript::VariableExpr(name);
      }
#line 2058 "generated/parser.tab.cpp"
    break;

  case 62: /* expression: TOKEN_INT_LITERAL  */
#line 393 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::LiteralExpr((yyvsp[0].int_val), banglascript::DataType::Sonkha);
      }
#line 2066 "generated/parser.tab.cpp"
    break;

  case 63: /* expression: TOKEN_FLOAT_LITERAL  */
#line 397 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::LiteralExpr((yyvsp[0].float_val), banglascript::DataType::Dosomik);
      }
#line 2074 "generated/parser.tab.cpp"
    break;

  case 64: /* expression: TOKEN_STRING_LITERAL  */
#line 401 "parser/parser.y"
      {
          std::string str((yyvsp[0].str_val));
          free((yyvsp[0].str_val));
          (yyval.expr_node) = new banglascript::LiteralExpr(str, banglascript::DataType::Bakya);
      }
#line 2084 "generated/parser.tab.cpp"
    break;

  case 65: /* expression: "true"  */
#line 407 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::LiteralExpr(true, banglascript::DataType::Sotti);
      }
#line 2092 "generated/parser.tab.cpp"
    break;

  case 66: /* expression: "false"  */
#line 411 "parser/parser.y"
      {
          (yyval.expr_node) = new banglascript::LiteralExpr(false, banglascript::DataType::Sotti);
      }
#line 2100 "generated/parser.tab.cpp"
    break;

  case 67: /* arg_list: %empty  */
#line 417 "parser/parser.y"
                  { (yyval.expr_list) = new std::vector<banglascript::ExprPtr>(); }
#line 2106 "generated/parser.tab.cpp"
    break;

  case 68: /* arg_list: args  */
#line 418 "parser/parser.y"
                  { (yyval.expr_list) = (yyvsp[0].expr_list); }
#line 2112 "generated/parser.tab.cpp"
    break;

  case 69: /* args: expression  */
#line 423 "parser/parser.y"
      {
          auto list = new std::vector<banglascript::ExprPtr>();
          list->push_back(banglascript::ExprPtr((yyvsp[0].expr_node)));
          (yyval.expr_list) = list;
      }
#line 2122 "generated/parser.tab.cpp"
    break;

  case 70: /* args: args "," expression  */
#line 429 "parser/parser.y"
      {
          (yyvsp[-2].expr_list)->push_back(banglascript::ExprPtr((yyvsp[0].expr_node)));
          (yyval.expr_list) = (yyvsp[-2].expr_list);
      }
#line 2131 "generated/parser.tab.cpp"
    break;


#line 2135 "generated/parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, driver, yyscanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, driver, yyscanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, driver, yyscanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, driver, yyscanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, driver, yyscanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, driver, yyscanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 435 "parser/parser.y"


void yyerror(YYLTYPE* loc, banglascript::Driver& driver, void* yyscanner, const char* msg) {
    (void)yyscanner;
    banglascript::SourcePosition pos(driver.getFilename(), loc ? loc->first_line : 1, loc ? loc->first_column : 1);
    driver.getDiagnostics().error(banglascript::SourceSpan(pos), msg);
}
