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
    OSCADDRESS = 262,
    EQUAL = 263,
    REGEXP = 264,
    STRING = 265,
    EVAL = 266,
    ERR = 267,
    ENDEXPR = 268,
    ENDSCRIPT = 269,
    VARSTART = 270,
    VARIABLE = 271,
    LEFTPAR = 272,
    RIGHTPAR = 273,
    VARIABLEPOSTINC = 274,
    VARIABLEPOSTDEC = 275,
    VARIABLEPREINC = 276,
    VARIABLEPREDEC = 277,
    COLON = 278,
    COMMA = 279,
    POINT = 280,
    HOSTNAME = 281,
    IPNUM = 282,
    EXPRESSION = 283,
    JSCRIPT = 284,
    ADD = 285,
    SUB = 286,
    DIV = 287,
    MULT = 288,
    QUEST = 289,
    MIN = 290,
    MAX = 291,
    GREATER = 292,
    GREATEREQ = 293,
    LESS = 294,
    LESSEQ = 295,
    EQ = 296,
    MINUS = 297,
    NEG = 298,
    MODULO = 299,
    NEQ = 300,
    PREINC = 301,
    PREDEC = 302,
    POSTINC = 303,
    POSTDEC = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 28 "ITL.y" /* yacc.c:1919  */

	int		num;
	float	real;
	std::string* str;
	inscore::ITLparser::address*	addr;
	inscore::Sbaseparam *			p;
	inscore::IMessage::argslist*	plist;
	inscore::IMessage::TUrl*		url;
	inscore::SIMessage*				msg;
    inscore::SIMessageList*			msgList;

#line 116 "ITLparse.hpp" /* yacc.c:1919  */
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



int ITLparse (inscore::ITLparser* context);

#endif /* !YY_ITL_ITLPARSE_HPP_INCLUDED  */
