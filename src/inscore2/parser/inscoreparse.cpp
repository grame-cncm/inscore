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
#define yyparse INSCOREV2parse
#define yylex   INSCOREV2lex
#define yyerror INSCOREV2error
#define yylval  INSCOREV2lval
#define yychar  INSCOREV2char
#define yydebug INSCOREV2debug
#define yynerrs INSCOREV2nerrs
#define yylloc INSCOREV2lloc

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ACOS = 258,
     ACOSH = 259,
     ADD = 260,
     ANYADDR = 261,
     APPLY = 262,
     ASIN = 263,
     ASINH = 264,
     ATAN = 265,
     ATANH = 266,
     CBRT = 267,
     CEIL = 268,
     COLON = 269,
     COMMA = 270,
     COS = 271,
     COSH = 272,
     DIV = 273,
     ENDSCRIPT = 274,
     ENDSTATEMENT = 275,
     EOL = 276,
     EQ = 277,
     EQUAL = 278,
     ERR = 279,
     EXP = 280,
     EXPANDID = 281,
     FLOAT = 282,
     FLOOR = 283,
     GREATER = 284,
     GREATEREQ = 285,
     HAS = 286,
     IDENTIFIER = 287,
     INT = 288,
     JSCRIPT = 289,
     LDOTS = 290,
     LEFTBRACE = 291,
     LEFTBRACKET = 292,
     LEFTPAR = 293,
     LESS = 294,
     LESSEQ = 295,
     LETTERS = 296,
     LOG = 297,
     LOG10 = 298,
     LOG2 = 299,
     MAX = 300,
     MIN = 301,
     MODULO = 302,
     MSTIME = 303,
     MULT = 304,
     NEG = 305,
     POW = 306,
     QUEST = 307,
     RAND = 308,
     REGEXP = 309,
     RIGHTBRACE = 310,
     RIGHTBRACKET = 311,
     RIGHTPAR = 312,
     ROUND = 313,
     SIN = 314,
     SINH = 315,
     SLASH = 316,
     SQRT = 317,
     STIME = 318,
     STRING = 319,
     SUB = 320,
     TAN = 321,
     TANH = 322,
     URLPREFIX = 323,
     VARIABLE = 324,
     WITH = 325,
     SEQ = 326,
     PAR = 327,
     LDECL = 328,
     DECL = 329
   };
#endif
/* Tokens.  */
#define ACOS 258
#define ACOSH 259
#define ADD 260
#define ANYADDR 261
#define APPLY 262
#define ASIN 263
#define ASINH 264
#define ATAN 265
#define ATANH 266
#define CBRT 267
#define CEIL 268
#define COLON 269
#define COMMA 270
#define COS 271
#define COSH 272
#define DIV 273
#define ENDSCRIPT 274
#define ENDSTATEMENT 275
#define EOL 276
#define EQ 277
#define EQUAL 278
#define ERR 279
#define EXP 280
#define EXPANDID 281
#define FLOAT 282
#define FLOOR 283
#define GREATER 284
#define GREATEREQ 285
#define HAS 286
#define IDENTIFIER 287
#define INT 288
#define JSCRIPT 289
#define LDOTS 290
#define LEFTBRACE 291
#define LEFTBRACKET 292
#define LEFTPAR 293
#define LESS 294
#define LESSEQ 295
#define LETTERS 296
#define LOG 297
#define LOG10 298
#define LOG2 299
#define MAX 300
#define MIN 301
#define MODULO 302
#define MSTIME 303
#define MULT 304
#define NEG 305
#define POW 306
#define QUEST 307
#define RAND 308
#define REGEXP 309
#define RIGHTBRACE 310
#define RIGHTBRACKET 311
#define RIGHTPAR 312
#define ROUND 313
#define SIN 314
#define SINH 315
#define SLASH 316
#define SQRT 317
#define STIME 318
#define STRING 319
#define SUB 320
#define TAN 321
#define TANH 322
#define URLPREFIX 323
#define VARIABLE 324
#define WITH 325
#define SEQ 326
#define PAR 327
#define LDECL 328
#define DECL 329




/* Copy the first part of user declarations.  */
#line 2 "inscorev2.y"

