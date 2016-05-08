/* A Bison parser, made by GNU Bison 3.0.  */

/* Skeleton implementation for Bison GLR parsers in C

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0






/* First part of user declarations.  */
#line 1 "Tig.y" /* glr.c:207  */
			// Definitions Section: -  token declarations and C code 
			// C code goes inside these curly brackets 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h> //  parser uses alloc 
#include "SyntaxNode.h"
#include "symtab.h"
#include "StringTable.h"
#include "Coder.h"
#include "main.h"
#include "Tig.h"
#include "Stack.h"
#include "Nodes.h"

CStateStack State;

CSymbolTable SymbTable;	//Symbol table - keeps track of global variables, function names etc

CStringTable StrTable;  //Where we store any strings that are parsed

CCoder CodeObj;		//CodeObj will write the final bytecode to a file

CNodes SyntaxObj;		//SyntaxObj creates the various syntax nodes we need.

//Symbol-handling routines that create a syntax tree:
//CSyntaxNode* SyntaxObj.Operator(int oper, int nops, ...); 	//Create an IF, WHILE etc node
//CSyntaxNode* SyntaxObj.IdentifierExpression(char* Name);	// Create a node for a variable or parameter symbol
//CSyntaxNode* SyntaxObj.IdentifierAssignment(char* Name); //Create a syntax node for a variable which is being assigned a value.
//CSyntaxNode* SyntaxObj.IdentifyVarName(char* Name); //Check if the named variable has already been declared.
//CSyntaxNode* SyntaxObj.IntegerConstant(int Value);	// Create a node for a numeric constant 
//CSyntaxNode* FloatNode(float Value); //Create a node for a float constant
//CSyntaxNode* StrNode(char* Str); //Create a node for a string constant 
//CSyntaxNode* SyntaxObj.CreateGlobalFnNameNode(char* Name); //Create a node for a function declaration
//CSyntaxNode *SyntaxObj.CreateMembFnNameNode(char* Name); //Create a node for a member function declaration
//CSyntaxNode* FnCallNode(char* Name);  //Createa a node for a function call
CSyntaxNode* DeclClassNode(char* Name); //Declare a class name
//CSyntaxNode* SyntaxObj.ClassIdNode(char* Name);	//Create a node for class symbol
CSyntaxNode* MemberNode(CSyntaxNode* Obj, char* MemberName); //Create a node for a data member symbol
CSyntaxNode* DeclArrayNode(CSyntaxNode* Dimension); //create a node for an array declaration
//CSyntaxNode* ArrayElementNode(CSyntaxNode* Array, CSyntaxNode*  Element, int DimensionCount); //Create a node for an array element
//CSyntaxNode *SyntaxObj.CreateSuperMembNode(CSyntaxNode* Obj, char* MemberName); //Create a node for a superclassed member  function.
CSyntaxNode* ClassOpNode(CSyntaxNode* Name, CSyntaxNode* Parents, CSyntaxNode* Members, int ParentCount); //Create class declaration operator node
CSyntaxNode *SupMembFnCallNode(char* Name); //Create a node for a call to a parent function.
CSyntaxNode* DeclTableNode(CSyntaxNode* Rows, CSyntaxNode* Columns); //create a node for a table declaration
CSyntaxNode* RandNode(char* Str,CSyntaxNode* Throws, CSyntaxNode* Dice); //create a node for a random number declaration
//CSyntaxNode* DeclFnNode(CSyntaxNode* Name, CSyntaxNode* Code); 
CSyntaxNode* InitMemberNode(char* MemberName);
//CSyntaxNode* SyntaxObj.MemberNode (char* MemberName); //Create a node for a data member symbol
//CSyntaxNode* MemberOfNode(CSyntaxNode* Memb);
CSyntaxNode* NewListArrayNode(CSyntaxNode* Initialisation, int Dimension);
CSyntaxNode* NewListTableNode(CSyntaxNode* Initialisation, int Cols, int Rows);
 
//Symbol-handling routines that don't result in a syntax node: 
//void DeclGlobalVar(char* Name,int val);  //Handle the declaration of a global variable. just record name etc
void DeclParam(char* Name, char* Ptr);  //Handle a function parameter declaration
void DeclDataMember(char* Name);  //Handle a class data-member declaration
void FreeNode(CSyntaxNode *p); //Delete nodes when they're no longer required
void RemoveFinalGetproperty(); //Simple kludge that removes the final ARROW operation where a value is being assigned to a obj->member.


void AddParentToCurrentClass(char* ParentName);

//Forward declarations for Bison
int yylex(void); //Called by Bison to parse input
void yyerror(const char *s); //Called by Bison when there's an error


int NoParents = 0;
//int SyntaxObj.TotalMembs = 0;
int ArrayFunc = 0;
int TableRows = 0;

CSyntaxNode* FinalMembNode = NULL;

void Error (const char *format, ...); //Our own error function - this is what yerror calls

//This symbol table entry represents the default int type. Symbols that aren't of a user-defined type can now be set to this. 
SymDesc *DefaultIntType = SymbTable.Find(GLOBAL_SCOPE,"Int"); 




#line 138 "Tig.cpp" /* glr.c:207  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#include "Tig.hpp"

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;

/* Copy the second part of user declarations.  */

#line 166 "Tig.cpp" /* glr.c:230  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef bool yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify clang.  */
# define YYLONGJMP(Env, Val) (longjmp (Env, Val), YYASSERT (0))
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#ifndef YYASSERT
# define YYASSERT(Condition) ((void) ((Condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   570

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNRULES -- Number of states.  */
#define YYNSTATES  213
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 7
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    54,     2,     2,
      61,    62,    52,    50,    55,    51,     2,    53,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    60,
      46,    63,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    65,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,    59,     2,     2,     2,     2,
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
      47,    48,    49,    56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   168,   168,   169,   171,   179,   183,   187,   188,   192,
     196,   200,   201,   202,   203,   212,   213,   217,   221,   222,
     226,   232,   236,   240,   241,   247,   248,   249,   250,   254,
     255,   259,   260,   264,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   287,   288,   299,
     303,   304,   309,   312,   318,   319,   324,   325,   327,   336,
     336,   342,   342,   349,   350,   353,   355,   361,   362,   370,
     374,   375,   379,   384,   388,   389,   393,   393,   398,   399,
     406,   407,   408,   409,   410,   411,   412,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   431,   432,   433,   437,   438,   440,   441,   442,
     447,   448
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "IDENTIFIER", "STRING",
  "FLOAT", "RAND", "WHILE", "FOR", "IF", "PRINT", "PRINT_VALERIC",
  "FUNC_CALL", "FUNC_CALL_RET", "FN_RETURN", "LOCAL_VAR", "CLASS", "HAS",
  "WITH", "ARROW", "BASED_ON", "ARRAY", "TABLE", "SUPERCLASS", "DATA_TYPE",
  "STR_INPUT", "RESERVED_ADD", "RESERVED_SIZE", "MEMB_ASSIGN", "PLIB",
  "DEREF_ASSIGN", "ARRAY_ASSIGN", "ARRAY_ELEMENT", "ARRAY_LIST",
  "TABLE_LIST", "IFX", "ELSE", "PRINT_COMPLEX", "FUNC", "NEW", "GE", "LE",
  "EQ", "NE", "'>'", "'<'", "OR", "AND", "RAND2", "'+'", "'-'", "'*'",
  "'/'", "'%'", "','", "UMINUS", "NON_SEQ", "'{'", "'}'", "';'", "'('",
  "')'", "'='", "'['", "']'", "$accept", "code", "global_statement",
  "class_name", "init_list", "init_pair", "data_member", "definition",
  "function_def", "func_name", "param_list", "param_name",
  "class_name_dec", "class_parents", "class_list", "data_list",
  "member_func", "member_func_decl", "member_func_name", "stmt",
  "stmt_list", "assignment", "var_or_member", "assignment_var_or_member",
  "memberOf", "deref", "function_call", "$@1", "function_call_return",
  "$@2", "call_func_name", "call_param_list", "complex_str", "ui_list",
  "ui", "for_rules", "dimension_list", "array_list", "$@3", "table_list",
  "expr", "expr_sequence", YY_NULL
};
#endif

