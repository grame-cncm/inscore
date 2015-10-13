/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         ITLparse
#define yylex           ITLlex
#define yyerror         ITLerror
#define yydebug         ITLdebug
#define yynerrs         ITLnerrs


/* Copy the first part of user declarations.  */
#line 2 "ITL.y" /* yacc.c:339  */


#include <iostream>
#include <sstream>
#include <string>

#include "ITLparser.h"
#include "IMessage.h"
#include "IExpression.h"
#include "IMessageStream.h"
#include "ITLparse.hpp"



#line 87 "ITLparse.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "ITLparse.hpp".  */
#ifndef YY_ITL_ITLPARSE_HPP_INCLUDED
# define YY_ITL_ITLPARSE_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int ITLdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    UINT = 259,
    FLOAT = 260,
    IDENTIFIER = 261,
    EQUAL = 262,
    REGEXP = 263,
    PATHSEP = 264,
    FILEPATH = 265,
    STRING = 266,
    QUOTEDSTRING = 267,
    WATCH = 268,
    EVAL = 269,
    ERR = 270,
    ENDEXPR = 271,
    ENDSCRIPT = 272,
    VARSTART = 273,
    LEFTPAR = 274,
    RIGHTPAR = 275,
    COLON = 276,
    COMMA = 277,
    POINT = 278,
    HOSTNAME = 279,
    IPNUM = 280,
    EXPRESSIONSTART = 281,
    EXPRESSIONEND = 282,
    AMPERSAND = 283,
    LUASCRIPT = 284,
    JSCRIPT = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 27 "ITL.y" /* yacc.c:355  */

	int		num;
	float	real;
	std::string* str;
	inscore::ITLparser::address*	addr;
	inscore::Sbaseparam *			p;
	inscore::IMessage::argslist*	plist;
	inscore::IMessage::TUrl*		url;
	inscore::SIMessage*				msg;
    inscore::SIMessageList*			msgList;

#line 170 "ITLparse.cpp" /* yacc.c:355  */
};
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



int ITLparse (inscore::ITLparser* context);

#endif /* !YY_ITL_ITLPARSE_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 71 "ITL.y" /* yacc.c:358  */


#include <iostream>
#include <sstream>
#include <string>

#include "ITLparser.h"
#include "ITLparse.hpp"

#ifndef NO_OSCSTREAM
#include "ITLError.h"
#endif

#define VARERROR(str, var)	{ VARerror(&yyloc, context, str, var); YYABORT; }

//#define ERROR_CB() [&yyloc, &context](const char *s) -> void {yyerror(&yyloc, context, s);}
#define HANDLE_READER_ERROR() if(context->fReader.hasFailed()){ yyerror(&yyloc, context, context->fReader.errorlog().c_str()); YYABORT; }

typedef void * yyscan_t;

int VARerror(YYLTYPE* locp, inscore::ITLparser* context, const char*s, const char* var);
int yyerror (const YYLTYPE* locp, inscore::ITLparser* context, const char*s);
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
int lineno(inscore::ITLparser* context);

#define scanner context->fScanner

using namespace std;

//namespace inscore
//{


#line 231 "ITLparse.cpp" /* yacc.c:358  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  98

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
static const yytype_uint16 yyrline[] =
{
       0,   110,   110,   111,   117,   118,   119,   125,   131,   134,
     143,   144,   145,   146,   150,   153,   155,   160,   163,   168,
     169,   170,   173,   174,   177,   180,   181,   182,   185,   186,
     189,   190,   193,   194,   195,   201,   205,   206,   212,   213,
     214,   215,   218,   221,   226,   232,   233,   234,   235,   236,
     237,   238,   244,   245,   248,   249,   254,   255,   261,   264,
     267,   268,   269,   270,   271,   272
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "UINT", "FLOAT", "IDENTIFIER",
  "EQUAL", "REGEXP", "PATHSEP", "FILEPATH", "STRING", "QUOTEDSTRING",
  "WATCH", "EVAL", "ERR", "ENDEXPR", "ENDSCRIPT", "VARSTART", "LEFTPAR",
  "RIGHTPAR", "COLON", "COMMA", "POINT", "HOSTNAME", "IPNUM",
  "EXPRESSIONSTART", "EXPRESSIONEND", "AMPERSAND", "LUASCRIPT", "JSCRIPT",
  "$accept", "start", "expr", "script", "message", "messagelist",
  "address", "oscaddress", "relativeaddress", "oscpath", "urlprefix",
  "hostname", "identifier", "eval", "watchparams", "params", "watchmethod",
  "variable", "param", "variabledecl", "varname", "number", "expression",
  "operatorid", "expArg", YY_NULLPTR
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

#define YYPACT_NINF -57

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-57)))

