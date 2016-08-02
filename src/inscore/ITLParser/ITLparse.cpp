/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse ITLparse
#define yylex   ITLlex
#define yyerror ITLerror
#define yylval  ITLlval
#define yychar  ITLchar
#define yydebug ITLdebug
#define yynerrs ITLnerrs
#define yylloc ITLlloc

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     UINT = 259,
     FLOAT = 260,
     IDENTIFIER = 261,
     EQUAL = 262,
     REGEXP = 263,
     PATHSEP = 264,
     BACKPATH = 265,
     FILEPATH = 266,
     STRING = 267,
     EVAL = 268,
     ERR = 269,
     ENDEXPR = 270,
     ENDSCRIPT = 271,
     VARSTART = 272,
     VARIABLE = 273,
     LEFTPAR = 274,
     RIGHTPAR = 275,
     COLON = 276,
     COMMA = 277,
     POINT = 278,
     HOSTNAME = 279,
     IPNUM = 280,
     EXPRESSION = 281,
     LUASCRIPT = 282,
     JSCRIPT = 283,
     ADD = 284,
     SUB = 285,
     DIV = 286,
     MULT = 287,
     QUEST = 288,
     MIN = 289,
     MAX = 290,
     GREATER = 291,
     GREATEREQ = 292,
     LESS = 293,
     LESSEQ = 294,
     EQ = 295,
     MINUS = 296,
     NEG = 297,
     MODULO = 298,
     PREINC = 299,
     PREDEC = 300,
     POSTINC = 301,
     POSTDEC = 302
   };
#endif
/* Tokens.  */
#define INT 258
#define UINT 259
#define FLOAT 260
#define IDENTIFIER 261
#define EQUAL 262
#define REGEXP 263
#define PATHSEP 264
#define BACKPATH 265
#define FILEPATH 266
#define STRING 267
#define EVAL 268
#define ERR 269
#define ENDEXPR 270
#define ENDSCRIPT 271
#define VARSTART 272
#define VARIABLE 273
#define LEFTPAR 274
#define RIGHTPAR 275
#define COLON 276
#define COMMA 277
#define POINT 278
#define HOSTNAME 279
#define IPNUM 280
#define EXPRESSION 281
#define LUASCRIPT 282
#define JSCRIPT 283
#define ADD 284
#define SUB 285
#define DIV 286
#define MULT 287
#define QUEST 288
#define MIN 289
#define MAX 290
#define GREATER 291
#define GREATEREQ 292
#define LESS 293
#define LESSEQ 294
#define EQ 295
#define MINUS 296
#define NEG 297
#define MODULO 298
#define PREINC 299
#define PREDEC 300
#define POSTINC 301
#define POSTDEC 302




/* Copy the first part of user declarations.  */
#line 2 "ITL.y"


#include <iostream>
#include <sstream>
#include <string>

#include "ITLparser.h"
#include "IMessage.h"
#include "IMessageStream.h"
#include "ITLparse.hpp"




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 26 "ITL.y"
{
	int		num;
	float	real;
	std::string* str;
	inscore::ITLparser::address*	addr;
	inscore::Sbaseparam *			p;
	inscore::IMessage::argslist*	plist;
	inscore::IMessage::TUrl*		url;
	inscore::SIMessage*				msg;
    inscore::SIMessageList*			msgList;
}
/* Line 193 of yacc.c.  */
#line 224 "ITLparse.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */
#line 79 "ITL.y"


#include <iostream>
#include <sstream>
#include <string>

#include "ITLparser.h"
#include "ITLparse.hpp"

#ifndef NO_OSCSTREAM
#include "ITLError.h"
#endif

typedef void * yyscan_t;

//int VARerror(YYLTYPE* locp, inscore::ITLparser* context, const char*s, const char* var);
int yyerror (const YYLTYPE* locp, inscore::ITLparser* context, const char*s);
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
int lineno(inscore::ITLparser* context);

#define scanner context->fScanner

using namespace std;



