/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
     MAPIDENTIFIER = 263,
     REGEXP = 264,
     PATHSEP = 265,
     STRING = 266,
     MSG = 267,
     ERR = 268,
     ENDEXPR = 269,
     COMMENTSTR = 270,
     SPACE = 271,
     EOL = 272,
     LPAR = 273,
     RPAR = 274,
     SEP = 275,
     LOOP = 276,
     LOOPIDENTIFIER = 277,
     LOOPREGEXP = 278,
     VARSTART = 279,
     LUASCRIPT = 280,
     JSCRIPT = 281
   };
#endif
/* Tokens.  */
#define INT 258
#define UINT 259
#define FLOAT 260
#define IDENTIFIER 261
#define EQUAL 262
#define MAPIDENTIFIER 263
#define REGEXP 264
#define PATHSEP 265
#define STRING 266
#define MSG 267
#define ERR 268
#define ENDEXPR 269
#define COMMENTSTR 270
#define SPACE 271
#define EOL 272
#define LPAR 273
#define RPAR 274
#define SEP 275
#define LOOP 276
#define LOOPIDENTIFIER 277
#define LOOPREGEXP 278
#define VARSTART 279
#define LUASCRIPT 280
#define JSCRIPT 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 24 "ITL.y"
{
	int		num;
	float	real;
	std::string* str;
	inscore::Sbaseparam *			p;
	inscore::IMessage::argslist*	plist;
	inscore::SIMessage*				msg;
	inscore::SIMessageList*		msgList;
}
/* Line 1529 of yacc.c.  */
#line 111 "ITLparse.hpp"
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