#define YYPACT_NINF -56
#define YYTABLE_NINF -66

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short int yypact[] =
{
     -56,   222,   -56,   -54,    28,   -47,   -46,   -25,   148,    13,
      43,    44,    20,   -56,   -56,   -56,     2,     0,   -56,    24,
      46,   -10,    36,    45,   -56,    61,   210,    79,   210,   -56,
      21,    50,   -56,   -56,   103,   -56,   106,   210,   -56,   210,
      57,    12,   -56,    51,    59,   112,   -56,   -56,   456,   -56,
     -56,   476,   -56,    54,   -56,    31,   -56,   243,   255,     4,
     -56,   210,   117,   210,   -56,   -56,   -56,   -56,   390,    65,
      89,    22,    88,   412,   210,   136,   -56,    96,    97,   -56,
     210,   434,   -56,   -43,   155,    23,   -56,   -56,    50,   -56,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   -56,   -56,   156,   157,   144,   -56,
     -56,   -56,   280,   -56,   -56,   -28,   -56,   516,   -38,   304,
     210,    20,   210,   159,    20,    20,   340,   162,   147,   164,
     516,    49,   -56,    57,   -56,   -15,   210,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    94,    94,   -56,   -56,
     -56,   108,    33,   -56,   113,   109,   -56,   120,   156,   -56,
     172,   -56,   210,   -56,   115,   123,   -56,   496,   116,   -56,
     143,   -56,   -56,   177,   -56,   -22,   -56,   210,   210,   -56,
     -56,   122,   178,   -56,   308,     5,   182,    35,   -56,   365,
     -56,    79,    20,   -56,   164,   -56,   516,   516,   -56,   108,
     -56,   -56,   320,   -56,     7,   -56,   -56,   -56,   -56,   -56,
     -56,   -56,   -56
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned char yydefact[] =
{
       4,     0,     1,     0,    56,     0,     0,     0,     0,     0,
       0,     0,     0,    34,     3,     2,     0,     0,     5,     0,
       0,     0,     0,     0,    46,     0,     0,     0,     0,    80,
      83,    81,    82,   108,     0,   104,     0,     0,    76,     0,
       0,     0,    84,     0,     0,     0,    70,   105,     0,    81,
      44,     0,    21,     0,    64,    56,    47,     0,     0,     0,
      36,     0,     0,     0,    58,    43,    59,    66,     0,    56,
       0,     0,     0,     0,     0,    50,   103,    85,     0,    88,
       0,     0,    78,     0,     0,   107,    61,    38,    69,    71,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    45,     0,     0,     0,    35,
      48,    12,     0,    20,    16,     0,    18,    49,    57,     0,
      68,     0,     0,     0,     0,     0,     0,     0,    51,     0,
     110,     0,   102,     0,   106,    87,    68,    98,    99,   101,
     100,    95,    94,    97,    96,   109,    89,    90,    91,    92,
      93,    25,     0,    27,     0,     0,    23,    22,     0,    11,
       0,    15,     0,    74,     0,    67,    39,     0,    57,    40,
      41,    72,    54,     0,    10,     0,     7,     0,     0,    77,
      79,     0,     0,    13,     0,     0,     0,     0,    19,     0,
      60,     0,     0,    55,     0,    86,     9,   111,    62,    26,
      28,    30,     0,    32,     0,    24,    14,    75,    73,    42,
       8,    29,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
     -56,   -56,   -56,   -56,   -56,    -7,   -56,   -56,   -56,   -56,
       9,    29,   -56,   -56,   -56,    34,    14,   -56,   -56,     6,
     -55,   -26,   -56,   -56,   -56,    -1,   -56,   -56,   -56,   -56,
       1,    64,   -56,   -56,   150,   -56,   161,   -36,   -56,   -56,
      42,   125
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,     1,    14,    78,   175,   176,   177,    15,    16,    17,
     115,   116,    53,   108,   157,   152,   153,   154,   155,    56,
      57,    19,    76,    20,   128,    41,    22,   120,    42,   136,
      43,   164,    44,    45,    46,    72,    64,    47,    80,    83,
     130,   165
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short int yytable[] =
{
      21,    70,    23,   112,    82,   -57,    24,    18,   113,   113,
      62,    21,   133,    23,    26,    27,    29,    30,    49,    32,
      33,     3,   134,   -65,    55,   -53,    71,   160,     5,     6,
       7,     8,    84,   194,   161,     9,    28,    11,    34,    35,
     195,   -56,   123,   -58,    11,    25,   -65,    52,    54,   -57,
      48,    51,    25,    36,    63,    25,    21,    21,    23,    23,
      58,    59,   160,   110,    37,    67,   114,   203,    68,   212,
      73,    38,   106,    50,    39,   107,    63,    40,    12,    79,
      13,    81,   -63,    69,    60,   -56,    63,   -58,   182,   -17,
     182,   -52,   -63,   183,   -52,   206,    65,   180,    99,   100,
     101,   102,   103,   117,   178,   119,    66,    75,   179,    61,
      77,    21,    86,    23,    74,    38,   126,    88,   110,    87,
      21,   118,    23,    21,    21,    23,    23,   166,   -52,   202,
     169,   170,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   101,   102,   103,   122,
     124,    29,    30,    31,    32,    33,   127,    -6,   129,   135,
     151,   156,   158,   168,   167,   208,   172,   173,   174,   -33,
     185,   184,    11,    34,    35,   186,   113,   190,   178,   -53,
     192,   193,   199,    21,   198,    23,   205,   210,    36,   188,
      71,    21,   187,    23,   204,    89,   200,     0,   209,    37,
     181,    21,    85,    23,   189,   131,    38,     0,   110,    39,
       0,     0,    40,    29,    30,    49,    32,    33,     0,   196,
     197,     0,     2,     3,     0,     0,     4,     0,     0,     0,
       5,     6,     7,     8,    11,    34,    35,     9,     0,    10,
       0,     0,     0,     0,     3,     0,    11,    55,     0,     0,
      36,     5,     6,     7,     8,     0,     3,     0,     9,    55,
       0,    37,     0,     5,     6,     7,     8,    11,    38,     0,
       9,    39,     0,     0,    40,     0,     0,     0,     0,    11,
      12,     3,    13,     0,    55,     0,     0,     0,     5,     6,
       7,     8,     0,     0,     0,     9,     0,     0,     0,     0,
       0,    12,   109,    13,    11,     0,     0,     0,     0,     3,
       0,     0,    55,    12,   111,    13,     5,     6,     7,     8,
       0,     3,     0,     9,    55,     0,     0,     0,     5,     6,
       7,     8,    11,     0,     0,     9,     0,     0,    12,   159,
      13,     0,     0,     0,    11,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   162,
       0,     0,     0,     0,     0,     0,    12,   201,    13,   163,
       0,     0,     0,     0,     0,     0,     0,     0,    12,   211,
      13,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   171,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     207,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,     0,
       0,     0,   121,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     0,     0,     0,
       0,     0,     0,     0,   125,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,     0,
       0,     0,     0,     0,     0,     0,   132,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,     0,   104,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,     0,   105,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,     0,   191,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103
};

static const short int yycheck[] =
{
       1,    27,     1,    58,    40,    20,    60,     1,     4,     4,
      20,    12,    55,    12,    61,    61,     3,     4,     5,     6,
       7,     1,    65,    61,     4,    63,    27,    55,     8,     9,
      10,    11,    20,    55,    62,    15,    61,    24,    25,    26,
      62,    20,    20,    20,    24,    24,    61,     4,     4,    64,
       8,     9,    24,    40,    64,    24,    57,    58,    57,    58,
      58,    61,    55,    57,    51,     4,    62,    62,    26,    62,
      28,    58,    18,    60,    61,    21,    64,    64,    58,    37,
      60,    39,    61,     4,    60,    64,    64,    64,    55,    61,
      55,    63,    61,    60,    63,    60,    60,   133,    50,    51,
      52,    53,    54,    61,    55,    63,    61,     4,    59,    63,
       4,   112,    61,   112,    64,    58,    74,     5,   112,    60,
     121,     4,   121,   124,   125,   124,   125,   121,    63,   184,
     124,   125,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    52,    53,    54,    60,
      62,     3,     4,     5,     6,     7,    20,    61,    61,     4,
       4,     4,    18,     4,   122,   191,     4,    20,     4,    61,
      61,    58,    24,    25,    26,    55,     4,    62,    55,    63,
      37,     4,     4,   184,    62,   184,     4,   194,    40,   160,
     191,   192,   158,   192,   185,    45,   182,    -1,   192,    51,
     136,   202,    41,   202,   162,    80,    58,    -1,   202,    61,
      -1,    -1,    64,     3,     4,     5,     6,     7,    -1,   177,
     178,    -1,     0,     1,    -1,    -1,     4,    -1,    -1,    -1,
       8,     9,    10,    11,    24,    25,    26,    15,    -1,    17,
      -1,    -1,    -1,    -1,     1,    -1,    24,     4,    -1,    -1,
      40,     8,     9,    10,    11,    -1,     1,    -1,    15,     4,
      -1,    51,    -1,     8,     9,    10,    11,    24,    58,    -1,
      15,    61,    -1,    -1,    64,    -1,    -1,    -1,    -1,    24,
      58,     1,    60,    -1,     4,    -1,    -1,    -1,     8,     9,
      10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    24,    -1,    -1,    -1,    -1,     1,
      -1,    -1,     4,    58,    59,    60,     8,     9,    10,    11,
      -1,     1,    -1,    15,     4,    -1,    -1,    -1,     8,     9,
      10,    11,    24,    -1,    -1,    15,    -1,    -1,    58,    59,
      60,    -1,    -1,    -1,    24,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    60,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    60,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    60,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    67,     0,     1,     4,     8,     9,    10,    11,    15,
      17,    24,    58,    60,    68,    73,    74,    75,    85,    87,
      89,    91,    92,    96,    60,    24,    61,    61,    61,     3,
       4,     5,     6,     7,    25,    26,    40,    51,    58,    61,
      64,    91,    94,    96,    98,    99,   100,   103,   106,     5,
      60,   106,     4,    78,     4,     4,    85,    86,    58,    61,
      60,    63,    20,    64,   102,    60,    61,     4,   106,     4,
      87,    91,   101,   106,    64,     4,    88,     4,    69,   106,
     104,   106,   103,   105,    20,   102,    61,    60,     5,   100,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    60,    60,    18,    21,    79,    59,
      85,    59,    86,     4,    62,    76,    77,   106,     4,   106,
      93,    62,    60,    20,    62,    62,   106,    20,    90,    61,
     106,   107,    62,    55,    65,     4,    95,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,     4,    81,    82,    83,    84,     4,    80,    18,    59,
      55,    62,    55,    65,    97,   107,    85,   106,     4,    85,
      85,    65,     4,    20,     4,    70,    71,    72,    55,    59,
     103,    97,    55,    60,    58,    61,    55,    81,    77,   106,
      62,    60,    37,     4,    55,    62,   106,   106,    62,     4,
      82,    59,    86,    62,    76,     4,    60,    65,    87,    85,
      71,    59,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    66,    67,    67,    67,    68,    69,    70,    70,    71,
      72,    73,    73,    73,    73,    74,    74,    75,    76,    76,
      77,    78,    79,    80,    80,    81,    81,    81,    81,    82,
      82,    83,    83,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    86,    86,    87,
      88,    88,    89,    89,    90,    90,    91,    91,    91,    93,
      92,    95,    94,    96,    96,    96,    96,    97,    97,    98,
      99,    99,   100,   101,   102,   102,   104,   103,   105,   105,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     107,   107
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     2,     0,     1,     1,     1,     3,     2,
       1,     4,     3,     5,     6,     4,     3,     1,     1,     3,
       1,     1,     2,     1,     3,     1,     3,     1,     3,     4,
       3,     4,     3,     1,     1,     3,     2,     3,     3,     5,
       5,     5,     7,     2,     2,     3,     2,     1,     2,     3,
       1,     2,     1,     3,     2,     3,     1,     3,     2,     0,
       5,     0,     5,     1,     2,     3,     3,     1,     0,     2,
       1,     2,     4,     5,     3,     5,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     2,     5,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     3,     2,     1,     3,
       1,     3
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,    63,     0
};

/* Error token number */
#define YYTERROR 1



YYSTYPE yylval;

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

struct yyGLRStack;
static void yypstack (struct yyGLRStack* yystackp, size_t yyk)
  __attribute__ ((__unused__));
static void yypdumpstack (struct yyGLRStack* yystackp)
  __attribute__ ((__unused__));

#else /* !YYDEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif


#if YYERROR_VERBOSE

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
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
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;


  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

static void yyFail (yyGLRStack* yystackp, const char* yymsg)
  __attribute__ ((__noreturn__));
static void
yyFail (yyGLRStack* yystackp, const char* yymsg)
{
  if (yymsg != YY_NULL)
    yyerror (yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

static void yyMemoryExhausted (yyGLRStack* yystackp)
  __attribute__ ((__noreturn__));
static void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) __attribute__ ((__unused__));
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULL;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     __attribute__ ((__unused__));
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, size_t yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp)
{
  yybool yynormal __attribute__ ((__unused__)) =
    (yystackp->yysplitPoint == YY_NULL);
  int yylow;
  YYUSE (yyvalp);
  YYUSE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  switch (yyn)
    {
        case 2:
#line 168 "Tig.y" /* glr.c:788  */
    { CodeObj.Encode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); FreeNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1169 "Tig.cpp" /* glr.c:788  */
    break;

  case 3:
#line 169 "Tig.y" /* glr.c:788  */
    { CodeObj.AppendGlobal((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1175 "Tig.cpp" /* glr.c:788  */
    break;

  case 5:
#line 179 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr); }
#line 1181 "Tig.cpp" /* glr.c:788  */
    break;

  case 6:
#line 183 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.ClassIdNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1187 "Tig.cpp" /* glr.c:788  */
    break;

  case 7:
#line 187 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr);}
#line 1193 "Tig.cpp" /* glr.c:788  */
    break;

  case 8:
#line 188 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr)  = SyntaxObj.Operator(';', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1199 "Tig.cpp" /* glr.c:788  */
    break;

  case 9:
#line 192 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(INIT_STACK, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr));}
#line 1205 "Tig.cpp" /* glr.c:788  */
    break;

  case 10:
#line 196 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = InitMemberNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));  }
#line 1211 "Tig.cpp" /* glr.c:788  */
    break;

  case 11:
#line 200 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.CreateFnDefNode( (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr)); SymbTable.ClearCurrentFn(); }
#line 1217 "Tig.cpp" /* glr.c:788  */
    break;

  case 12:
#line 201 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.CreateFnDefNode( (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), NULL); SymbTable.ClearCurrentFn();}
#line 1223 "Tig.cpp" /* glr.c:788  */
    break;

  case 13:
#line 202 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = ClassOpNode( (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nPtr),NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr),0);NoParents = 0; }
#line 1229 "Tig.cpp" /* glr.c:788  */
    break;

  case 14:
#line 203 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = ClassOpNode( (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.nPtr),(((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr), NoParents); NoParents = 0; SyntaxObj.TotalMembs = 0;}
#line 1235 "Tig.cpp" /* glr.c:788  */
    break;

  case 15:
#line 212 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nPtr); }
#line 1241 "Tig.cpp" /* glr.c:788  */
    break;

  case 16:
#line 213 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr);  }
#line 1247 "Tig.cpp" /* glr.c:788  */
    break;

  case 17:
#line 217 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.CreateGlobalFnNameNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1253 "Tig.cpp" /* glr.c:788  */
    break;

  case 18:
#line 221 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr); }
#line 1259 "Tig.cpp" /* glr.c:788  */
    break;

  case 19:
#line 222 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr); }
#line 1265 "Tig.cpp" /* glr.c:788  */
    break;

  case 20:
#line 226 "Tig.y" /* glr.c:788  */
    { DeclParam((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str),NULL); }
#line 1271 "Tig.cpp" /* glr.c:788  */
    break;

  case 21:
#line 232 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = DeclClassNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1277 "Tig.cpp" /* glr.c:788  */
    break;

  case 22:
#line 236 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr);}
#line 1283 "Tig.cpp" /* glr.c:788  */
    break;

  case 23:
#line 240 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.ClassIdNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); NoParents++; AddParentToCurrentClass((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));}
#line 1289 "Tig.cpp" /* glr.c:788  */
    break;

  case 24:
#line 241 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), SyntaxObj.ClassIdNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))); NoParents++; AddParentToCurrentClass((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));}
#line 1295 "Tig.cpp" /* glr.c:788  */
    break;

  case 25:
#line 247 "Tig.y" /* glr.c:788  */
    { DeclDataMember((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));}
#line 1301 "Tig.cpp" /* glr.c:788  */
    break;

  case 26:
#line 248 "Tig.y" /* glr.c:788  */
    { DeclDataMember((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1307 "Tig.cpp" /* glr.c:788  */
    break;

  case 27:
#line 249 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr); }
#line 1313 "Tig.cpp" /* glr.c:788  */
    break;

  case 28:
#line 250 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr)  = SyntaxObj.Operator(';', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1319 "Tig.cpp" /* glr.c:788  */
    break;

  case 29:
#line 254 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(FUNC, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr)); SymbTable.ClearCurrentFn();}
#line 1325 "Tig.cpp" /* glr.c:788  */
    break;

  case 30:
#line 255 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(FUNC, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), NULL); SymbTable.ClearCurrentFn();}
#line 1331 "Tig.cpp" /* glr.c:788  */
    break;

  case 31:
#line 259 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nPtr);  }
#line 1337 "Tig.cpp" /* glr.c:788  */
    break;

  case 32:
#line 260 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr);  }
#line 1343 "Tig.cpp" /* glr.c:788  */
    break;

  case 33:
#line 264 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.CreateMembFnNameNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1349 "Tig.cpp" /* glr.c:788  */
    break;

  case 34:
#line 271 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';', 2, NULL, NULL); }
#line 1355 "Tig.cpp" /* glr.c:788  */
    break;

  case 35:
#line 272 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr); }
#line 1361 "Tig.cpp" /* glr.c:788  */
    break;

  case 36:
#line 273 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr); }
#line 1367 "Tig.cpp" /* glr.c:788  */
    break;

  case 37:
#line 274 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(PRINT, 1, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr)); }
#line 1373 "Tig.cpp" /* glr.c:788  */
    break;

  case 38:
#line 275 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr); }
#line 1379 "Tig.cpp" /* glr.c:788  */
    break;

  case 39:
#line 276 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(WHILE, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1385 "Tig.cpp" /* glr.c:788  */
    break;

  case 40:
#line 277 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(FOR, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1391 "Tig.cpp" /* glr.c:788  */
    break;

  case 41:
#line 278 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(IF, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1397 "Tig.cpp" /* glr.c:788  */
    break;

  case 42:
#line 279 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(IF, 3, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1403 "Tig.cpp" /* glr.c:788  */
    break;

  case 43:
#line 280 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr); }
#line 1409 "Tig.cpp" /* glr.c:788  */
    break;

  case 44:
#line 281 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(FN_RETURN,1,NULL); }
#line 1415 "Tig.cpp" /* glr.c:788  */
    break;

  case 45:
#line 282 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(FN_RETURN,1,(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr)); }
#line 1421 "Tig.cpp" /* glr.c:788  */
    break;

  case 46:
#line 283 "Tig.y" /* glr.c:788  */
    { yyerrok;}
#line 1427 "Tig.cpp" /* glr.c:788  */
    break;

  case 47:
#line 287 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr); }
#line 1433 "Tig.cpp" /* glr.c:788  */
    break;

  case 48:
#line 288 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1439 "Tig.cpp" /* glr.c:788  */
    break;

  case 49:
#line 299 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator('=', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1445 "Tig.cpp" /* glr.c:788  */
    break;

  case 50:
#line 303 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.IdentifierExpression((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1451 "Tig.cpp" /* glr.c:788  */
    break;

  case 51:
#line 304 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(ARROW, 2, SyntaxObj.IdentifierExpression((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.str)), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1457 "Tig.cpp" /* glr.c:788  */
    break;

  case 52:
#line 309 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.varAssignmentIdentifierNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1463 "Tig.cpp" /* glr.c:788  */
    break;

  case 53:
#line 312 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(MEMB_ASSIGN, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr),  SyntaxObj.MemberNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))); }
#line 1469 "Tig.cpp" /* glr.c:788  */
    break;

  case 54:
#line 318 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(ARROW,1, SyntaxObj.MemberNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))); FinalMembNode = ((*yyvalp).nPtr); }
#line 1475 "Tig.cpp" /* glr.c:788  */
    break;

  case 55:
#line 319 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';',2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr),SyntaxObj.Operator(ARROW,1, SyntaxObj.MemberNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)))); FinalMembNode = ((*yyvalp).nPtr)->op[1];}
#line 1481 "Tig.cpp" /* glr.c:788  */
    break;

  case 56:
#line 324 "Tig.y" /* glr.c:788  */
    {  ((*yyvalp).nPtr) = SyntaxObj.IdentifierExpression((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1487 "Tig.cpp" /* glr.c:788  */
    break;

  case 57:
#line 325 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';',2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr),SyntaxObj.Operator(ARROW,1, SyntaxObj.MemberNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))));  }
#line 1493 "Tig.cpp" /* glr.c:788  */
    break;

  case 58:
#line 327 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';',2,(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr),  SyntaxObj.Operator(ARRAY_ELEMENT,1,(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)));  }
#line 1499 "Tig.cpp" /* glr.c:788  */
    break;

  case 59:
#line 336 "Tig.y" /* glr.c:788  */
    {State.Push(); }
#line 1505 "Tig.cpp" /* glr.c:788  */
    break;

  case 60:
#line 337 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(FUNC_CALL,3,(((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.nPtr),(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr),State.Seq_Count);State.Pop(); }
#line 1511 "Tig.cpp" /* glr.c:788  */
    break;

  case 61:
#line 342 "Tig.y" /* glr.c:788  */
    {State.Push(); }
#line 1517 "Tig.cpp" /* glr.c:788  */
    break;

  case 62:
#line 344 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(FUNC_CALL_RET,3,(((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.nPtr),(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr),State.Seq_Count); State.Pop(); }
#line 1523 "Tig.cpp" /* glr.c:788  */
    break;

  case 63:
#line 349 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.CreateFnCallNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)) ; }
#line 1529 "Tig.cpp" /* glr.c:788  */
    break;

  case 64:
#line 350 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SupMembFnCallNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)) ; }
#line 1535 "Tig.cpp" /* glr.c:788  */
    break;

  case 65:
#line 353 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator('m', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), SyntaxObj.MemberNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)) ); }
#line 1541 "Tig.cpp" /* glr.c:788  */
    break;

  case 66:
#line 355 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.CreateSuperMembNode(SyntaxObj.IdentifierExpression((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.str)),(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1547 "Tig.cpp" /* glr.c:788  */
    break;

  case 67:
#line 361 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr);}
#line 1553 "Tig.cpp" /* glr.c:788  */
    break;

  case 68:
#line 362 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = NULL; }
#line 1559 "Tig.cpp" /* glr.c:788  */
    break;

  case 69:
#line 370 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';', 2,(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr),  SyntaxObj.Operator(PRINT,1,SyntaxObj.CreateStrNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))) ); }
#line 1565 "Tig.cpp" /* glr.c:788  */
    break;

  case 70:
#line 374 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr); }
#line 1571 "Tig.cpp" /* glr.c:788  */
    break;

  case 71:
#line 375 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';',2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1577 "Tig.cpp" /* glr.c:788  */
    break;

  case 72:
#line 379 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(PRINT, 2 ,  SyntaxObj.CreateStrNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.str)), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr)); }
#line 1583 "Tig.cpp" /* glr.c:788  */
    break;

  case 73:
#line 384 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';',3,(((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.nPtr),(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr),(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1589 "Tig.cpp" /* glr.c:788  */
    break;

  case 74:
#line 388 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr); }
#line 1595 "Tig.cpp" /* glr.c:788  */
    break;

  case 75:
#line 389 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';',2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr)); }
#line 1601 "Tig.cpp" /* glr.c:788  */
    break;

  case 76:
#line 393 "Tig.y" /* glr.c:788  */
    {State.Push(); }
#line 1607 "Tig.cpp" /* glr.c:788  */
    break;

  case 77:
#line 394 "Tig.y" /* glr.c:788  */
    {((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr); }
#line 1613 "Tig.cpp" /* glr.c:788  */
    break;

  case 78:
#line 398 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr); TableRows++;}
#line 1619 "Tig.cpp" /* glr.c:788  */
    break;

  case 79:
#line 399 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(';',2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); TableRows++;}
#line 1625 "Tig.cpp" /* glr.c:788  */
    break;

  case 80:
#line 406 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.IntegerConstant((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.iValue)); }
#line 1631 "Tig.cpp" /* glr.c:788  */
    break;

  case 81:
#line 407 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.CreateStrNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str));}
#line 1637 "Tig.cpp" /* glr.c:788  */
    break;

  case 82:
#line 408 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.FloatConstant((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.fValue)); }
#line 1643 "Tig.cpp" /* glr.c:788  */
    break;

  case 83:
#line 409 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.IdentifierExpression((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)); }
#line 1649 "Tig.cpp" /* glr.c:788  */
    break;

  case 84:
#line 410 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr); }
#line 1655 "Tig.cpp" /* glr.c:788  */
    break;

  case 85:
#line 411 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(NEW,1,SyntaxObj.ClassIdNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str)));}
#line 1661 "Tig.cpp" /* glr.c:788  */
    break;

  case 86:
#line 412 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) =  SyntaxObj.Operator(NEW,2,(((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nPtr),(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr));}
#line 1667 "Tig.cpp" /* glr.c:788  */
    break;

  case 87:
#line 415 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(ARROW, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr),  SyntaxObj.MemberNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str))); }
#line 1673 "Tig.cpp" /* glr.c:788  */
    break;

  case 88:
#line 416 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(UMINUS, 1, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1679 "Tig.cpp" /* glr.c:788  */
    break;

  case 89:
#line 417 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator('+', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1685 "Tig.cpp" /* glr.c:788  */
    break;

  case 90:
#line 418 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator('-', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1691 "Tig.cpp" /* glr.c:788  */
    break;

  case 91:
#line 419 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator('*', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1697 "Tig.cpp" /* glr.c:788  */
    break;

  case 92:
#line 420 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator('/', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1703 "Tig.cpp" /* glr.c:788  */
    break;

  case 93:
#line 421 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator('%', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1709 "Tig.cpp" /* glr.c:788  */
    break;

  case 94:
#line 422 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator('<', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1715 "Tig.cpp" /* glr.c:788  */
    break;

  case 95:
#line 423 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator('>', 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1721 "Tig.cpp" /* glr.c:788  */
    break;

  case 96:
#line 424 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(AND, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1727 "Tig.cpp" /* glr.c:788  */
    break;

  case 97:
#line 425 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(OR, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1733 "Tig.cpp" /* glr.c:788  */
    break;

  case 98:
#line 426 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(GE, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1739 "Tig.cpp" /* glr.c:788  */
    break;

  case 99:
#line 427 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(LE, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1745 "Tig.cpp" /* glr.c:788  */
    break;

  case 100:
#line 428 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(NE, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1751 "Tig.cpp" /* glr.c:788  */
    break;

  case 101:
#line 429 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(EQ, 2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1757 "Tig.cpp" /* glr.c:788  */
    break;

  case 102:
#line 431 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr); }
#line 1763 "Tig.cpp" /* glr.c:788  */
    break;

  case 103:
#line 432 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(DATA_TYPE,1,(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1769 "Tig.cpp" /* glr.c:788  */
    break;

  case 104:
#line 433 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(STR_INPUT,0); }
#line 1775 "Tig.cpp" /* glr.c:788  */
    break;

  case 105:
#line 437 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = NewListArrayNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr),State.Seq_Count);State.Pop(); }
#line 1781 "Tig.cpp" /* glr.c:788  */
    break;

  case 106:
#line 438 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = NewListTableNode((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr),State.Seq_Count,TableRows);  TableRows=0;}
#line 1787 "Tig.cpp" /* glr.c:788  */
    break;

  case 107:
#line 440 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = SyntaxObj.Operator(ARRAY_ELEMENT,2,(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nPtr),(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1793 "Tig.cpp" /* glr.c:788  */
    break;

  case 108:
#line 441 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = RandNode((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.str), NULL,NULL); }
#line 1799 "Tig.cpp" /* glr.c:788  */
    break;

  case 109:
#line 442 "Tig.y" /* glr.c:788  */
    { ((*yyvalp).nPtr) = RandNode(NULL,(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr),(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); }
#line 1805 "Tig.cpp" /* glr.c:788  */
    break;

  case 110:
#line 447 "Tig.y" /* glr.c:788  */
    {((*yyvalp).nPtr) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr); State.Seq_Count++; }
#line 1811 "Tig.cpp" /* glr.c:788  */
    break;

  case 111:
#line 448 "Tig.y" /* glr.c:788  */
    {((*yyvalp).nPtr) = SyntaxObj.Operator(';',2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nPtr), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nPtr)); State.Seq_Count++; }
#line 1817 "Tig.cpp" /* glr.c:788  */
    break;


#line 1821 "Tig.cpp" /* glr.c:788  */
      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
                &yys->yysemantics.yysval);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YYFPRINTF (stderr, "%s unresolved ", yymsg);
          else
            YYFPRINTF (stderr, "%s incomplete ", yymsg);
          yy_symbol_print (stderr, yystos[yys->yylrState],
                           YY_NULL);
          YYFPRINTF (stderr, "\n");
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-56)))

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yytable_value) \
  0

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yypact_value_is_default (yypact[yystate])
      || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yylhs)
{
  int yyr = yypgoto[yylhs - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yylhs - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, size_t yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) YYMALLOC (16 * sizeof yyset->yystates[0]);
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULL;
  yyset->yylookaheadNeeds =
    (yybool*) YYMALLOC (16 * sizeof yyset->yylookaheadNeeds[0]);
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, size_t yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems =
    (yyGLRStackItem*) YYMALLOC (yysize * sizeof yystackp->yynextFree[0]);
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULL;
  yystackp->yylastDeleted = YY_NULL;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yynewSize;
  size_t yyn;
  size_t yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems = (yyGLRStackItem*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(yybool *) yyp0)
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULL)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULL)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULL)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULL)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULL)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                 yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULL)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULL && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULL)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULL;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULL || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULL;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULL)
        {
          if (yyi == yyj)
            {
              YYDPRINTF ((stderr, "Removing dead stacks.\n"));
            }
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            {
              YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
                          (unsigned long int) yyi, (unsigned long int) yyj));
            }
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
            size_t yyposn,
            YYSTYPE* yyvalp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
                 size_t yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULL;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print Args;               \
} while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (int yynormal, yyGLRStackItem* yyvsp, size_t yyk,
                 yyRuleNum yyrule)
{
  int yynrhs = yyrhsLength (yyrule);
  int yyi;
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
             (unsigned long int) yyk, yyrule - 1,
             (unsigned long int) yyrline[yyrule]);
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyvsp[yyi - yynrhs + 1].yystate.yylrState],
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval
                                              );
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YYFPRINTF (stderr, " (unresolved)");
      YYFPRINTF (stderr, "\n");
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULL)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
      YYASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((1, yyrhs, yyk, yyrule));
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp,
                           yyvalp);
    }
  else
    {
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((0, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
             yybool yyforceEval)
{
  size_t yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULL)
    {
      YYRESULTTAG yyflag;
      YYSTYPE yysval;

      yyflag = yydoAction (yystackp, yyk, yyrule, &yysval);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULL)
        {
          YYDPRINTF ((stderr, "Parse on stack %lu rejected by rule #%d.\n",
                     (unsigned long int) yyk, yyrule - 1));
        }
      if (yyflag != yyok)
        return yyflag;
      YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
                  "Reduced stack %lu by rule #%d; action deferred.  "
                  "Now in state %d.\n",
                  (unsigned long int) yyk, yyrule - 1, yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULL)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
                                (unsigned long int) yyk,
                                (unsigned long int) yyi));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static size_t