/* Line 216 of yacc.c.  */
#line 274 "ITLparse.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   332

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    16,    18,    20,
      22,    24,    27,    33,    37,    39,    43,    45,    47,    49,
      51,    54,    56,    59,    62,    65,    69,    73,    77,    79,
      83,    85,    87,    89,    91,    93,    96,    98,   101,   104,
     107,   110,   115,   117,   119,   121,   123,   125,   129,   131,
     133,   135,   139,   143,   146,   150,   154,   158,   162,   167,
     172,   180,   183,   186,   189,   192,   194,   197,   201,   205,
     209,   213,   217,   221,   223,   225,   227,   229
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    -1,    49,    50,    -1,    52,    15,
      -1,    70,    15,    -1,    51,    -1,    16,    -1,    27,    -1,
      28,    -1,    55,    -1,    55,    63,    -1,    55,    62,    19,
      53,    20,    -1,    55,    62,    64,    -1,    52,    -1,    53,
      54,    52,    -1,    22,    -1,    21,    -1,    56,    -1,    57,
      -1,    59,    56,    -1,    58,    -1,    56,    58,    -1,    23,
      56,    -1,     9,    61,    -1,     9,    17,    71,    -1,    60,
      21,     4,    -1,    25,    21,     4,    -1,    24,    -1,    60,
      23,    24,    -1,     6,    -1,    24,    -1,     8,    -1,    13,
      -1,    66,    -1,    63,    66,    -1,    18,    -1,    18,    46,
      -1,    18,    47,    -1,    44,    18,    -1,    45,    18,    -1,
      17,    19,    52,    20,    -1,    72,    -1,     5,    -1,    61,
      -1,    12,    -1,    73,    -1,    19,    53,    20,    -1,    51,
      -1,    65,    -1,    64,    -1,    66,    29,    66,    -1,    66,
      30,    66,    -1,    41,    66,    -1,    66,    32,    66,    -1,
      66,    31,    66,    -1,    66,    43,    66,    -1,    19,    66,
      20,    -1,    34,    19,    67,    20,    -1,    35,    19,    68,
      20,    -1,    19,    69,    33,    66,    21,    66,    20,    -1,
      66,    66,    -1,    67,    66,    -1,    66,    66,    -1,    68,
      66,    -1,    66,    -1,    42,    66,    -1,    66,    40,    66,
      -1,    66,    36,    66,    -1,    66,    37,    66,    -1,    66,
      38,    66,    -1,    66,    39,    66,    -1,    71,     7,    63,
      -1,     6,    -1,    24,    -1,     4,    -1,     3,    -1,    26,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   110,   110,   111,   117,   118,   119,   125,   131,   134,
     143,   144,   145,   148,   152,   155,   157,   158,   163,   164,
     165,   168,   169,   172,   175,   176,   179,   180,   183,   184,
     187,   188,   189,   195,   206,   207,   210,   212,   215,   218,
     221,   224,   230,   231,   232,   233,   234,   235,   236,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   255,   256,   259,   260,   263,   264,   265,   266,   267,
     268,   269,   274,   277,   278,   283,   284,   290
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "UINT", "FLOAT", "IDENTIFIER",
  "EQUAL", "REGEXP", "PATHSEP", "BACKPATH", "FILEPATH", "STRING", "EVAL",
  "ERR", "ENDEXPR", "ENDSCRIPT", "VARSTART", "VARIABLE", "LEFTPAR",
  "RIGHTPAR", "COLON", "COMMA", "POINT", "HOSTNAME", "IPNUM", "EXPRESSION",
  "LUASCRIPT", "JSCRIPT", "ADD", "SUB", "DIV", "MULT", "QUEST", "MIN",
  "MAX", "GREATER", "GREATEREQ", "LESS", "LESSEQ", "EQ", "MINUS", "NEG",
  "MODULO", "PREINC", "PREDEC", "POSTINC", "POSTDEC", "$accept", "start",
  "expr", "script", "message", "messagelist", "messagelistseparator",
  "address", "oscaddress", "relativeaddress", "oscpath", "urlprefix",
  "hostname", "identifier", "eval", "params", "variable", "param",
  "mathexpr", "mathmin", "mathmax", "mathbool", "variabledecl", "varname",
  "number", "expression", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    50,    50,    51,    51,
      52,    52,    52,    52,    53,    53,    54,    54,    55,    55,
      55,    56,    56,    57,    58,    58,    59,    59,    60,    60,
      61,    61,    61,    62,    63,    63,    64,    64,    64,    64,
      64,    64,    65,    65,    65,    65,    65,    65,    65,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    67,    68,    68,    69,    69,    69,    69,    69,
      69,    69,    70,    71,    71,    72,    72,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     1,     1,     1,     1,
       1,     2,     5,     3,     1,     3,     1,     1,     1,     1,
       2,     1,     2,     2,     2,     3,     3,     3,     1,     3,
       1,     1,     1,     1,     1,     2,     1,     2,     2,     2,
       2,     4,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     3,     2,     3,     3,     3,     3,     4,     4,
       7,     2,     2,     2,     2,     1,     2,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    73,     0,     7,     0,    28,     0,     8,     9,     0,
       2,     6,     0,    10,    18,    19,    21,     0,     0,     0,
       0,    30,    32,     0,    31,    24,    23,     0,     1,     3,
       4,    76,    75,    43,    45,    33,     0,    36,     0,    77,
       0,     0,     0,     0,     0,    48,    44,     0,    11,    50,
      49,    34,    42,    46,    22,    20,     0,     0,     5,     0,
      74,    25,    27,     0,    37,    38,    31,     0,    14,     0,
      65,     0,     0,     0,    53,    39,    40,     0,    13,    35,
       0,     0,     0,     0,     0,    26,    29,    72,    28,     0,
      66,    47,    17,    16,     0,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    55,
      54,    56,    41,    15,    68,    69,    70,    71,    67,     0,
      61,    58,    62,    63,    59,    64,    12,     0,     0,    60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     9,    10,    45,    12,    69,    94,    13,    14,    15,
      16,    17,    18,    46,    47,    48,    49,    50,    51,   103,
     105,    71,    19,    20,    52,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -39