#define YYTABLE_NINF -56

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       0,   -57,    52,   -57,    25,    36,    30,   -57,   -57,    44,
     -57,   -57,    31,    75,    25,   -57,   -57,    25,    69,    38,
      39,   -57,   -57,   -57,     9,   -57,   -57,    25,    62,   -57,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,    13,    89,
      51,   -57,   -57,     3,    26,   103,   103,   -57,   -57,   -57,
     -57,   -57,    25,    67,    53,   -57,   131,   -57,   -57,   -57,
      89,   -57,   -57,   -57,    80,   -57,   156,    89,   -57,    89,
     -57,   -57,   -57,   103,   -57,   -57,    89,   103,    66,   -57,
      89,   -57,   -57,    25,   -57,   -57,   -57,   156,    96,    97,
     104,   -57,   -57,    64,   -57,   -57,   -57,   -57
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    54,     0,     7,     0,    30,     0,     8,     9,     0,
       2,     6,     0,    10,    19,    20,    22,     0,     0,     0,
       0,    32,    34,    26,     0,    33,    25,    24,     0,     1,
       3,     4,    57,    56,    46,    48,    42,    35,     0,     0,
       0,    51,    47,     0,    12,    11,    36,    39,    38,    45,
      49,    23,    21,     0,     0,     5,     0,    55,    27,    29,
       0,    43,    30,    17,     0,    59,     0,     0,    15,     0,
      16,    40,    41,    37,    28,    31,     0,    52,     0,    50,
       0,    61,    60,    63,    62,    64,    65,     0,     0,     0,
       0,    44,    18,     0,    14,    13,    50,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -57,   -57,    86,     4,     2,   -49,   -57,    -3,   -57,   -11,
     -57,   -57,    -2,   -57,   -57,    -4,   -57,   -38,   -37,   -57,
     -12,   -57,   -56,   -57,    10
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     9,    10,    41,    63,    64,    13,    14,    15,    16,
      17,    18,    42,    43,    44,    45,    46,    47,    48,    19,
      20,    49,    50,    66,    87
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      26,    27,    12,    51,    11,    68,     1,    71,    72,     2,
      86,    12,    58,    11,    52,     1,    51,     3,    88,     1,
      89,    38,    67,     4,     5,     6,    61,    90,    85,     7,
       8,    86,    60,    57,     2,    71,    72,    57,    65,    71,
      72,    51,    73,   -55,    29,    69,    56,    31,    70,    85,
       1,    28,    77,     2,    55,     7,     8,    21,    21,    22,
      22,     3,    78,    83,    84,    23,    59,     4,     5,     6,
      24,    74,    51,     7,     8,    25,    25,    75,    32,    33,
      34,    21,    92,    22,    83,    84,    91,    35,    36,    37,
      53,    97,    54,    38,    39,    30,     0,    93,     2,    25,
      79,    40,    80,     0,     7,     8,    32,    33,    34,    21,
       0,    22,     4,    62,     6,    35,    94,    95,    80,    80,
       0,    38,    39,     0,    96,     0,    80,    25,     0,    40,
       0,     0,     7,     8,    32,    33,    34,    21,     0,    22,
       0,     0,     0,    35,     0,     0,     0,     0,     0,    38,
      76,     0,     0,     0,     0,    25,     0,    40,     0,     0,
       7,     8,    21,     0,    22,     2,    81,     0,    82,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
      25,     0,    40
};