yysplitStack (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yysplitPoint == YY_NULL)
    {
      YYASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yysize >= yystackp->yytops.yycapacity)
    {
      yyGLRState** yynewStates;
      yybool* yynewLookaheadNeeds;

      yynewStates = YY_NULL;

      if (yystackp->yytops.yycapacity
          > (YYSIZEMAX / (2 * sizeof yynewStates[0])))
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      yynewStates =
        (yyGLRState**) YYREALLOC (yystackp->yytops.yystates,
                                  (yystackp->yytops.yycapacity
                                   * sizeof yynewStates[0]));
      if (yynewStates == YY_NULL)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yystates = yynewStates;

      yynewLookaheadNeeds =
        (yybool*) YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                             (yystackp->yytops.yycapacity
                              * sizeof yynewLookaheadNeeds[0]));
      if (yynewLookaheadNeeds == YY_NULL)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize-1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yysval = yys0->yysemantics.yysval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yysval = yys1->yysemantics.yysval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULL)
                break;
              else if (*yyz0p == YY_NULL)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
                                   yyGLRStack* yystackp);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp);
    yychar = yychar_current;
    yylval = yylval_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULL)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1, (unsigned long int) (yys->yyposn + 1),
               (unsigned long int) yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]));
          else
            YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]),
                       (unsigned long int) (yystates[yyi-1]->yyposn + 1),
                       (unsigned long int) yystates[yyi]->yyposn);
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULL; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              return yyreportAmbiguity (yybest, yyp);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YYASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULL; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yystos[yys->yylrState],
                                &yysval);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULL;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp)
{
  if (yystackp->yysplitPoint != YY_NULL)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             ));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULL)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULL;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = ((yyGLRStackItem*) yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULL;
  yystackp->yylastDeleted = YY_NULL;

  while (yyr != YY_NULL)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, size_t yyk,
                   size_t yyposn)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULL)
    {
      yyStateNum yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
                  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule]);
          if (yyflag == yyerr)
            {
              YYDPRINTF ((stderr,
                          "Stack %lu dies "
                          "(predicate failure or explicit user error).\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yySymbol yytoken;
          int yyaction;
          const short int* yyconflicts;

          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;
          if (yychar == YYEMPTY)
            {
              YYDPRINTF ((stderr, "Reading a token: "));
              yychar = yylex ();
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

          yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);

          while (*yyconflicts != 0)
            {
              YYRESULTTAG yyflag;
              size_t yynewStack = yysplitStack (yystackp, yyk);
              YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
                          (unsigned long int) yynewStack,
                          (unsigned long int) yyk));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts]);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn));
              else if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr, "Stack %lu dies.\n",
                              (unsigned long int) yynewStack));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
              yyconflicts += 1;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction]);
              if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr,
                              "Stack %lu dies "
                              "(predicate failure or explicit user error).\n",
                              (unsigned long int) yyk));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

