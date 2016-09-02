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
     OSCADDRESS = 262,
     EQUAL = 263,
     REGEXP = 264,
     FILEPATH = 265,
     STRING = 266,
     EVAL = 267,
     ERR = 268,
     ENDEXPR = 269,
     ENDSCRIPT = 270,
     VARSTART = 271,
     VARIABLE = 272,
     LEFTPAR = 273,
     RIGHTPAR = 274,
     VARIABLEPOSTINC = 275,
     VARIABLEPOSTDEC = 276,
     VARIABLEPREINC = 277,
     VARIABLEPREDEC = 278,
     COLON = 279,
     COMMA = 280,
     POINT = 281,
     HOSTNAME = 282,
     IPNUM = 283,
     EXPRESSION = 284,
     LUASCRIPT = 285,
     JSCRIPT = 286,
     ADD = 287,
     SUB = 288,
     DIV = 289,
     MULT = 290,
     QUEST = 291,
     MIN = 292,
     MAX = 293,
     GREATER = 294,
     GREATEREQ = 295,
     LESS = 296,
     LESSEQ = 297,
     EQ = 298,
     MINUS = 299,
     NEG = 300,
     MODULO = 301,
     NEQ = 302,
     POSTDEC = 303,
     POSTINC = 304,
     PREDEC = 305,
     PREINC = 306
   };
#endif
/* Tokens.  */
#define INT 258
#define UINT 259
#define FLOAT 260
#define IDENTIFIER 261
#define OSCADDRESS 262
#define EQUAL 263
#define REGEXP 264
#define FILEPATH 265
#define STRING 266
#define EVAL 267
#define ERR 268
#define ENDEXPR 269
#define ENDSCRIPT 270
#define VARSTART 271
#define VARIABLE 272
#define LEFTPAR 273
#define RIGHTPAR 274
#define VARIABLEPOSTINC 275
#define VARIABLEPOSTDEC 276
#define VARIABLEPREINC 277
#define VARIABLEPREDEC 278
#define COLON 279
#define COMMA 280
#define POINT 281
#define HOSTNAME 282
#define IPNUM 283
#define EXPRESSION 284
#define LUASCRIPT 285
#define JSCRIPT 286
#define ADD 287
#define SUB 288
#define DIV 289
#define MULT 290
#define QUEST 291
#define MIN 292
#define MAX 293
#define GREATER 294
#define GREATEREQ 295
#define LESS 296
#define LESSEQ 297
#define EQ 298
#define MINUS 299
#define NEG 300
#define MODULO 301
#define NEQ 302
#define POSTDEC 303
#define POSTINC 304
#define PREDEC 305
#define PREINC 306




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 29 "ITL.y"
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
/* Line 1529 of yacc.c.  */
#line 163 "ITLparse.hpp"
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