static const yytype_int8 yycheck[] =
{
       2,     4,     0,    14,     0,    43,     6,    45,    45,     9,
      66,     9,    24,     9,    17,     6,    27,    17,    67,     6,
      69,    18,    19,    23,    24,    25,    38,    76,    66,    29,
      30,    87,    19,    24,     9,    73,    73,    24,    40,    77,
      77,    52,    46,     7,     0,    19,     7,    16,    44,    87,
       6,    21,    56,     9,    16,    29,    30,     6,     6,     8,
       8,    17,    60,    66,    66,    13,     4,    23,    24,    25,
      18,     4,    83,    29,    30,    24,    24,    24,     3,     4,
       5,     6,    80,     8,    87,    87,    20,    12,    13,    14,
      21,    27,    23,    18,    19,     9,    -1,    87,     9,    24,
      20,    26,    22,    -1,    29,    30,     3,     4,     5,     6,
      -1,     8,    23,    24,    25,    12,    20,    20,    22,    22,
      -1,    18,    19,    -1,    20,    -1,    22,    24,    -1,    26,
      -1,    -1,    29,    30,     3,     4,     5,     6,    -1,     8,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    18,
      19,    -1,    -1,    -1,    -1,    24,    -1,    26,    -1,    -1,
      29,    30,     6,    -1,     8,     9,    10,    -1,    12,    -1,
      -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    26
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     9,    17,    23,    24,    25,    29,    30,    32,
      33,    34,    35,    37,    38,    39,    40,    41,    42,    50,
      51,     6,     8,    13,    18,    24,    43,    38,    21,     0,
      33,    16,     3,     4,     5,    12,    13,    14,    18,    19,
      26,    34,    43,    44,    45,    46,    47,    48,    49,    52,
      53,    40,    38,    21,    23,    16,     7,    24,    51,     4,
      19,    51,    24,    35,    36,    43,    54,    19,    48,    19,
      34,    48,    49,    46,     4,    24,    19,    46,    35,    20,
      22,    10,    12,    38,    43,    48,    53,    55,    36,    36,
      36,    20,    35,    55,    20,    20,    20,    27
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    32,    33,    33,    33,    33,    34,    34,
      35,    35,    35,    35,    35,    35,    35,    36,    36,    37,
      37,    37,    38,    38,    39,    40,    40,    40,    41,    41,
      42,    42,    43,    43,    43,    44,    45,    45,    46,    46,
      46,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    50,    50,    51,    51,    52,    52,    53,    54,
      55,    55,    55,    55,    55,    55
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     1,     1,     1,     1,
       1,     2,     2,     5,     5,     3,     3,     1,     3,     1,
       1,     2,     1,     2,     2,     2,     2,     3,     3,     3,
       1,     3,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     1,     2,     4,     1,     1,     1,     1,     1,
       3,     1,     3,     5,     1,     1,     1,     1,     5,     1,
       1,     1,     1,     1,     1,     1
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
      yyerror (&yylloc, context, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, context); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, inscore::ITLparser* context)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (context);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, inscore::ITLparser* context)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, context);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, inscore::ITLparser* context)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , context);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, context); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, inscore::ITLparser* context)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (context);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (inscore::ITLparser* context)
{
/* The lookahead symbol.  */
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
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 117 "ITL.y" /* yacc.c:1646  */
    { context->fReader.add(*(yyvsp[-1].msg)); delete (yyvsp[-1].msg); }
#line 1498 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 118 "ITL.y" /* yacc.c:1646  */
    { delete (yyvsp[-1].str); }
#line 1504 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 119 "ITL.y" /* yacc.c:1646  */
    {	if (*(yyvsp[0].msgList)) {
										for (unsigned int i=0; i < (*(yyvsp[0].msgList))->list().size(); i++)
											context->fReader.add((*(yyvsp[0].msgList))->list()[i]);
									}
									delete (yyvsp[0].msgList);
								}
#line 1515 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 125 "ITL.y" /* yacc.c:1646  */
    { YYACCEPT; }
#line 1521 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 131 "ITL.y" /* yacc.c:1646  */
    {	(yyval.msgList) = new inscore::SIMessageList (inscore::IMessageList::create());
									*(yyval.msgList) = context->fReader.luaEval(context->fText.c_str());
								}
#line 1529 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 134 "ITL.y" /* yacc.c:1646  */
    {	(yyval.msgList) = new inscore::SIMessageList (inscore::IMessageList::create());
									*(yyval.msgList) = context->fReader.jsEval(context->fText.c_str(), yylloc.last_line);
								}
#line 1537 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 143 "ITL.y" /* yacc.c:1646  */
    { (yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[0].addr)->fOsc)); (*(yyval.msg))->setUrl((yyvsp[0].addr)->fUrl); delete (yyvsp[0].addr); }