static void
yyreportSyntaxError (yyGLRStack* yystackp)
{
  if (yystackp->yyerrState != 0)
    return;
#if ! YYERROR_VERBOSE
  yyerror (YY_("syntax error"));
#else
  {
  yySymbol yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);
  size_t yysize0 = yytnamerr (YY_NULL, yytokenName (yytoken));
  size_t yysize = yysize0;
  yybool yysize_overflow = yyfalse;
  char* yymsg = YY_NULL;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected").  */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
      yyarg[yycount++] = yytokenName (yytoken);
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for this
             state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;
          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytokenName (yyx);
                {
                  size_t yysz = yysize + yytnamerr (YY_NULL, yytokenName (yyx));
                  yysize_overflow |= yysz < yysize;
                  yysize = yysz;
                }
              }
        }
    }

  switch (yycount)
    {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  {
    size_t yysz = yysize + strlen (yyformat);
    yysize_overflow |= yysz < yysize;
    yysize = yysz;
  }

  if (!yysize_overflow)
    yymsg = (char *) YYMALLOC (yysize);

  if (yymsg)
    {
      char *yyp = yymsg;
      int yyi = 0;
      while ((*yyp = *yyformat))
        {
          if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
              yyp += yytnamerr (yyp, yyarg[yyi++]);
              yyformat += 2;
            }
          else
            {
              yyp++;
              yyformat++;
            }
        }
      yyerror (yymsg);
      YYFREE (yymsg);
    }
  else
    {
      yyerror (YY_("syntax error"));
      yyMemoryExhausted (yystackp);
    }
  }
