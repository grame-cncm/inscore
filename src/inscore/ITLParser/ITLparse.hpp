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
     POSTDEC = 301,
     POSTINC = 302,
     PREDEC = 303,
     PREINC = 304
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
#define STRING 265
#define EVAL 266
#define ERR 267
#define ENDEXPR 268
#define ENDSCRIPT 269
#define VARSTART 270
#define VARIABLE 271
#define LEFTPAR 272
#define RIGHTPAR 273
#define VARIABLEPOSTINC 274
#define VARIABLEPOSTDEC 275
#define VARIABLEPREINC 276
#define VARIABLEPREDEC 277
#define COLON 278
#define COMMA 279
#define POINT 280
#define HOSTNAME 281
#define IPNUM 282
#define EXPRESSION 283
#define JSCRIPT 284
#define ADD 285
#define SUB 286
#define DIV 287
#define MULT 288
#define QUEST 289
#define MIN 290
#define MAX 291
#define GREATER 292
#define GREATEREQ 293
#define LESS 294
#define LESSEQ 295
#define EQ 296
#define MINUS 297
#define NEG 298
#define MODULO 299
#define NEQ 300
#define POSTDEC 301
#define POSTINC 302
#define PREDEC 303
#define PREINC 304




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 28 "ITL.y"
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
#line 159 "ITLparse.hpp"
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


