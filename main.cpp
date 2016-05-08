#include <stdio.h>
#include "SyntaxNode.h"
#include "Tig.hpp"

#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include "main.h"
#include "Coder.h"


int ErrorCount = 0; //The number of syntax errors detected during parsing.


/** Write a parser-generated compiler error to stdout. Adds the line number to parser's error message. */
void Error (const char *format, ...)   {
   va_list args;
   ErrorCount++;
   printf ("\nError, line %d:\n", lineno);
   printf ("%s\n",linestr);
   va_start(args, format);
   vfprintf(stdout, format, args);
   va_end(args);
   printf("\n");
   exit (false);
}  


/** Called by the parser when an error occurs. */
void yyerror(const char *msg) {
   Error (msg);
}


  
/** Compile the given source code file into bytecode. */
int main (int argc, char *argv[])  {
	char OutFile[40];
	bool TokeniseOnly = false;


	//parse commandline
	for (int p=1;p < argc;p++) { //for each parameter...
		if (strcmp(argv[p], "-d") == 0) //user wants to see the syntax tree diagram
			CodeObj.Diagram = true;
		if (strcmp(argv[p], "-t") == 0) //user just wants to see the tokens
			TokeniseOnly = true;
	 }
	yyin = NULL;
	yyin = fopen (argv[argc-1], "rt"); //attemp to open the given file
	if (yyin == NULL) {
	   printf("\nFile not found");
      return 0;
   }

	if (TokeniseOnly) {
		int x = yylex();
		while(x>0) {
			if (x == STRING)
				printf("\n %d %s ",x,yylval.str); 
			else
				printf("\n %d %s",x,yytext); 
			 x = yylex();
	}

		return 0;

	}


	strcpy(OutFile,argv[argc-1]); //construct the output filename from the input filename, suffixing '.tig'.
	char* Suffix = strrchr(OutFile,'.');
	strcpy(Suffix+1,"tig");

	CodeObj.OpenFile(OutFile); //pass the output file to the coder.
	CodeObj.SetSymbolTable(&SymbTable); //initialise the coder.
	CodeObj.GetStrTablePtr(StrTable.GetData()); //Get a pointer to the string table. TO DO: still needed?

	int tmp = (int)CodeObj.CodeFile.tellp();
 
	//Run the parser!
	yyparse (); //It will parse the text found at yyin.
  
  //We don't return here until all parsing has finished and all bytecode (except for any global statements) has been written to file.
  
	//Now we encode global statements, if any, so they end up on the end of the file
	//TO DO: consider creating CodeObj here in main, rather than in Tig.Y, as the scanner shouldn't need to know about it.

	
	CodeObj.EncodeGlobal();
	CodeObj.CloseFile(); //close the file (filling-out the header details first).
  
  if (!ErrorCount) {
	  printf("\n\n%s compiled successfully!\n\n",OutFile);
  }
  return 0;
}