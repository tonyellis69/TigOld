#ifndef _LEX_H_
#define _LEX_H_

#include <stdio.h>
#include "Coder.h"
#include "StringTable.h"



// export some global variables that we use in flex and bison. 
extern int lineno;
extern char* linestr;
extern char *yytext; //Should whatever string Flex has just tokenised. 


extern FILE *yyin;  // The file we scan from.

extern CCoder CodeObj;
extern CStringTable StrTable;
extern CSymbolTable SymbTable;

// Function prototype

int yylex ();
int yyparse ();








#endif