#endif /* YYERROR_VERBOSE */
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp)
{
  size_t yyk;
  int yyj;

  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yySymbol yytoken;
        if (yychar == YYEOF)
          yyFail (yystackp, YY_NULL);
        if (yychar != YYEMPTY)
          {
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval);
          }
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = yylex ();
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
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
    if (yystackp->yytops.yystates[yyk] != YY_NULL)
      break;
  if (yyk >= yystackp->yytops.yysize)
    yyFail (yystackp, YY_NULL);
  for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystackp, yyk);
  yyremoveDeletes (yystackp);
  yycompressStack (yystackp);

  /* Now pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULL)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYTERROR;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yytable[yyj],
                          yys->yyposn, &yylval);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      if (yys->yypred != YY_NULL)
        yydestroyGLRState ("Error: popping", yys);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULL)
    yyFail (yystackp, YY_NULL);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  size_t yyposn;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode */
      while (yytrue)
        {
          yyRuleNum yyrule;
          int yyaction;
          const short int* yyconflicts;

          yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
          YYDPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {

                  yyreportSyntaxError (&yystack);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue));
            }
          else
            {
              yySymbol yytoken;
              if (yychar == YYEMPTY)
                {
                  YYDPRINTF ((stderr, "Reading a token: "));
                  yychar = yylex ();
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

              yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
              if (*yyconflicts != 0)
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {

                  yyreportSyntaxError (&yystack);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue));
            }
        }

      while (yytrue)
        {
          yySymbol yytoken_to_shift;
          size_t yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));

              yyreportSyntaxError (&yystack);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              int yyaction;
              const short int* yyconflicts;
              yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
              yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval);
              YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                          (unsigned long int) yys,
                          yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          size_t yysize = yystack.yytops.yysize;
          size_t yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                  if (yys->yypred != YY_NULL)
                      yydestroyGLRState ("Cleanup: popping", yys);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULL)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULL ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
        {
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long int) yyp->yystate.yyposn,
                     (long int) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long int) YYINDEX (yyp->yyoption.yystate),
                     (long int) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif

