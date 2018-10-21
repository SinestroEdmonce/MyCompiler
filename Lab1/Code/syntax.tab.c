/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "syntax.y" /* yacc.c:339  */

    #include<stdio.h>
    #include<stdlib.h>
    #include<stdbool.h>
    #include "SyntaxTree.h"
    #include "lex.yy.c"
    #define MAXLENGTH 128


#line 76 "syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    ID = 260,
    SEMI = 261,
    COMMA = 262,
    ASSIGNOP = 263,
    RELOP = 264,
    PLUS = 265,
    MINUS = 266,
    STAR = 267,
    DIV = 268,
    AND = 269,
    OR = 270,
    DOT = 271,
    NOT = 272,
    TYPE = 273,
    LP = 274,
    RP = 275,
    LB = 276,
    RB = 277,
    LC = 278,
    RC = 279,
    STRUCT = 280,
    RETURN = 281,
    IF = 282,
    ELSE = 283,
    WHILE = 284,
    LOWER_THAN_ELSE = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 11 "syntax.y" /* yacc.c:355  */

    struct TreeNode* tree_node;

#line 151 "syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 168 "syntax.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   447

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    68,    68,    70,    71,    73,    74,    75,    77,    78,
      79,    80,    82,    83,    85,    86,    90,    91,    93,    94,
      96,    98,    99,   101,   105,   106,   108,   109,   110,   112,
     113,   115,   116,   117,   119,   120,   122,   123,   125,   127,
     131,   132,   134,   135,   137,   138,   139,   140,   141,   142,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   159,   160,   162,   164,   166,   167,   169,   170,
     172,   173,   175,   176,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   199,   200,   201,   202,   203,   205,   206,   208
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "DOT",
  "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

#define YYPACT_NINF -77

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-77)))