#line 1543 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 144 "ITL.y" /* yacc.c:1646  */
    { (yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[-1].addr)->fOsc, *(yyvsp[0].plist), (yyvsp[-1].addr)->fUrl)); delete (yyvsp[-1].addr); delete (yyvsp[0].plist); }
#line 1549 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 145 "ITL.y" /* yacc.c:1646  */
    { (yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[-1].addr)->fOsc, *(yyvsp[0].plist), (yyvsp[-1].addr)->fUrl)); delete (yyvsp[-1].addr); delete (yyvsp[0].plist); }
#line 1555 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 147 "ITL.y" /* yacc.c:1646  */
    {	(yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[-4].addr)->fOsc, *(yyvsp[-3].plist), (yyvsp[-4].addr)->fUrl));
											(*(yyval.msg))->add(*(yyvsp[-1].msgList));
											delete (yyvsp[-4].addr); delete (yyvsp[-3].plist); delete (yyvsp[-1].msgList); }
#line 1563 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 151 "ITL.y" /* yacc.c:1646  */
    {	(yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[-4].addr)->fOsc, *(yyvsp[-3].plist), (yyvsp[-4].addr)->fUrl));
											(*(yyval.msg))->add(*(yyvsp[-1].msgList)); delete (yyvsp[-4].addr); delete (yyvsp[-3].plist); delete (yyvsp[-1].msgList); }
#line 1570 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 153 "ITL.y" /* yacc.c:1646  */
    {	(yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[-2].addr)->fOsc, *(yyvsp[-1].plist), (yyvsp[-2].addr)->fUrl));
											(*(yyval.msg))->add(*(yyvsp[0].plist)); delete (yyvsp[-2].addr); delete (yyvsp[-1].plist); delete (yyvsp[0].plist); }
#line 1577 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 155 "ITL.y" /* yacc.c:1646  */
    {	(yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[-2].addr)->fOsc, *(yyvsp[-1].plist), (yyvsp[-2].addr)->fUrl));
											if (*(yyvsp[0].msgList)) (*(yyval.msg))->add(*(yyvsp[0].msgList));
											delete (yyvsp[-2].addr); delete (yyvsp[-1].plist); delete (yyvsp[0].msgList); }
#line 1585 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 160 "ITL.y" /* yacc.c:1646  */
    {	(yyval.msgList) = new inscore::SIMessageList (inscore::IMessageList::create());
											(*(yyval.msgList))->list().push_back(*(yyvsp[0].msg));
											delete (yyvsp[0].msg); }
#line 1593 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 163 "ITL.y" /* yacc.c:1646  */
    {	(yyval.msgList) = (yyvsp[-2].msgList); (*(yyval.msgList))->list().push_back(*(yyvsp[0].msg)); delete (yyvsp[0].msg); }
#line 1599 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 168 "ITL.y" /* yacc.c:1646  */
    { (yyval.addr) = new inscore::ITLparser::address (*(yyvsp[0].str)); delete (yyvsp[0].str);}
#line 1605 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 169 "ITL.y" /* yacc.c:1646  */
    { (yyval.addr) = new inscore::ITLparser::address (*(yyvsp[0].str)); delete (yyvsp[0].str);}
#line 1611 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 170 "ITL.y" /* yacc.c:1646  */
    { (yyval.addr) = new inscore::ITLparser::address (*(yyvsp[0].str), *(yyvsp[-1].url)); delete (yyvsp[-1].url); delete (yyvsp[0].str); }