#undef yylval
#undef yychar
#undef yynerrs



#line 451 "Tig.y" /* glr.c:2549  */










/** Create a function node for a call to the named superclass member function.  */
CSyntaxNode *SupMembFnCallNode(char* Name) {
    CSyntaxNode *Node = new CSyntaxNode(typeId);

	//Search for it as a member func of the parent class first.
	SymDesc* Fn = SymbTable.Find (CURRENT_CLASS_PARENT, Name);
	if (Fn != NULL) {
		Node->symbol = 0;
		Node->value = Fn->MemberNo;
		Node->NodeType = typeSuperMemb;
		return Node;
	}	


	//Not found? 
	Error("'%s' referenced as a function of the parent class, but no such function found.",Name);
	return Node;
}


/** Create a symbol table entry for this parameter. No need to create a syntax node as this requires no code.*/
void DeclParam(char* Name, char* Ptr) {
	if (SymbTable.Find (CURRENT_FN,Name) == NULL) {  //if this parameter name isn't already assigned to the current function...
		SymDesc* Param = new SymDesc (Name, PAR,  lineno);
		bool Result = SymbTable.Add(CURRENT_FN, Param); 
		if (!Result) {
			Error("Too many parameters!");
			return;
		}

	}
	else
		Error("'%s' already declared as a parameter name for this function.",Name);

}


