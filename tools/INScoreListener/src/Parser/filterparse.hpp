/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_FILTERPARSE_HPP_INCLUDED
# define YY_YY_FILTERPARSE_HPP_INCLUDED
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
    UINT = 259,
    FLOAT = 260,
    IDENTIFIER = 261,
    REGEXP = 262,
    PATHSEP = 263,
    LEFTPAR = 264,
    RIGHTPAR = 265,
    EQUAL = 266,
    NOTEQUAL = 267,
    NOT = 268,
    GREATER = 269,
    GREATEREQUAL = 270,
    LOWER = 271,
    LOWEREQUAL = 272,
    LAND = 273,
    LOR = 274,
    LNOT = 275,
    STRING = 276,
    QUOTEDSTRING = 277,
    ARGID = 278,
    ADDR = 279
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 25 "filter.y" /* yacc.c:1909  */

	int		num;
	float	real;
	std::string* str;
	inscorelistener::OSCFilterNode* filterNode;
	inscorelistener::OSCFilterExprArg* filterArg;
	inscorelistener::OSCFilterExpr::Operator filterOperator;


#line 89 "filterparse.hpp" /* yacc.c:1909  */
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



int yyparse (inscorelistener::filterparser* context);

#endif /* !YY_YY_FILTERPARSE_HPP_INCLUDED  */
