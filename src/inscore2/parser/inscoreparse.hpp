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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 135 "inscorev2.y"
{
	inscore2::INode* 		treeptr;
}
/* Line 1529 of yacc.c.  */
#line 201 "inscoreparse.hpp"
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