#define YYTABLE_NINF -44

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,   193,   -77,    12,    18,   -77,     6,   209,   -77,     2,
     -77,   -77,    62,    44,    61,    76,   -77,   -77,   -77,    52,
     157,   -77,    79,     3,    14,   105,   -77,    95,   224,    38,
     -77,   175,    32,   -77,   110,    38,   -77,   -77,   111,     2,
     -77,   174,    60,   126,    21,    38,   -77,   131,   -77,   152,
      54,   204,   -77,    43,   -77,   -77,   -77,   -77,   114,   133,
     220,   235,   -77,   -77,   -77,     7,   -77,   210,   215,   -77,
     -77,    70,    87,   -77,   -77,   222,   304,   304,   304,   234,
     109,   118,   -77,   226,    43,   316,   -77,   154,   304,   251,
     -77,   178,   237,   -77,   237,   -77,   -77,   229,   426,   140,
     345,   252,   176,   304,   256,   304,   273,   -77,   -77,   -77,
     304,   304,   304,   304,   278,   304,   304,   304,   258,   295,
     264,   -77,   387,   -77,   387,   264,   -77,   -77,   -77,   331,
      63,   -77,   -77,   -77,   -77,   359,   244,   192,   373,   245,
     208,   387,   420,   426,   426,   -77,   140,   140,   413,   400,
     -77,   247,   159,   300,   -77,   -77,    75,    75,    75,    86,
      75,    75,    75,    75,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,   101,   238,   -77,   -77,   -77,   -77,    75,   113,
     -77,    87,   -77
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    16,    22,     0,     2,     0,     0,    17,     0,
      24,    10,     0,    12,    23,     0,    19,     1,     3,     0,
       0,     6,     0,     0,     0,     0,     8,     0,     0,    63,
       9,     0,     0,     5,    11,    63,     7,    14,     0,    15,
      13,     0,     0,     0,     0,    63,    33,     0,    30,     0,
       0,    35,    41,     0,    26,    27,    28,    25,     0,    70,
       0,    66,    20,    18,    62,     0,    31,    39,    38,    32,
      29,     0,     0,    90,    91,    89,     0,     0,     0,     0,
       0,     0,    45,     0,     0,     0,    65,     0,     0,     0,
      64,     0,     0,    37,    36,    34,    50,     0,    83,    84,
       0,     0,     0,     0,     0,     0,     0,    40,    42,    44,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    68,    72,    73,    71,    69,    67,    94,    86,    98,
       0,    82,    51,    52,    46,     0,     0,     0,     0,     0,
       0,    74,    77,    78,    79,    92,    80,    81,    75,    76,
      88,     0,     0,     0,    93,    85,     0,     0,     0,     0,
       0,     0,     0,     0,    95,    96,    87,    99,    97,    54,
      53,    55,    60,    47,    56,    57,    58,    49,     0,     0,
      59,    61,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -77,   -77,   274,   -77,    99,    10,   -77,   -77,   -77,   -38,
     -77,   -51,   -77,   263,   203,   -13,   117,   -77,   156,   -77,
     -76,   135
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    12,    43,     8,    15,    16,    13,
      23,    50,    51,    82,    83,    84,    44,    45,    60,    61,
      85,   130
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      98,    99,   100,   102,    34,    59,    -4,     1,    92,    24,
       7,    68,   122,   124,    93,     9,     7,    14,    17,    10,
      95,   129,    62,    25,     2,     2,    35,   135,   137,   138,
     140,     3,     3,    47,   141,   142,   143,   144,   146,   147,
     148,   149,    49,   152,    72,    63,    73,    74,    75,    59,
       2,    27,    48,    59,    76,    69,     2,     3,    30,    24,
      77,    56,    78,     3,   154,    28,    35,   -43,    26,    79,
      80,    94,    81,    25,    70,    49,    72,   129,    73,    74,
      75,    49,    57,   155,   -21,    33,    76,   172,     2,    73,
      74,    75,    77,    96,    78,     3,    39,    76,    35,    29,
      10,    79,    80,    77,    81,    78,    22,    96,    38,    35,
     103,    52,    79,    80,   181,    81,    73,    74,    75,   105,
      86,    87,    88,    37,    76,    52,    40,    58,   104,   178,
      77,    10,    78,    54,    52,    25,    35,   106,    65,    79,
      80,    89,    81,   169,   170,   171,   173,   174,   175,   176,
     177,    66,    53,    67,    28,   120,   118,    10,    31,    10,
     165,   119,    64,   -24,   -24,   180,   182,   110,   111,   112,
     113,   114,   115,   116,   117,   118,    32,   133,   -24,   125,
     119,   166,   134,    10,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   158,     9,    46,    55,   119,    10,    11,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   162,
      19,    71,   159,   119,    20,    21,   110,   111,   112,   113,
     114,   115,   116,   117,   118,    41,    90,    42,   163,   119,
     127,    25,    73,    74,    75,   101,    28,    73,    74,    75,
      76,    97,    91,   121,    65,    76,    77,   126,    78,   128,
     107,    77,   123,    78,    73,    74,    75,   136,   132,    73,
      74,    75,    76,   150,   157,   161,   179,    76,    77,   164,
      78,    87,    88,    77,   139,    78,    73,    74,    75,   145,
      18,    73,    74,    75,    76,    25,    36,   108,   168,    76,
      77,     0,    78,     0,     0,    77,   151,    78,    73,    74,
      75,   167,     0,    73,    74,    75,    76,    73,    74,    75,
       0,    76,    77,     0,    78,    76,     0,    77,     0,    78,
       0,    77,   109,    78,   110,   111,   112,   113,   114,   115,
     116,   117,   118,     0,     0,     0,     0,   119,   153,   110,
     111,   112,   113,   114,   115,   116,   117,   118,     0,     0,
       0,     0,   119,   110,   111,   112,   113,   114,   115,   116,
     117,   118,     0,     0,     0,   131,   119,   110,   111,   112,
     113,   114,   115,   116,   117,   118,     0,     0,     0,   156,
     119,   110,   111,   112,   113,   114,   115,   116,   117,   118,
       0,     0,     0,   160,   119,   110,   111,   112,   113,   114,
     115,   116,   117,   118,     0,     0,     0,     0,   119,   111,
     112,   113,   114,   115,   116,     0,   118,     0,     0,     0,
       0,   119,   111,   112,   113,   114,   115,     0,     0,   118,
     112,   113,   114,   115,   119,     0,   118,     0,   114,   115,
       0,   119,   118,     0,     0,     0,     0,   119
};