/** Create a syntax node for this class declaration; enter the class on the symbol table.  */
CSyntaxNode* DeclClassNode(char* Name) {
	CSyntaxNode *Node = new CSyntaxNode(typeId);

	if ( SymbTable.Find (GLOBAL_SCOPE, Name) == NULL)   { // Class doesn't exist yet; create it
		SymDesc* Class = new SymDesc (Name, CLASS_SYM,  lineno);
		Node->symbol = Class;
		SymbTable.Add ( GLOBAL_SCOPE, Class);
	}
	else
		Error("Global identifier '%s' is already in use.",Name); 

    return Node;
}


/** Create a symbol table entry for the named class data-member. No need to create a syntax node as this requires no code.*/
void DeclDataMember(char* name) {
 	if ( (SymbTable.Find (CURRENT_CLASS,name) == NULL) && (SymbTable.Find (CURRENT_CLASS_PARENT,name) == NULL) ) {
		SymDesc* symbol = new SymDesc (name, DATA_MEMBER,  lineno);
		SymbTable.Add(CURRENT_CLASS, symbol);
	}
	else
		Error("'%s' is already declared as a member name for this class, or a parent class.",name);
}


//Create class declaration operator node
CSyntaxNode* ClassOpNode(CSyntaxNode* Name, CSyntaxNode* Parents, CSyntaxNode* Members, int ParentCount) {
    CSyntaxNode* Node = new CSyntaxNode(typeOpr);
	 Node->oper = CLASS;
    Node->nops = 3;
	Node->value = ParentCount;

	Node->op[0] = Name;
	Node->op[1] = Parents;
	Node->op[2] = Members;


	Name->symbol->Value = Name->symbol->NoDataMembers  ;

	if (ParentCount > 0)
			Name->symbol->Value += SyntaxObj.TotalMembs; //calculate total data members including inherited. Needed to calculate storage space for instances.

	//Now that we've finished defining this class, it's no longer the current class:
	SymbTable.ClearCurrentClass();
	
	return Node;
}