#line 1617 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 173 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[0].str); }
#line 1623 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 174 "ITL.y" /* yacc.c:1646  */
    { *(yyvsp[-1].str) += *(yyvsp[0].str); (yyval.str) = (yyvsp[-1].str); delete (yyvsp[0].str); }
#line 1629 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 177 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = new string("." + *(yyvsp[0].str)); delete (yyvsp[0].str); }
#line 1635 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 180 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = new string("/" + *(yyvsp[0].str)); delete (yyvsp[0].str); }
#line 1641 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 181 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = new string("/" + context->fText); }
#line 1647 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 182 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = new string("/$" + *(yyvsp[0].str)); delete (yyvsp[0].str); }
#line 1653 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 185 "ITL.y" /* yacc.c:1646  */
    { (yyval.url) = new inscore::IMessage::TUrl((yyvsp[-2].str)->c_str(), context->fInt); delete (yyvsp[-2].str); }
#line 1659 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 186 "ITL.y" /* yacc.c:1646  */
    { (yyval.url) = new inscore::IMessage::TUrl(context->fText.c_str(), context->fInt); }
#line 1665 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 189 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = new string(context->fText); }
#line 1671 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 190 "ITL.y" /* yacc.c:1646  */
    { *(yyvsp[-2].str) += '.' + context->fText; (yyval.str)=(yyvsp[-2].str); }
#line 1677 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 193 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = new string(context->fText); }
#line 1683 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 194 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = new string(context->fText); }
#line 1689 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 195 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = new string(context->fText); }
#line 1695 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 201 "ITL.y" /* yacc.c:1646  */
    { (yyval.plist) = new inscore::IMessage::argslist; 
								  inscore::Sbaseparam * p = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText));
								  (yyval.plist)->push_back(*p); delete p; }
#line 1703 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 205 "ITL.y" /* yacc.c:1646  */
    { (yyval.plist) = new inscore::IMessage::argslist; (yyval.plist)->push_back(*(yyvsp[0].p)); delete (yyvsp[0].p); }
#line 1709 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 206 "ITL.y" /* yacc.c:1646  */
    { (yyval.plist) = new inscore::IMessage::argslist;
								  (yyval.plist)->push_back(*(yyvsp[-1].p));
								  (yyval.plist)->push_back((yyvsp[0].plist));
								  delete (yyvsp[-1].p); delete (yyvsp[0].plist);
								}
#line 1719 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 212 "ITL.y" /* yacc.c:1646  */
    { (yyval.plist) = new inscore::IMessage::argslist; (yyval.plist)->push_back(*(yyvsp[0].p)); delete (yyvsp[0].p); }
#line 1725 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 213 "ITL.y" /* yacc.c:1646  */
    { (yyval.plist) = (yyvsp[0].plist); }
#line 1731 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 214 "ITL.y" /* yacc.c:1646  */
    { (yyvsp[-1].plist)->push_back((yyvsp[0].plist));  (yyval.plist) = (yyvsp[-1].plist); delete (yyvsp[0].plist); }
#line 1737 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 215 "ITL.y" /* yacc.c:1646  */
    { (yyvsp[-1].plist)->push_back(*(yyvsp[0].p)); (yyval.plist) = (yyvsp[-1].plist); delete (yyvsp[0].p); }
#line 1743 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 218 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); }
#line 1749 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 221 "ITL.y" /* yacc.c:1646  */
    { (yyval.plist) = new inscore::IMessage::argslist;
								  std::string var = "$" + *(yyvsp[0].str);
								  (yyval.plist)->push_back (context->fReader.resolve((yyvsp[0].str)->c_str(), var.c_str()));
								  delete (yyvsp[0].str);
								}
#line 1759 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 226 "ITL.y" /* yacc.c:1646  */
    { (yyval.plist) = new inscore::IMessage::argslist;
								  (yyval.plist)->push_back (context->fReader.resolve(*(yyvsp[-1].msg)));
								  delete (yyvsp[-1].msg);
								}