static const yytype_int16 yypact[] =
{
     300,   -39,    24,   -39,     0,    20,   -18,   -39,   -39,   277,
     -39,   -39,    22,   152,     0,   -39,   -39,     0,    10,    38,
      75,   -39,   -39,    -4,   -39,   -39,     0,    69,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,    68,    29,   109,   -39,
      72,    80,   254,    70,    88,   -39,   -39,    -6,   254,   -39,
     -39,    73,   -39,   -39,   -39,     0,   104,    95,   -39,   254,
     -39,   -39,   -39,    27,   -39,   -39,    33,   254,   -39,    59,
     -15,    87,   254,   254,   -24,   -39,   -39,    27,   -39,    73,
     254,   254,   254,   254,   254,   -39,   -39,   254,   -39,   105,
      73,   -39,   -39,   -39,    27,   -39,   254,   254,   254,   254,
     254,   254,    66,   186,    66,   220,   102,   -24,   -24,   -39,
     -39,   -39,   -39,   -39,    73,    73,    73,    73,    73,   289,
      73,   -39,    73,    73,   -39,    73,   -39,   254,   283,   -39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -39,   -39,   120,    77,   -37,    53,   -39,   -39,    51,   -39,
      -8,   -39,   -39,   129,   -39,    79,    92,   -39,   -38,   -39,
     -39,   -39,   -39,   117,   -39,   -39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -75
static const yytype_int16 yytable[] =
{
      70,    68,     1,    27,    74,    95,    54,    82,    83,     2,
      79,    36,    37,    77,    80,    81,    82,    83,    54,    84,
      60,    96,    97,    98,    99,   100,    89,   -74,    84,    90,
      21,    56,    22,    57,   102,   104,     2,    30,    43,    44,
      68,    23,   107,   108,   109,   110,   111,    54,    24,    79,
       4,    88,     6,    58,   -28,    26,   -28,   113,   114,   115,
     116,   117,   118,   119,   120,   122,   123,   125,    55,    31,
      32,    33,    21,    62,    22,    64,    65,    11,    34,    91,
      92,    93,    59,    36,    37,    38,    11,    63,    75,   128,
      24,    72,    39,     7,     8,    80,    81,    82,    83,    73,
      40,    41,    80,    81,    82,    83,    76,    42,    85,    84,
      43,    44,    31,    32,    33,    21,    84,    22,     2,    86,
     101,    34,   126,    92,    93,   112,    36,    37,    38,    29,
     106,    25,     4,    66,     6,    39,     7,     8,    87,    78,
      61,     0,     0,    40,    41,     0,     0,     0,     0,     0,
      42,    67,     0,    43,    44,    31,    32,    33,    21,     0,
      22,     0,     0,     0,    34,    35,     0,     0,     0,    36,
      37,    38,     0,     0,     0,     0,    24,     0,    39,     7,
       8,     0,     0,     0,     0,     0,    40,    41,     0,    31,
      32,    33,    21,    42,    22,     0,    43,    44,    34,     0,
       0,     0,     0,    36,    37,    38,   121,     0,     0,     0,
      24,     0,    39,     7,     8,     0,     0,     0,     0,     0,
      40,    41,     0,    31,    32,    33,    21,    42,    22,     0,
      43,    44,    34,     0,     0,     0,     0,    36,    37,    38,
     124,     0,     0,     0,    24,     0,    39,     7,     8,     0,
       0,     0,     0,     0,    40,    41,     0,    31,    32,    33,
      21,    42,    22,     0,    43,    44,    34,     0,     0,     0,
       0,    36,    37,    38,     0,     0,     0,    28,    24,     0,
      39,     7,     8,     1,     0,     0,     2,     0,    40,    41,
       0,     0,     0,     3,     0,    42,     0,     0,    43,    44,
       4,     5,     6,   129,     7,     8,     1,     0,     0,     2,
     127,     0,    80,    81,    82,    83,     3,     0,    80,    81,
      82,    83,     0,     4,     5,     6,    84,     7,     8,     0,
       0,     0,    84
};

static const yytype_int8 yycheck[] =
{
      38,    38,     6,    21,    42,    20,    14,    31,    32,     9,
      48,    17,    18,    19,    29,    30,    31,    32,    26,    43,
      24,    36,    37,    38,    39,    40,    63,     7,    43,    67,
       6,    21,     8,    23,    72,    73,     9,    15,    44,    45,
      77,    17,    80,    81,    82,    83,    84,    55,    24,    87,
      23,    24,    25,    15,    21,     4,    23,    94,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,    17,     3,
       4,     5,     6,     4,     8,    46,    47,     0,    12,    20,
      21,    22,     7,    17,    18,    19,     9,    19,    18,   127,
      24,    19,    26,    27,    28,    29,    30,    31,    32,    19,
      34,    35,    29,    30,    31,    32,    18,    41,     4,    43,
      44,    45,     3,     4,     5,     6,    43,     8,     9,    24,
      33,    12,    20,    21,    22,    20,    17,    18,    19,     9,
      77,     2,    23,    24,    25,    26,    27,    28,    59,    47,
      23,    -1,    -1,    34,    35,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    44,    45,     3,     4,     5,     6,    -1,
       8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    17,
      18,    19,    -1,    -1,    -1,    -1,    24,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,     3,
       4,     5,     6,    41,     8,    -1,    44,    45,    12,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    -1,    -1,    -1,
      24,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      34,    35,    -1,     3,     4,     5,     6,    41,     8,    -1,
      44,    45,    12,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    -1,    -1,    -1,    24,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    34,    35,    -1,     3,     4,     5,
       6,    41,     8,    -1,    44,    45,    12,    -1,    -1,    -1,
      -1,    17,    18,    19,    -1,    -1,    -1,     0,    24,    -1,
      26,    27,    28,     6,    -1,    -1,     9,    -1,    34,    35,
      -1,    -1,    -1,    16,    -1,    41,    -1,    -1,    44,    45,
      23,    24,    25,    20,    27,    28,     6,    -1,    -1,     9,
      21,    -1,    29,    30,    31,    32,    16,    -1,    29,    30,
      31,    32,    -1,    23,    24,    25,    43,    27,    28,    -1,
      -1,    -1,    43
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     9,    16,    23,    24,    25,    27,    28,    49,
      50,    51,    52,    55,    56,    57,    58,    59,    60,    70,
      71,     6,     8,    17,    24,    61,    56,    21,     0,    50,
      15,     3,     4,     5,    12,    13,    17,    18,    19,    26,
      34,    35,    41,    44,    45,    51,    61,    62,    63,    64,
      65,    66,    72,    73,    58,    56,    21,    23,    15,     7,
      24,    71,     4,    19,    46,    47,    24,    42,    52,    53,
      66,    69,    19,    19,    66,    18,    18,    19,    64,    66,
      29,    30,    31,    32,    43,     4,    24,    63,    24,    52,
      66,    20,    21,    22,    54,    20,    36,    37,    38,    39,
      40,    33,    66,    67,    66,    68,    53,    66,    66,    66,
      66,    66,    20,    52,    66,    66,    66,    66,    66,    66,
      66,    20,    66,    66,    20,    66,    20,    21,    66,    20
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, context, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, scanner)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, context); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, inscore::ITLparser* context)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, context)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    inscore::ITLparser* context;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (context);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, inscore::ITLparser* context)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, context)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    inscore::ITLparser* context;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, context);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, inscore::ITLparser* context)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, context)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    inscore::ITLparser* context;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , context);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, context); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, inscore::ITLparser* context)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, context)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    inscore::ITLparser* context;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (context);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (inscore::ITLparser* context);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (inscore::ITLparser* context)
#else
int
yyparse (context)
    inscore::ITLparser* context;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
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
     `$$ = $1'.

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
#line 117 "ITL.y"
    { context->fReader.add(*(yyvsp[(1) - (2)].msg)); delete (yyvsp[(1) - (2)].msg); ;}
    break;

  case 5:
#line 118 "ITL.y"
    { delete (yyvsp[(1) - (2)].str); ;}
    break;

  case 6:
#line 119 "ITL.y"
    {	if (*(yyvsp[(1) - (1)].msgList)) {
										for (unsigned int i=0; i < (*(yyvsp[(1) - (1)].msgList))->list().size(); i++)
											context->fReader.add((*(yyvsp[(1) - (1)].msgList))->list()[i]);
									}
									delete (yyvsp[(1) - (1)].msgList);
								;}
    break;

  case 7:
#line 125 "ITL.y"
    { YYACCEPT; ;}
    break;

  case 8:
#line 131 "ITL.y"
    {	(yyval.msgList) = new inscore::SIMessageList (inscore::IMessageList::create());
									*(yyval.msgList) = context->fReader.luaEval(context->fText.c_str());
								;}
    break;

  case 9:
#line 134 "ITL.y"
    {	(yyval.msgList) = new inscore::SIMessageList (inscore::IMessageList::create());
									*(yyval.msgList) = context->fReader.jsEval(context->fText.c_str(), yylloc.last_line);
								;}
    break;

  case 10:
#line 143 "ITL.y"
    { (yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[(1) - (1)].addr)->fOsc)); (*(yyval.msg))->setUrl((yyvsp[(1) - (1)].addr)->fUrl); delete (yyvsp[(1) - (1)].addr); ;}
    break;

  case 11:
#line 144 "ITL.y"
    { (yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[(1) - (2)].addr)->fOsc, *(yyvsp[(2) - (2)].plist), (yyvsp[(1) - (2)].addr)->fUrl)); delete (yyvsp[(1) - (2)].addr); delete (yyvsp[(2) - (2)].plist); ;}
    break;

  case 12:
#line 146 "ITL.y"
    {	(yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[(1) - (5)].addr)->fOsc, *(yyvsp[(2) - (5)].plist), (yyvsp[(1) - (5)].addr)->fUrl));
											(*(yyval.msg))->add(*(yyvsp[(4) - (5)].msgList)); delete (yyvsp[(1) - (5)].addr); delete (yyvsp[(2) - (5)].plist); delete (yyvsp[(4) - (5)].msgList); ;}
    break;

  case 13:
#line 148 "ITL.y"
    {	(yyval.msg) = new inscore::SIMessage(inscore::IMessage::create((yyvsp[(1) - (3)].addr)->fOsc, *(yyvsp[(2) - (3)].plist), (yyvsp[(1) - (3)].addr)->fUrl));
											(*(yyval.msg))->add(*(yyvsp[(3) - (3)].plist)); delete (yyvsp[(1) - (3)].addr); delete (yyvsp[(2) - (3)].plist); delete (yyvsp[(3) - (3)].plist); ;}
    break;

  case 14:
#line 152 "ITL.y"
    {	(yyval.msgList) = new inscore::SIMessageList (inscore::IMessageList::create());
											(*(yyval.msgList))->list().push_back(*(yyvsp[(1) - (1)].msg));
											delete (yyvsp[(1) - (1)].msg); ;}
    break;

  case 15:
#line 155 "ITL.y"
    {	(yyval.msgList) = (yyvsp[(1) - (3)].msgList); (*(yyval.msgList))->list().push_back(*(yyvsp[(3) - (3)].msg)); delete (yyvsp[(3) - (3)].msg); ;}
    break;

  case 18:
#line 163 "ITL.y"
    { (yyval.addr) = new inscore::ITLparser::address (*(yyvsp[(1) - (1)].str)); delete (yyvsp[(1) - (1)].str);;}
    break;

  case 19:
#line 164 "ITL.y"
    { (yyval.addr) = new inscore::ITLparser::address (*(yyvsp[(1) - (1)].str)); delete (yyvsp[(1) - (1)].str);;}
    break;

  case 20:
#line 165 "ITL.y"
    { (yyval.addr) = new inscore::ITLparser::address (*(yyvsp[(2) - (2)].str), *(yyvsp[(1) - (2)].url)); delete (yyvsp[(1) - (2)].url); delete (yyvsp[(2) - (2)].str); ;}
    break;

  case 21:
#line 168 "ITL.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 22:
#line 169 "ITL.y"
    { *(yyvsp[(1) - (2)].str) += *(yyvsp[(2) - (2)].str); (yyval.str) = (yyvsp[(1) - (2)].str); delete (yyvsp[(2) - (2)].str); ;}
    break;

  case 23:
#line 172 "ITL.y"
    { (yyval.str) = new string("." + *(yyvsp[(2) - (2)].str)); delete (yyvsp[(2) - (2)].str); ;}
    break;

  case 24:
#line 175 "ITL.y"
    { (yyval.str) = new string("/" + *(yyvsp[(2) - (2)].str)); delete (yyvsp[(2) - (2)].str); ;}
    break;

  case 25:
#line 176 "ITL.y"
    { (yyval.str) = new string("/$" + *(yyvsp[(3) - (3)].str)); delete (yyvsp[(3) - (3)].str); ;}
    break;

  case 26:
#line 179 "ITL.y"
    { (yyval.url) = new inscore::IMessage::TUrl((yyvsp[(1) - (3)].str)->c_str(), context->fInt); delete (yyvsp[(1) - (3)].str); ;}
    break;

  case 27:
#line 180 "ITL.y"
    { (yyval.url) = new inscore::IMessage::TUrl(context->fText.c_str(), context->fInt); ;}
    break;

  case 28:
#line 183 "ITL.y"
    { (yyval.str) = new string(context->fText); ;}
    break;

  case 29:
#line 184 "ITL.y"
    { *(yyvsp[(1) - (3)].str) += '.' + context->fText; (yyval.str)=(yyvsp[(1) - (3)].str); ;}
    break;

  case 30:
#line 187 "ITL.y"
    { (yyval.str) = new string(context->fText); ;}
    break;

  case 31:
#line 188 "ITL.y"
    { (yyval.str) = new string(context->fText); ;}
    break;

  case 32:
#line 189 "ITL.y"
    { (yyval.str) = new string(context->fText); ;}
    break;

  case 33:
#line 195 "ITL.y"
    { (yyval.plist) = new inscore::IMessage::argslist; 
								  inscore::Sbaseparam * p = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText));
								  (yyval.plist)->push_back(*p); delete p; ;}
    break;

  case 34:
#line 206 "ITL.y"
    { (yyval.plist) = (yyvsp[(1) - (1)].plist); ;}
    break;

  case 35:
#line 207 "ITL.y"
    { (yyvsp[(1) - (2)].plist)->push_back((yyvsp[(2) - (2)].plist));  (yyval.plist) = (yyvsp[(1) - (2)].plist); delete (yyvsp[(2) - (2)].plist); ;}
    break;

  case 36:
#line 210 "ITL.y"
    { (yyval.plist) = new inscore::IMessage::argslist; 
									  (yyval.plist)->push_back (context->fReader.resolve(context->fText.c_str(), lineno(context))); ;}
    break;

  case 37:
#line 212 "ITL.y"
    { (yyval.plist) = new inscore::IMessage::argslist; 
								  			  (yyval.plist)->push_back (context->fReader.resolveinc(context->fText.c_str(), true, lineno(context)));
								  			;}
    break;

  case 38:
#line 215 "ITL.y"
    { (yyval.plist) = new inscore::IMessage::argslist; 
								  			  (yyval.plist)->push_back (context->fReader.resolvedec(context->fText.c_str(), true, lineno(context)));
								  			;}
    break;

  case 39:
#line 218 "ITL.y"
    { (yyval.plist) = new inscore::IMessage::argslist; 
								  			  (yyval.plist)->push_back (context->fReader.resolveinc(context->fText.c_str(), false, lineno(context)));
								  			;}
    break;

  case 40:
#line 221 "ITL.y"
    { (yyval.plist) = new inscore::IMessage::argslist; 
								  			  (yyval.plist)->push_back (context->fReader.resolvedec(context->fText.c_str(), false, lineno(context)));
								  			;}
    break;

  case 41:
#line 224 "ITL.y"
    { (yyval.plist) = new inscore::IMessage::argslist;
								  (yyval.plist)->push_back (context->fReader.resolve(*(yyvsp[(3) - (4)].msg)));
								  delete (yyvsp[(3) - (4)].msg);
								;}
    break;

  case 42:
#line 230 "ITL.y"
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<int>((yyvsp[(1) - (1)].num))); ;}
    break;

  case 43:
#line 231 "ITL.y"
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<float>(context->fFloat)); ;}
    break;

  case 44:
#line 232 "ITL.y"
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); delete (yyvsp[(1) - (1)].str); ;}
    break;

  case 45:
#line 233 "ITL.y"
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<std::string>(context->fText)); ;}
    break;

  case 46:
#line 234 "ITL.y"
    { (yyval.p) = (yyvsp[(1) - (1)].p);;}
    break;

  case 47:
#line 235 "ITL.y"
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<inscore::SIMessageList>(*(yyvsp[(2) - (3)].msgList))); delete (yyvsp[(2) - (3)].msgList); ;}
    break;

  case 48:
#line 236 "ITL.y"
    { (yyval.p) = new inscore::Sbaseparam(new inscore::IMsgParam<inscore::SIMessageList>(*(yyvsp[(1) - (1)].msgList))); delete (yyvsp[(1) - (1)].msgList); ;}
    break;

  case 49:
#line 241 "ITL.y"
    { (yyval.plist) = new inscore::IMessage::argslist; (yyval.plist)->push_back (*(yyvsp[(1) - (1)].p)); delete (yyvsp[(1) - (1)].p) ;}
    break;

  case 50:
#line 242 "ITL.y"
    { (yyval.plist) = (yyvsp[(1) - (1)].plist); ;}
    break;

  case 51:
#line 243 "ITL.y"
    { (yyval.plist) = context->math().add((yyvsp[(1) - (3)].plist), (yyvsp[(3) - (3)].plist)); delete (yyvsp[(1) - (3)].plist); delete (yyvsp[(3) - (3)].plist); ;}
    break;

  case 52:
#line 244 "ITL.y"
    { (yyval.plist) = context->math().sub((yyvsp[(1) - (3)].plist), (yyvsp[(3) - (3)].plist)); delete (yyvsp[(1) - (3)].plist); delete (yyvsp[(3) - (3)].plist);  ;}
    break;

  case 53:
#line 245 "ITL.y"
    { (yyval.plist) = (yyval.plist) = context->math().minus((yyvsp[(2) - (2)].plist));   delete (yyvsp[(2) - (2)].plist); ;}
    break;

  case 54:
#line 246 "ITL.y"
    { (yyval.plist) = context->math().mult((yyvsp[(1) - (3)].plist), (yyvsp[(3) - (3)].plist)); delete (yyvsp[(1) - (3)].plist); delete (yyvsp[(3) - (3)].plist); ;}
    break;

  case 55:
#line 247 "ITL.y"
    { (yyval.plist) = context->math().div((yyvsp[(1) - (3)].plist), (yyvsp[(3) - (3)].plist));  delete (yyvsp[(1) - (3)].plist); delete (yyvsp[(3) - (3)].plist); ;}
    break;

  case 56:
#line 248 "ITL.y"
    { (yyval.plist) = context->math().mod((yyvsp[(1) - (3)].plist), (yyvsp[(3) - (3)].plist));  delete (yyvsp[(1) - (3)].plist); delete (yyvsp[(3) - (3)].plist); ;}
    break;

  case 57:
#line 249 "ITL.y"
    { (yyval.plist) = (yyvsp[(2) - (3)].plist); ;}
    break;

  case 58:
#line 250 "ITL.y"
    { (yyval.plist) = (yyvsp[(3) - (4)].plist); ;}
    break;

  case 59:
#line 251 "ITL.y"
    { (yyval.plist) = (yyvsp[(3) - (4)].plist); ;}
    break;

  case 60:
#line 252 "ITL.y"
    { (yyval.plist) = (yyvsp[(2) - (7)].num) ? (delete (yyvsp[(6) - (7)].plist), (yyvsp[(4) - (7)].plist)) : (delete (yyvsp[(4) - (7)].plist), (yyvsp[(6) - (7)].plist)); ;}
    break;

  case 61:
#line 255 "ITL.y"
    { (yyval.plist) = context->math().less(*(yyvsp[(1) - (2)].plist), *(yyvsp[(2) - (2)].plist)) ? (delete (yyvsp[(2) - (2)].plist), (yyvsp[(1) - (2)].plist)) : (delete (yyvsp[(1) - (2)].plist), (yyvsp[(2) - (2)].plist)); ;}
    break;

  case 62:
#line 256 "ITL.y"
    { (yyval.plist) = context->math().less(*(yyvsp[(1) - (2)].plist), *(yyvsp[(2) - (2)].plist)) ? (delete (yyvsp[(2) - (2)].plist), (yyvsp[(1) - (2)].plist)) : (delete (yyvsp[(1) - (2)].plist), (yyvsp[(2) - (2)].plist)); ;}
    break;

  case 63:
#line 259 "ITL.y"
    { (yyval.plist) = context->math().greater(*(yyvsp[(1) - (2)].plist), *(yyvsp[(2) - (2)].plist)) ? (delete (yyvsp[(2) - (2)].plist), (yyvsp[(1) - (2)].plist)) : (delete (yyvsp[(1) - (2)].plist), (yyvsp[(2) - (2)].plist)); ;}
    break;

  case 64:
#line 260 "ITL.y"
    { (yyval.plist) = context->math().greater(*(yyvsp[(1) - (2)].plist), *(yyvsp[(2) - (2)].plist)) ? (delete (yyvsp[(2) - (2)].plist), (yyvsp[(1) - (2)].plist)) : (delete (yyvsp[(1) - (2)].plist), (yyvsp[(2) - (2)].plist)); ;}
    break;

  case 65:
#line 263 "ITL.y"
    { (yyval.num) = context->math().tobool(*(yyvsp[(1) - (1)].plist)); 		delete (yyvsp[(1) - (1)].plist);;}
    break;

  case 66:
#line 264 "ITL.y"
    { (yyval.num) = (context->math().tobool(*(yyvsp[(2) - (2)].plist)) ? 0 : 1); delete (yyvsp[(2) - (2)].plist); ;}
    break;

  case 67:
#line 265 "ITL.y"
    { (yyval.num) = context->math().equal(*(yyvsp[(1) - (3)].plist), *(yyvsp[(3) - (3)].plist));     delete (yyvsp[(1) - (3)].plist); delete (yyvsp[(3) - (3)].plist); ;}
    break;

  case 68:
#line 266 "ITL.y"
    { (yyval.num) = context->math().greater(*(yyvsp[(1) - (3)].plist), *(yyvsp[(3) - (3)].plist));   delete (yyvsp[(1) - (3)].plist); delete (yyvsp[(3) - (3)].plist); ;}
    break;

  case 69:
#line 267 "ITL.y"
    { (yyval.num) = context->math().greatereq(*(yyvsp[(1) - (3)].plist), *(yyvsp[(3) - (3)].plist)); delete (yyvsp[(1) - (3)].plist); delete (yyvsp[(3) - (3)].plist); ;}
    break;

  case 70:
#line 268 "ITL.y"
    { (yyval.num) = context->math().less(*(yyvsp[(1) - (3)].plist), *(yyvsp[(3) - (3)].plist)); 	  	delete (yyvsp[(1) - (3)].plist); delete (yyvsp[(3) - (3)].plist); ;}
    break;

  case 71:
#line 269 "ITL.y"
    { (yyval.num) = context->math().lesseq(*(yyvsp[(1) - (3)].plist), *(yyvsp[(3) - (3)].plist)); 	delete (yyvsp[(1) - (3)].plist); delete (yyvsp[(3) - (3)].plist); ;}
    break;

  case 72:
#line 274 "ITL.y"
    { (yyval.str)=(yyvsp[(1) - (3)].str); context->fReader.variable((yyvsp[(1) - (3)].str)->c_str(), (yyvsp[(3) - (3)].plist)); delete (yyvsp[(3) - (3)].plist);;}
    break;

  case 73:
#line 277 "ITL.y"
    { (yyval.str) = new string(context->fText); ;}
    break;

  case 74:
#line 278 "ITL.y"
    { (yyval.str) = new string(context->fText); ;}
    break;

  case 75:
#line 283 "ITL.y"
    { (yyval.num) = context->fInt; ;}
    break;

  case 76:
#line 284 "ITL.y"
    { (yyval.num) = context->fInt; ;}
    break;

  case 77:
#line 290 "ITL.y"
    { (yyval.p) = context->fReader.parseExpr(context->fText, context->fExprStartLine, yyloc.first_column + 1 - context->fText.length());;}
    break;


/* Line 1267 of yacc.c.  */
#line 2046 "ITLparse.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, context, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (&yylloc, context, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, context, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, context);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, context, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, context);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 293 "ITL.y"


namespace inscore 
{

SIMessageList ITLparser::parse()
{
	fParseSucceed = !yyparse (this);
	return fReader.messages();
}
}

using namespace inscore;

int lineno (ITLparser* context)	
{ 
	return context->fLine + context->fLineOffset; 
}

int yyerror(const YYLTYPE* loc, ITLparser* context, const char*s) {
#ifdef NO_OSCSTREAM
	cerr << "error line " << loc->last_line + context->fLineOffset << " col " << loc->first_column << ":" << s << endl;
#else
	context->fReader.error (loc->last_line + context->fLineOffset, loc->first_column, s);
#endif
	return 0;
}

