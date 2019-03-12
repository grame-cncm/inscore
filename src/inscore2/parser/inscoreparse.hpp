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
     URLPREFIX = 320,
     VARIABLE = 321,
     WITH = 322,
     STIME = 323,
     MSTIME = 324,
     SEQ = 325,
     PAR = 326,
     MFUN = 327,
     OP = 328,
     LDECL = 329,
     DECL = 330
   };
#endif
/* Tokens.  */
#define ACOS 258
#define ACOSH 259
#define ADD 260
#define ANYADDR 261
#define ASIN 262
#define ASINH 263
#define ATAN 264
#define ATANH 265
#define CBRT 266
#define CEIL 267
#define COLON 268
#define COMMA 269
#define COS 270
#define COSH 271
#define DIV 272
#define ENDSCRIPT 273
#define ENDSTATEMENT 274
#define EOL 275
#define EQ 276
#define EQUAL 277
#define ERR 278
#define EXP 279
#define EXPANDID 280
#define FLOAT 281
#define FLOOR 282
#define GREATER 283
#define GREATEREQ 284
#define HAS 285
#define IDENTIFIER 286
#define INT 287
#define JSCRIPT 288
#define LDOTS 289
#define LEFTBRACE 290
#define LEFTBRACKET 291
#define LEFTPAR 292
#define LESS 293
#define LESSEQ 294
#define LETTERS 295
#define LOG 296
#define LOG10 297
#define LOG2 298
#define MAX 299
#define MIN 300
#define MODULO 301
#define MULT 302
#define NEG 303
#define POW 304
#define QUEST 305
#define RAND 306
#define REGEXP 307
#define RIGHTBRACE 308
#define RIGHTBRACKET 309
#define RIGHTPAR 310
#define ROUND 311
#define SIN 312
#define SINH 313
#define SLASH 314
#define SQRT 315
#define STRING 316
#define SUB 317
#define TAN 318
#define TANH 319
#define URLPREFIX 320
#define VARIABLE 321
#define WITH 322
#define STIME 323
#define MSTIME 324
#define SEQ 325
#define PAR 326
#define MFUN 327
#define OP 328
#define LDECL 329
#define DECL 330




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 118 "inscorev2.y"
{
	inscore2::INode* 		treeptr;
}
/* Line 1529 of yacc.c.  */
#line 203 "inscoreparse.hpp"
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