/*

  INScore Project

  Copyright (C) 2019  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame - Centre national de création musicale, 
  11 cours de Verdun Gensoul, 69002 Lyon - France

*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
 
#include "IParser2.h"
#include "inscoreparse.hpp"
#include "inscorelex.hpp"

#ifdef WIN32
#pragma warning (disable : 4267 4100)
#endif

using namespace std;
using namespace inscore2;



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
#line 135 "inscorev2.y"
{
	inscore2::INode* 		treeptr;
}
/* Line 193 of yacc.c.  */
#line 300 "inscoreparse.cpp"
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
#line 143 "inscorev2.y"


int yyerror (const YYLTYPE* locp, IParser* context, const char*s);

#define scanner context->fScanner

// ----------------------------------------------------------------------------------------
// debug utility
#define YDEBUG	1
#if YDEBUG
#define ydebug std::cerr << "Y " 
#define yend std::endl
#else 
class nodebug {	public: template<typename T> nodebug& operator << (T) { return *this;} };
#define yend ""
nodebug ydebug;
#endif



/* Line 216 of yacc.c.  */
#line 344 "inscoreparse.cpp"

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
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   513

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNRULES -- Number of states.  */
#define YYNSTATES  117

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   329

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    17,    19,    21,
      27,    34,    36,    40,    44,    46,    48,    50,    52,    54,
      56,    58,    60,    62,    64,    67,    69,    72,    76,    80,
      82,    84,    86,    88,    90,    92,    98,   100,   105,   109,
     113,   115,   120,   122,   126,   128,   130,   132,   134,   136,
     138,   140,   142,   144,   146,   148,   150,   152,   154,   156,
     158,   160,   162,   164,   166,   168,   170,   172,   174,   176,
     178,   180,   182,   184,   186,   188,   190,   192,   194,   196,
     198,   200,   202,   204,   206,   208,   210
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      76,     0,    -1,    77,    -1,    76,    77,    -1,    80,    20,
      -1,    88,    20,    -1,    78,    20,    -1,    34,    -1,    19,
      -1,    81,    38,    57,    23,    80,    -1,    81,    38,    79,
      57,    23,    80,    -1,    81,    -1,    81,    23,    80,    -1,
      79,    15,    79,    -1,    81,    -1,    85,    -1,    84,    -1,
      95,    -1,    82,    -1,    83,    -1,    87,    -1,    94,    -1,
      90,    -1,    93,    -1,    61,    80,    -1,     6,    -1,    80,
      80,    -1,    80,    15,    80,    -1,    38,    80,    57,    -1,
      41,    -1,    32,    -1,    26,    -1,    54,    -1,    68,    -1,
      64,    -1,    37,    95,    35,    95,    56,    -1,    86,    -1,
      86,    36,    91,    55,    -1,    81,    23,    80,    -1,    81,
      23,    80,    -1,    92,    -1,    92,    36,    91,    55,    -1,
      89,    -1,    91,    15,    88,    -1,    69,    -1,    59,    -1,
      16,    -1,    66,    -1,     8,    -1,     3,    -1,    10,    -1,
      60,    -1,    17,    -1,    67,    -1,     9,    -1,     4,    -1,
      11,    -1,    25,    -1,    42,    -1,    43,    -1,    44,    -1,
      51,    -1,    62,    -1,    12,    -1,    13,    -1,    28,    -1,
      58,    -1,     5,    -1,    65,    -1,    18,    -1,    49,    -1,
      47,    -1,    52,    -1,    50,    -1,    22,    -1,    29,    -1,
      30,    -1,    39,    -1,    40,    -1,    46,    -1,    45,    -1,
      31,    -1,    53,    -1,    63,    -1,    48,    -1,    33,    -1,
      27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   169,   169,   170,   174,   175,   176,   177,   178,   182,
     183,   186,   187,   188,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   209,
     210,   213,   216,   219,   222,   225,   228,   229,   235,   238,
     241,   242,   245,   246,   249,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   265,   266,   267,
     268,   269,   270,   271,   273,   274,   275,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   295,   296,   299,   300
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ACOS", "ACOSH", "ADD", "ANYADDR",
  "APPLY", "ASIN", "ASINH", "ATAN", "ATANH", "CBRT", "CEIL", "COLON",
  "COMMA", "COS", "COSH", "DIV", "ENDSCRIPT", "ENDSTATEMENT", "EOL", "EQ",
  "EQUAL", "ERR", "EXP", "EXPANDID", "FLOAT", "FLOOR", "GREATER",
  "GREATEREQ", "HAS", "IDENTIFIER", "INT", "JSCRIPT", "LDOTS", "LEFTBRACE",
  "LEFTBRACKET", "LEFTPAR", "LESS", "LESSEQ", "LETTERS", "LOG", "LOG10",
  "LOG2", "MAX", "MIN", "MODULO", "MSTIME", "MULT", "NEG", "POW", "QUEST",
  "RAND", "REGEXP", "RIGHTBRACE", "RIGHTBRACKET", "RIGHTPAR", "ROUND",
  "SIN", "SINH", "SLASH", "SQRT", "STIME", "STRING", "SUB", "TAN", "TANH",
  "URLPREFIX", "VARIABLE", "WITH", "SEQ", "PAR", "LDECL", "DECL",
  "$accept", "start", "statement", "fundef", "argslist", "tree",
  "identifier", "expandid", "regexp", "prefix", "string", "exval",
  "expandval", "vardecl", "pushvardecl", "variable", "varlist", "varname",
  "math", "delay", "number", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    76,    77,    77,    77,    77,    77,    78,
      78,    79,    79,    79,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      81,    82,    83,    84,    85,    86,    87,    87,    88,    89,
      90,    90,    91,    91,    92,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    94,    94,    95,    95
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     1,     1,     5,
       6,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     5,     1,     4,     3,     3,
       1,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    49,    55,    67,    25,    48,    54,    50,    56,    63,
      64,    46,    52,    69,     8,    74,    57,    31,    86,    65,
      75,    76,    81,    30,    85,     7,     0,     0,    77,    78,
      29,    58,    59,    60,    80,    79,    71,    84,    70,    73,
      61,    72,    82,    32,    66,    45,    51,     0,    62,    83,
      34,    68,    47,    53,    33,    44,     0,     2,     0,     0,
      14,    18,    19,    16,    15,    36,    20,     0,    22,    40,
      23,    21,    17,     0,     0,    14,    24,     1,     3,     6,
       0,     4,    26,     0,     0,     0,     5,     0,     0,    28,
      27,    38,     0,     0,    11,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,    41,    35,     9,
      13,     0,    12,    39,     0,    43,    10
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    56,    57,    58,    93,    82,    75,    61,    62,    63,
      64,    65,    66,    67,    96,    68,    97,    69,    70,    71,
      72
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -77
static const yytype_int16 yypact[] =
{
     176,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   -14,   444,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   444,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   109,   -77,   -10,   243,
     -17,   -77,   -77,   -77,   -77,   -21,   -77,    -2,   -77,   -19,
     -77,   -77,   -77,   -15,   310,   -77,     2,   -77,   -77,   -77,
     444,   -77,    -3,   444,   -27,   -25,   -77,   -25,   -14,   -77,
      -3,   444,    -1,   -11,     3,     5,   -77,    -6,    -4,   -33,
     444,   -25,     6,   444,   444,   -25,   -77,   -77,   -77,   377,
     -77,   444,   377,   444,     8,   -77,   377
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,   -32,   -77,   -76,     0,     1,   -77,   -77,   -77,
     -77,   -77,   -77,   -73,   -77,   -77,   -54,   -77,   -77,   -77,
     -24
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      59,    60,    73,     4,   101,    23,    83,    23,     4,   105,
      79,   105,    80,    18,    30,    85,    30,    87,    86,    24,
      88,    84,   100,   108,    78,   110,   103,    74,   104,   111,
      92,    83,   115,    98,    26,    27,     0,     0,     0,    26,
       0,     0,     0,     0,     0,    37,   102,    76,     0,   106,
      37,   107,     0,     0,     0,     0,    59,    60,    47,     0,
      49,     0,     0,     0,    99,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      90,     0,     0,    91,     0,    94,    95,     0,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,     0,    94,   112,   113,     0,   114,     0,     0,    77,
       0,   116,     1,     2,     3,     4,     0,     5,     6,     7,
       8,     9,    10,     0,     0,    11,    12,    13,    14,     0,
       0,    15,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,     0,     0,     0,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,     1,
       2,     3,     4,     0,     5,     6,     7,     8,     9,    10,
       0,     0,    11,    12,    13,    14,     0,     0,    15,     0,
       0,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,     0,     0,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,     0,     0,     0,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,     1,     2,     3,     4,
       0,     5,     6,     7,     8,     9,    10,     0,    80,    11,
      12,    13,     0,    81,     0,    15,     0,     0,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,     0,     0,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,     0,     0,
       0,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,     1,     2,     3,     4,     0,     5,     6,
       7,     8,     9,    10,     0,    80,    11,    12,    13,     0,
       0,     0,    15,     0,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,     0,     0,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,     0,     0,    89,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
       1,     2,     3,     4,     0,     5,     6,     7,     8,     9,
      10,     0,    80,    11,    12,    13,     0,     0,     0,    15,
       0,     0,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     0,     0,     0,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,     0,     0,     0,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,     1,     2,     3,
       4,     0,     5,     6,     7,     8,     9,    10,     0,     0,
      11,    12,    13,     0,     0,     0,    15,     0,     0,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,     0,
       0,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,     0,
       0,     0,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55
};