#line 1768 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 232 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<int>((yyvsp[0].num))); }
#line 1774 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 233 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<float>(context->fFloat)); }
#line 1780 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 234 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); delete (yyvsp[0].str); }
#line 1786 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 235 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); }
#line 1792 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 236 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = (yyvsp[0].p);}
#line 1798 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 237 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = context->fReader.createParam(*(yyvsp[-1].msgList)); delete (yyvsp[-1].msgList); }
#line 1804 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 238 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = context->fReader.createParam(*(yyvsp[0].msgList)); delete (yyvsp[0].msgList); }
#line 1810 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 244 "ITL.y" /* yacc.c:1646  */
    { (yyval.str)=(yyvsp[-2].str); context->fReader.variable((yyvsp[-2].str)->c_str(), (yyvsp[0].plist)); delete (yyvsp[0].plist);}
#line 1816 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 245 "ITL.y" /* yacc.c:1646  */
    { (yyval.str)=(yyvsp[-4].str); context->fReader.variable((yyvsp[-4].str)->c_str(), (yyvsp[-1].msgList)); delete (yyvsp[-1].msgList);}
#line 1822 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 248 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = new string(context->fText); }
#line 1828 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 249 "ITL.y" /* yacc.c:1646  */
    { (yyval.str) = new string(context->fText); }
#line 1834 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 254 "ITL.y" /* yacc.c:1646  */
    { (yyval.num) = context->fInt; }
#line 1840 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 255 "ITL.y" /* yacc.c:1646  */
    { (yyval.num) = context->fInt; }
#line 1846 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 261 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = context->fReader.createExpr( (yyvsp[-3].str), (yyvsp[-2].p), (yyvsp[-1].p)); delete (yyvsp[-3].str); delete (yyvsp[-2].p); delete (yyvsp[-1].p);}
#line 1852 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 267 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = context->fReader.createExprArg<std::string>((context->fText)); }
#line 1858 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 268 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = context->fReader.createExprArg<inscore::filepath>(context->fText); }
#line 1864 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 269 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = context->fReader.createExprArg<inscore::identifier>(context->fText); delete (yyvsp[0].str);}
#line 1870 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 270 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = context->fReader.createExprArg<inscore::oscaddress>((yyvsp[0].str));}
#line 1876 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 271 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = context->fReader.createExprArgFromVar((yyvsp[0].plist)); HANDLE_READER_ERROR()}
#line 1882 "ITLparse.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 272 "ITL.y" /* yacc.c:1646  */
    { (yyval.p) = context->fReader.createExprArgFromExpr((yyvsp[0].p)); delete (yyvsp[0].p); HANDLE_READER_ERROR()}
#line 1888 "ITLparse.cpp" /* yacc.c:1646  */
    break;


#line 1892 "ITLparse.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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
      yyerror (&yylloc, context, YY_("syntax error"));
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
        yyerror (&yylloc, context, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, &yylloc, context);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, context);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
  yyerror (&yylloc, context, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, context);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, context);
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
#line 275 "ITL.y" /* yacc.c:1906  */


//} // end namespace

namespace inscore 
{

SIMessageList ITLparser::parse()
{
	yyparse (this);
	return fReader.messages();
}
}

using namespace inscore;

int lineno (ITLparser* context)	
{ 
	YYLTYPE* loc = (YYLTYPE*)context->fScanner;
	return loc->last_line + context->fLine; 
}

int yyerror(const YYLTYPE* loc, ITLparser* context, const char*s) {
#ifdef NO_OSCSTREAM
	cerr << "error line: " << loc->last_line + context->fLine << " col: " << loc->first_column << ": " << s << endl;
#else
	ITLErr << "error line: " << loc->last_line + context->fLine << " col: " << loc->first_column << ": " << s << ITLEndl;
#endif
	return 0;
}

int VARerror(YYLTYPE* loc, ITLparser* context, const char*s, const char* var) {
#ifdef NO_OSCSTREAM
	cerr << "error line " << loc->last_line + context->fLine << ": " << s << var << endl;
#else
	ITLErr << "error line " << loc->last_line + context->fLine << ": " << s << var << ITLEndl;
#endif
	return 0;
}