/** Create array declaration operator node */
CSyntaxNode* DeclArrayNode(CSyntaxNode* Dimension) {
    CSyntaxNode* Node = new CSyntaxNode(typeOpr);
	Node->oper = ARRAY;
    Node->nops = 1;

	Node->op[0] = Dimension;
	
	return Node;
}

/** Create table declaration operator node */
CSyntaxNode* DeclTableNode(CSyntaxNode* Rows, CSyntaxNode* Columns) {
    CSyntaxNode* Node = new CSyntaxNode(typeOpr);
	Node->oper = TABLE;
    Node->nops = 2;

	Node->op[0] = Rows;
	Node->op[1] = Columns;
	
	return Node;
}


/** Create a node for a random number generation. */
CSyntaxNode* RandNode(char* Str,CSyntaxNode* Throws, CSyntaxNode* Dice)
{
    CSyntaxNode* Node = new CSyntaxNode(typeOpr);
	Node->oper = RAND;
    Node->nops = 2;

	char* EndStr;
	if (Str != NULL) {
		long n = strtol(Str, &EndStr, 10);
		long r = strtol(EndStr+1, NULL, 10);
		if (( n <= INT_MIN) || (n >= INT_MAX ) || ( r <= INT_MIN) || (r >= INT_MAX ))
				Error("Number out of range in random number generation.");	
			
		Node->op[0] = SyntaxObj.IntegerConstant(n);
		Node->op[1] = SyntaxObj.IntegerConstant(r);
	}
	else {
		Node->op[0] = Throws;
		Node->op[1] = Dice;
	}
		
	return Node;
}

CSyntaxNode* InitMemberNode(char* MemberName)
{
	CSyntaxNode *Node = new CSyntaxNode(typeMemb);
	SymDesc* Member = SymbTable.Find(CURRENT_OBJ,MemberName); //Does this member belong to the class of the current object?
	if ( Member == NULL) {								  
		Error("%s is not a member of %s",MemberName,SymbTable.CurrentObj->Name);
		return Node;
	}
	
	//Node = new CSyntaxNode(typeMemb);
	//Node->symbol = Obj->symbol; 
	Node->value = Member->MemberNo;
	return Node;
}

//Add a parent class to the current class.
void AddParentToCurrentClass(char* ParentName)
{	
	SymDesc* ParentClass	 = SymbTable.Find (GLOBAL_SCOPE,ParentName);	 	//get the class symbol for the parent
	bool Result = SymbTable.Add ( CURRENT_CLASS_PARENT, ParentClass); //add it to the symbol table
}


//Simple kludge that removes the final ARROW operation where a value is being assigned to a obj->member.
//This is because we don't want the value of the member on the stack, which is the default value.
//This way, the last thing on the stack will be the member number.
void RemoveFinalGetproperty() {
	if (FinalMembNode)
		FinalMembNode->oper = ';';

}

/** Create array declaration operator node */
CSyntaxNode* NewListArrayNode(CSyntaxNode* Initialisation, int Dimension) {
    CSyntaxNode* Node = new CSyntaxNode(typeOpr);
	Node->oper = ARRAY_LIST;
    Node->nops = 1;

	Node->op[0] = Initialisation;
	Node->value = Dimension;
	
	return Node;
}


CSyntaxNode* NewListTableNode(CSyntaxNode* Initialisation, int Cols, int Rows) { 
   CSyntaxNode* Node = new CSyntaxNode(typeOpr);
	Node->oper = TABLE_LIST;
    Node->nops = 1;

	Node->op[0] = Initialisation;
	Node->value = Cols;
	Node->value2 = Rows;
	
	return Node;
}

/** Delete this node and any sub-nodes, freeing the memory. */
void FreeNode(CSyntaxNode *p) {
    int i;

    if (!p) return; 
	if (p->NodeType == typeOpr) {
        for (i = 0; i < p->nops; i++)
            FreeNode(p->op[i]);
    }
	
	delete p;
}