static const yytype_int8 yycheck[] =
{
       0,     0,    26,     6,    15,    32,    23,    32,     6,    15,
      20,    15,    15,    27,    41,    36,    41,    36,    20,    33,
      35,    38,    23,    56,    56,   101,    23,    27,    23,    23,
      57,    23,   105,    87,    37,    38,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    -1,    48,    57,    47,    -1,    55,
      48,    55,    -1,    -1,    -1,    -1,    56,    56,    61,    -1,
      63,    -1,    -1,    -1,    88,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    -1,    83,    -1,    84,    85,    -1,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,    -1,   101,   103,   104,    -1,   105,    -1,    -1,     0,
      -1,   111,     3,     4,     5,     6,    -1,     8,     9,    10,
      11,    12,    13,    -1,    -1,    16,    17,    18,    19,    -1,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    -1,    -1,    -1,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     3,
       4,     5,     6,    -1,     8,     9,    10,    11,    12,    13,
      -1,    -1,    16,    17,    18,    19,    -1,    -1,    22,    -1,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    -1,    20,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,     3,     4,     5,     6,    -1,     8,     9,
      10,    11,    12,    13,    -1,    15,    16,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       3,     4,     5,     6,    -1,     8,     9,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    -1,    -1,    -1,    22,
      -1,    -1,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,     3,     4,     5,
       6,    -1,     8,     9,    10,    11,    12,    13,    -1,    -1,
      16,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      13,    16,    17,    18,    19,    22,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    76,    77,    78,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    90,    92,
      93,    94,    95,    95,    80,    81,    80,     0,    77,    20,
      15,    20,    80,    23,    38,    36,    20,    36,    35,    57,
      80,    80,    57,    79,    81,    81,    89,    91,    91,    95,
      23,    15,    57,    23,    23,    15,    55,    55,    56,    80,
      79,    23,    80,    80,    81,    88,    80
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, inscore2::IParser* context)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, context)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    inscore2::IParser* context;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, inscore2::IParser* context)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, context)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    inscore2::IParser* context;
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, inscore2::IParser* context)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, context)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    inscore2::IParser* context;
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, inscore2::IParser* context)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, context)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    inscore2::IParser* context;
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
int yyparse (inscore2::IParser* context);
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
yyparse (inscore2::IParser* context)
#else
int
yyparse (context)
    inscore2::IParser* context;
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
#line 174 "inscorev2.y"
    { context->add ((yyvsp[(1) - (2)].treeptr)); ;}
    break;

  case 5:
#line 175 "inscorev2.y"
    { ;}
    break;

  case 6:
#line 176 "inscorev2.y"
    { ;}
    break;

  case 7:
#line 177 "inscorev2.y"
    { context->add (context->javascript (context->fText)); ;}
    break;

  case 8:
#line 178 "inscorev2.y"
    { YYACCEPT; ;}
    break;

  case 9:
#line 182 "inscorev2.y"
    { cerr << "fundef " << (yyvsp[(1) - (5)].treeptr)->getValue() << "()" << endl; ;}
    break;

  case 10:
#line 183 "inscorev2.y"
    { cerr << "fundef " << (yyvsp[(1) - (6)].treeptr)->getValue() << " args: " << (yyvsp[(3) - (6)].treeptr) << " -> " << (yyvsp[(6) - (6)].treeptr)  << endl; ;}
    break;

  case 11:
#line 186 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 12:
#line 187 "inscorev2.y"
    { (yyval.treeptr) = context->seq((yyvsp[(1) - (3)].treeptr), (yyvsp[(3) - (3)].treeptr)); ;}
    break;

  case 13:
#line 188 "inscorev2.y"
    { (yyval.treeptr) = context->par((yyvsp[(1) - (3)].treeptr), (yyvsp[(3) - (3)].treeptr)) ;}
    break;

  case 14:
#line 192 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 15:
#line 193 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 16:
#line 194 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 17:
#line 195 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 18:
#line 196 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 19:
#line 197 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 20:
#line 198 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 21:
#line 199 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 22:
#line 200 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 23:
#line 201 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 24:
#line 202 "inscorev2.y"
    { (yyval.treeptr) = context->slash((yyvsp[(2) - (2)].treeptr)); ;}
    break;

  case 25:
#line 203 "inscorev2.y"
    { (yyval.treeptr) = context->slash(context->create ("*")); ;}
    break;

  case 26:
#line 204 "inscorev2.y"
    { (yyval.treeptr) = context->seq((yyvsp[(1) - (2)].treeptr), (yyvsp[(2) - (2)].treeptr)); ;}
    break;

  case 27:
#line 205 "inscorev2.y"
    { (yyval.treeptr) = context->par((yyvsp[(1) - (3)].treeptr), (yyvsp[(3) - (3)].treeptr)); ;}
    break;

  case 28:
#line 206 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(2) - (3)].treeptr); ;}
    break;

  case 29:
#line 209 "inscorev2.y"
    { (yyval.treeptr) = context->create (context->fText); ;}
    break;

  case 30:
#line 210 "inscorev2.y"
    { (yyval.treeptr) = context->create (context->fText); ;}
    break;

  case 31:
#line 213 "inscorev2.y"
    { (yyval.treeptr) = context->expand (context->fText); ;}
    break;

  case 32:
#line 216 "inscorev2.y"
    { (yyval.treeptr) = context->create (context->fText); ;}
    break;

  case 33:
#line 219 "inscorev2.y"
    { (yyval.treeptr) = context->prefix (context->fText); ;}
    break;

  case 34:
#line 222 "inscorev2.y"
    { (yyval.treeptr) = context->create (context->fText); ;}
    break;

  case 35:
#line 225 "inscorev2.y"
    { (yyval.treeptr) = context->expandVal ((yyvsp[(2) - (5)].treeptr), (yyvsp[(4) - (5)].treeptr)); ;}
    break;

  case 36:
#line 228 "inscorev2.y"
    { (yyval.treeptr) = (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 37:
#line 229 "inscorev2.y"
    { (yyval.treeptr) = context->setEnv((yyvsp[(1) - (4)].treeptr)); context->popEnv(); ;}
    break;

  case 38:
#line 235 "inscorev2.y"
    {context->declare ((yyvsp[(1) - (3)].treeptr)->getValue(), (yyvsp[(3) - (3)].treeptr)); delete (yyvsp[(1) - (3)].treeptr); ;}
    break;

  case 39:
#line 238 "inscorev2.y"
    { context->pushEnv(); context->declare ((yyvsp[(1) - (3)].treeptr)->getValue(), (yyvsp[(3) - (3)].treeptr)); delete (yyvsp[(1) - (3)].treeptr); ;}
    break;

  case 40:
#line 241 "inscorev2.y"
    { (yyval.treeptr) = context->variable ((yyvsp[(1) - (1)].treeptr)->getValue()); delete (yyvsp[(1) - (1)].treeptr); ;}
    break;

  case 41:
#line 242 "inscorev2.y"
    { (yyval.treeptr) = context->variable ((yyvsp[(1) - (4)].treeptr)->getValue()); context->popEnv(); delete  (yyvsp[(1) - (4)].treeptr); ;}
    break;

  case 42:
#line 245 "inscorev2.y"
    { ;}
    break;

  case 43:
#line 246 "inscorev2.y"
    { ;}
    break;

  case 44:
#line 249 "inscorev2.y"
    { (yyval.treeptr) = context->create (context->fText); ;}
    break;

  case 45:
#line 252 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kSin); ;}
    break;

  case 46:
#line 253 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kCos); ;}
    break;

  case 47:
#line 254 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kTan); ;}
    break;

  case 48:
#line 255 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kASin); ;}
    break;

  case 49:
#line 256 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kACos); ;}
    break;

  case 50:
#line 257 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kATan); ;}
    break;

  case 51:
#line 258 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kSinh); ;}
    break;

  case 52:
#line 259 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kCosh); ;}
    break;

  case 53:
#line 260 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kTanh); ;}
    break;

  case 54:
#line 261 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kASinh); ;}
    break;

  case 55:
#line 262 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kACosh); ;}
    break;

  case 56:
#line 263 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kATanh); ;}
    break;

  case 57:
#line 265 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kExp); ;}
    break;

  case 58:
#line 266 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kLog); ;}
    break;

  case 59:
#line 267 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kLog10); ;}
    break;

  case 60:
#line 268 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kLog2); ;}
    break;

  case 61:
#line 269 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kPow); ;}
    break;

  case 62:
#line 270 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kSqrt); ;}
    break;

  case 63:
#line 271 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kCbrt); ;}
    break;

  case 64:
#line 273 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kCeil); ;}
    break;

  case 65:
#line 274 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kFloor); ;}
    break;

  case 66:
#line 275 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kRound); ;}
    break;

  case 67:
#line 277 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kAdd); ;}
    break;

  case 68:
#line 278 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kSub); ;}
    break;

  case 69:
#line 279 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kDiv); ;}
    break;

  case 70:
#line 280 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kMult); ;}
    break;

  case 71:
#line 281 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kModulo); ;}
    break;

  case 72:
#line 282 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kQuest); ;}
    break;

  case 73:
#line 283 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kNeg); ;}
    break;

  case 74:
#line 284 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kEq); ;}
    break;

  case 75:
#line 285 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kGreater); ;}
    break;

  case 76:
#line 286 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kGreatereq); ;}
    break;

  case 77:
#line 287 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kLess); ;}
    break;

  case 78:
#line 288 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kLesseq); ;}
    break;

  case 79:
#line 289 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kMin); ;}
    break;

  case 80:
#line 290 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kMax); ;}
    break;

  case 81:
#line 291 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kHas); ;}
    break;

  case 82:
#line 292 "inscorev2.y"
    { (yyval.treeptr) = context->operation (INode::kRand); ;}
    break;

  case 83:
#line 295 "inscorev2.y"
    { (yyval.treeptr) = context->delay (context->fText); ;}
    break;

  case 84:
#line 296 "inscorev2.y"
    { (yyval.treeptr) = context->delay (context->fText); ;}
    break;

  case 85:
#line 299 "inscorev2.y"
    { (yyval.treeptr) = context->create (context->fText, INode::kInt); ;}
    break;

  case 86:
#line 300 "inscorev2.y"
    { (yyval.treeptr) = context->create (context->fText, INode::kFloat); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2186 "inscoreparse.cpp"
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


#line 303 "inscorev2.y"


namespace inscore2
{

bool IParser::parse()
{
	return !yyparse (this);
}

} // end namespace


int yyerror(const YYLTYPE* loc, IParser* context, const char*s) {
	cerr << "error line " << context->fLine << " column " << context->fColumn  << ": " << s << endl;
	context->error(context->fLine, context->fColumn, s);
	return 0;
}

