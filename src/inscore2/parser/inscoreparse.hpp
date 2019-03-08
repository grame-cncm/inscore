/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

#ifndef YY_INSCOREV2_INSCOREPARSE_HPP_INCLUDED
# define YY_INSCOREV2_INSCOREPARSE_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int INSCOREV2debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ACOS = 258,
    ACOSH = 259,
    ADD = 260,
    ANYADDR = 261,
    ASIN = 262,
    ASINH = 263,
    ATAN = 264,
    ATANH = 265,
    CBRT = 266,
    CEIL = 267,
    COLON = 268,
    COMMA = 269,
    COS = 270,
    COSH = 271,
    DIV = 272,
    ENDSCRIPT = 273,
    ENDSTATEMENT = 274,
    EOL = 275,
    EQ = 276,
    EQUAL = 277,
    ERR = 278,
    EXP = 279,
    EXPANDID = 280,
    FLOAT = 281,
    FLOOR = 282,
    GREATER = 283,
    GREATEREQ = 284,
    HAS = 285,
    IDENTIFIER = 286,
    INT = 287,
    JSCRIPT = 288,
    LDOTS = 289,
    LEFTBRACE = 290,
    LEFTBRACKET = 291,
    LEFTPAR = 292,
    LESS = 293,
    LESSEQ = 294,
    LETTERS = 295,
    LOG = 296,
    LOG10 = 297,
    LOG2 = 298,
    MAX = 299,
    MIN = 300,
    MODULO = 301,
    MULT = 302,
    NEG = 303,
    POW = 304,
    QUEST = 305,
    RAND = 306,
    REGEXP = 307,
    RIGHTBRACE = 308,
    RIGHTBRACKET = 309,
    RIGHTPAR = 310,
    ROUND = 311,
    SIN = 312,
    SINH = 313,
    SLASH = 314,
    SQRT = 315,
    STRING = 316,
    SUB = 317,
    TAN = 318,
    TANH = 319,
    UINT = 320,
    URLPREFIX = 321,
    VARIABLE = 322,
    WITH = 323,
    OP = 324,
    MFUN = 325,
    PAR = 326,
    SEQ = 327,
    DECL = 328,
    LDECL = 329
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 134 "inscorev2.y" /* yacc.c:1919  */

	inscore2::INode* 		treeptr;

#line 133 "inscoreparse.hpp" /* yacc.c:1919  */
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



int INSCOREV2parse (inscore2::IParser* context);

#endif /* !YY_INSCOREV2_INSCOREPARSE_HPP_INCLUDED  */