static const yytype_int16 yycheck[] =
{
      76,    77,    78,    79,     1,    43,     0,     1,     1,     7,
       0,    49,    88,    89,    65,     1,     6,     5,     0,     5,
      71,    97,     1,    21,    18,    18,    23,   103,   104,   105,
     106,    25,    25,     1,   110,   111,   112,   113,   114,   115,
     116,   117,    32,   119,     1,    24,     3,     4,     5,    87,
      18,     7,    20,    91,    11,     1,    18,    25,     6,     7,
      17,     1,    19,    25,     1,    21,    23,    24,     6,    26,
      27,     1,    29,    21,    20,    65,     1,   153,     3,     4,
       5,    71,    22,    20,    23,     6,    11,     1,    18,     3,
       4,     5,    17,     6,    19,    25,     1,    11,    23,    23,
       5,    26,    27,    17,    29,    19,     7,     6,     3,    23,
       1,    24,    26,    27,     1,    29,     3,     4,     5,     1,
       6,     7,     8,    24,    11,    24,    27,     1,    19,    28,
      17,     5,    19,    22,    24,    21,    23,    19,     7,    26,
      27,     8,    29,   156,   157,   158,   159,   160,   161,   162,
     163,    20,    35,     1,    21,     1,    16,     5,     1,     5,
       1,    21,    45,     6,     7,   178,   179,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    19,     1,    21,     1,
      21,    22,     6,     5,     8,     9,    10,    11,    12,    13,
      14,    15,    16,     1,     1,    20,    22,    21,     5,     6,
       8,     9,    10,    11,    12,    13,    14,    15,    16,     1,
       1,     7,    20,    21,     5,     6,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     1,     6,     3,    20,    21,
       1,    21,     3,     4,     5,     1,    21,     3,     4,     5,
      11,    19,     7,    87,     7,    11,    17,    91,    19,    20,
      24,    17,     1,    19,     3,     4,     5,     1,     6,     3,
       4,     5,    11,     5,    20,    20,    28,    11,    17,    22,
      19,     7,     8,    17,     1,    19,     3,     4,     5,     1,
       6,     3,     4,     5,    11,    21,    23,    84,   153,    11,
      17,    -1,    19,    -1,    -1,    17,     1,    19,     3,     4,
       5,     1,    -1,     3,     4,     5,    11,     3,     4,     5,
      -1,    11,    17,    -1,    19,    11,    -1,    17,    -1,    19,
      -1,    17,     6,    19,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    21,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    21,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    20,    21,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    20,
      21,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    20,    21,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    21,     9,
      10,    11,    12,    13,    14,    -1,    16,    -1,    -1,    -1,
      -1,    21,     9,    10,    11,    12,    13,    -1,    -1,    16,
      10,    11,    12,    13,    21,    -1,    16,    -1,    12,    13,
      -1,    21,    16,    -1,    -1,    -1,    -1,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    18,    25,    32,    33,    34,    36,    37,     1,
       5,     6,    35,    40,     5,    38,    39,     0,    33,     1,
       5,     6,    35,    41,     7,    21,     6,     7,    21,    23,
       6,     1,    19,     6,     1,    23,    44,    35,     3,     1,
      35,     1,     3,    36,    47,    48,    20,     1,    20,    36,
      42,    43,    24,    47,    22,    22,     1,    22,     1,    40,
      49,    50,     1,    24,    47,     7,    20,     1,    40,     1,
      20,     7,     1,     3,     4,     5,    11,    17,    19,    26,
      27,    29,    44,    45,    46,    51,     6,     7,     8,     8,
       6,     7,     1,    42,     1,    42,     6,    19,    51,    51,
      51,     1,    51,     1,    19,     1,    19,    24,    45,     6,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    21,
       1,    49,    51,     1,    51,     1,    49,     1,    20,    51,
      52,    20,     6,     1,     6,    51,     1,    51,    51,     1,
      51,    51,    51,    51,    51,     1,    51,    51,    51,    51,
       5,     1,    51,     7,     1,    20,    20,    20,     1,    20,
      20,    20,     1,    20,    22,     1,    22,     1,    52,    46,
      46,    46,     1,    46,    46,    46,    46,    46,    28,    28,
      46,     1,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      34,    34,    35,    35,    35,    35,    36,    36,    37,    37,
      37,    38,    38,    39,    40,    40,    40,    40,    40,    41,
      41,    41,    41,    41,    42,    42,    42,    42,    43,    43,
      44,    44,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    47,    47,    48,    48,    49,    49,    49,    49,
      50,    50,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    52,    52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     3,
       2,     3,     1,     3,     3,     3,     1,     1,     5,     2,
       5,     1,     0,     1,     1,     4,     4,     4,     4,     4,
       3,     4,     4,     3,     3,     1,     3,     3,     2,     2,
       4,     2,     2,     0,     2,     1,     3,     5,     7,     5,
       2,     3,     3,     5,     5,     5,     5,     5,     5,     7,
       5,     7,     2,     0,     3,     3,     1,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     4,     3,     4,     3,     1,
       1,     1,     3,     4,     3,     4,     4,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 68 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Program", "", true); Insert_Child((yyval.tree_node),(yyvsp[0].tree_node)); root=(yyval.tree_node);}
#line 1417 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 70 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDefList", "", true); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node));Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1423 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 71 "syntax.y" /* yacc.c:1646  */
    { (yyval.tree_node)=NULL; }
#line 1429 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 73 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDef", "", true); Insert_Child((yyval.tree_node),(yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1435 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 74 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDef", "", true); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1441 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 75 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDef", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1447 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 77 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDef", "", true); char str[MAXLENGTH] = "Wrong with Specifier"; syn_error=true; yyerror(str);}
#line 1453 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 78 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDef", "", true); char str[MAXLENGTH] = "Wrong ExtDecList between Specifier and \";\""; syn_error=true; yyerror(str);}
#line 1459 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 79 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDef", "", true); char str[MAXLENGTH] = "Unnecessary \";\""; syn_error=true; yyerror(str);}
#line 1465 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 80 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDef", "", true); char str[MAXLENGTH] = "Missing CompSt"; syn_error=true; yyerror(str);}
#line 1471 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 82 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDecList", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1477 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 83 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDecList", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1483 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 85 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDecList", "", true); char str[MAXLENGTH] = "Unnecessary \",\""; syn_error=true; yyerror(str);}
#line 1489 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 86 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ExtDecList", "", true); char str[MAXLENGTH] = "Unnecessary \",\", maybe change to \";\""; syn_error=true; yyerror(str);}
#line 1495 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 90 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Specifier", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1501 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 91 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Specifier", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1507 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 93 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("StructSpecifier", "", true); Insert_Child((yyval.tree_node),(yyvsp[-4].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-3].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1513 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 94 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("StructSpecifier", "", true); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1519 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 96 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("StructSpecifier", "", true); char str[MAXLENGTH] = "Missing \"}\""; syn_error=true; yyerror(str);}
#line 1525 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 98 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("OptTag", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1531 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 99 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=NULL;}
#line 1537 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 101 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Tag", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1543 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 105 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("VarDec", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1549 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 106 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("VarDec", "", true); Insert_Child((yyval.tree_node), (yyvsp[-3].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1555 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 108 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("VarDec", "", true); char str[MAXLENGTH] = "Wrong VarDec"; syn_error=true; yyerror(str);}
#line 1561 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 109 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("VarDec", "", true); char str[MAXLENGTH] = "Complicated INT between \"[\" and \"]\""; syn_error=true; yyerror(str);}
#line 1567 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 110 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("VarDec", "", true); char str[MAXLENGTH] = "Missing \"]\""; syn_error=true; yyerror(str);}
#line 1573 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 112 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("FunDec", "", true); Insert_Child((yyval.tree_node), (yyvsp[-3].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1579 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 113 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("FunDec", "", true); Insert_Child((yyval.tree_node),(yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1585 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 115 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("FunDec", "", true); char str[MAXLENGTH] = "Complicated VarList between \"(\" and \")\""; syn_error=true; yyerror(str);}
#line 1591 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 116 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("FunDec", "", true); char str[MAXLENGTH] = "Missing \")\""; syn_error=true; yyerror(str);}
#line 1597 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 117 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("FunDec", "", true); char str[MAXLENGTH] = "Missing \"(\""; syn_error=true; yyerror(str);}
#line 1603 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 119 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("VarList", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1609 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 120 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("VarList", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1615 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 122 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("VarList", "", true); char str[MAXLENGTH] = "Wrong \",\""; syn_error=true; yyerror(str);}
#line 1621 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 123 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("VarList", "", true); char str[MAXLENGTH] = "Wrong ParamDec"; syn_error=true; yyerror(str);}
#line 1627 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 125 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ParamDec", "", true); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1633 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 127 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("ParamDec", "", true); char str[MAXLENGTH] = "Wrong VarDec"; syn_error=true; yyerror(str);}
#line 1639 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 131 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("CompSt", "", true); Insert_Child((yyval.tree_node), (yyvsp[-3].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node),(yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1645 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 132 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("CompSt", "", true); char str[MAXLENGTH] = "Missing \";\""; syn_error=true; yyerror(str);}
#line 1651 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 134 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("StmtList", "", true); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1657 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 135 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=NULL;}
#line 1663 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 137 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1669 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 138 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1675 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 139 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node),(yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1681 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 140 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); Insert_Child((yyval.tree_node), (yyvsp[-4].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-3].tree_node));Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1687 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 141 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); Insert_Child((yyval.tree_node), (yyvsp[-6].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-5].tree_node)); Insert_Child((yyval.tree_node),(yyvsp[-4].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-3].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1693 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 142 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); Insert_Child((yyval.tree_node), (yyvsp[-4].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-3].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1699 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 144 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Expression"; syn_error=true; /*yyerror(str);*/}
#line 1705 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 145 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Exp"; syn_error=true; yyerror(str);}
#line 1711 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 146 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \";\""; syn_error=true; yyerror(str);}
#line 1717 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 147 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Exp"; syn_error=true; yyerror(str);}
#line 1723 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 148 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \"(\""; syn_error=true; yyerror(str);}
#line 1729 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 149 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \")\""; syn_error=true; yyerror(str);}
#line 1735 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 150 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \"(\""; syn_error=true; yyerror(str);}
#line 1741 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 151 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Exp"; syn_error=true; yyerror(str);}
#line 1747 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 152 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \")\""; syn_error=true; yyerror(str);}
#line 1753 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 153 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Missing \";\""; syn_error=true; yyerror(str);}
#line 1759 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 154 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Stmt"; syn_error=true; yyerror(str);}
#line 1765 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 155 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Stmt", "", true); char str[MAXLENGTH] = "Wrong Stmt"; syn_error=true; yyerror(str);}
#line 1771 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 159 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("DefList", "", true); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1777 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 160 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=NULL;}
#line 1783 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 162 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Def", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1789 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 164 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Def", "", true); char str[MAXLENGTH] = "Wrong DefList"; syn_error=true; yyerror(str);}
#line 1795 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 166 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("DecList", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1801 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 167 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("DecList", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1807 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 169 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("DecList", "", true); char str[MAXLENGTH] = "Wrong Declaration"; syn_error=true; yyerror(str);}
#line 1813 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 170 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("DecList", "", true); char str[MAXLENGTH] = "Unnecessary \",\",maybe change to \";\""; syn_error=true; yyerror(str);}
#line 1819 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 172 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Dec", "", true); Insert_Child((yyval.tree_node),(yyvsp[0].tree_node)); }
#line 1825 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 173 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Dec", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1831 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 175 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Dec", "", true); char str[MAXLENGTH] = "Wrong VarDec"; syn_error=true; yyerror(str);}
#line 1837 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 176 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Dec", "", true); char str[MAXLENGTH] = "COmplicated \"=\""; syn_error=true; yyerror(str);}
#line 1843 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 180 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true ); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1849 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 181 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1855 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 182 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1861 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 183 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1867 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 184 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1873 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 185 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1879 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 186 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1885 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 187 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1891 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 188 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1897 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 189 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1903 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 190 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1909 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 191 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-3].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1915 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 192 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1921 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 193 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-3].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1927 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 194 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1933 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 195 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1939 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 196 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1945 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 197 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node));}
#line 1951 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 199 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); char str[MAXLENGTH] = "Syntax Errors"; syn_error=true; yyerror(str);}
#line 1957 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 200 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); char str[MAXLENGTH] = "Missing \")\""; syn_error=true; yyerror(str);}
#line 1963 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 201 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); char str[MAXLENGTH] = "Missing \")\""; syn_error=true; yyerror(str);}
#line 1969 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 202 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); char str[MAXLENGTH] = "Wrong Exp"; syn_error=true; yyerror(str);}
#line 1975 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 203 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Exp", "", true); char str[MAXLENGTH] = "Missing \"]\""; syn_error=true; yyerror(str);}
#line 1981 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 205 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Args", "", true); Insert_Child((yyval.tree_node), (yyvsp[-2].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[-1].tree_node)); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1987 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 206 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Args", "", true); Insert_Child((yyval.tree_node), (yyvsp[0].tree_node)); }
#line 1993 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 208 "syntax.y" /* yacc.c:1646  */
    {(yyval.tree_node)=Node_Initializer("Args", "", true); char str[MAXLENGTH] = "Wrong Args"; syn_error=true; yyerror(str);}
#line 1999 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2003 "syntax.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 210 "syntax.y" /* yacc.c:1906  */


yyerror(char *msg){
        
    if(syn_error==true && strcmp(msg,"syntax error") != 0){
        if(last_syn_error_lineno==-1){
            last_syn_error_lineno = yylineno;
            fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
        }
        else{
            if(last_syn_error_lineno != yylineno)
                fprintf(stderr, "Error type B at line %d: %s\n", yylineno, msg);
        }
    }
    else if (syn_error==false){
        fprintf(stderr, "Error type B at line %d: %s\n", yylineno, "Syntax Errors");
    }

}
