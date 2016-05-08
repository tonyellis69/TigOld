/* A Bison parser, made by GNU Bison 3.0.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_TIG_HPP_INCLUDED
# define YY_YY_TIG_HPP_INCLUDED
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
    INTEGER = 258,
    IDENTIFIER = 259,
    STRING = 260,
    FLOAT = 261,
    RAND = 262,
    WHILE = 263,
    FOR = 264,
    IF = 265,
    PRINT = 266,
    PRINT_VALERIC = 267,
    FUNC_CALL = 268,
    FUNC_CALL_RET = 269,
    FN_RETURN = 270,
    LOCAL_VAR = 271,
    CLASS = 272,
    HAS = 273,
    WITH = 274,
    ARROW = 275,
    BASED_ON = 276,
    ARRAY = 277,
    TABLE = 278,
    SUPERCLASS = 279,
    DATA_TYPE = 280,
    STR_INPUT = 281,
    RESERVED_ADD = 282,
    RESERVED_SIZE = 283,
    MEMB_ASSIGN = 284,
    PLIB = 285,
    DEREF_ASSIGN = 286,
    ARRAY_ASSIGN = 287,
    ARRAY_ELEMENT = 288,
    ARRAY_LIST = 289,
    TABLE_LIST = 290,
    IFX = 291,
    ELSE = 292,
    PRINT_COMPLEX = 293,
    FUNC = 294,
    NEW = 295,
    GE = 296,
    LE = 297,
    EQ = 298,
    NE = 299,
    OR = 300,
    AND = 301,
    RAND2 = 302,
    UMINUS = 303,
    NON_SEQ = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 89 "Tig.y" /* glr.c:2553  */
				 						
    int iValue;                 // integer value - for numeric constants etc 
	float fValue;				//float value - for floating-point constants
    CSyntaxNode *nPtr;          // node pointer - enables symbols to point to syntax nodes
	char    *str;				// a character string
	int iValue2;				//dual integer value, needed for second digit in the random number generator, eg, 1d20

#line 112 "Tig.hpp" /* glr.c:2553  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TIG_HPP_INCLUDED  */
