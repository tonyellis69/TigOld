%{				// Defintitions Section: substitutions, code and start states.  
				//   Anything inside these curly brackets is copied to the generated C file. 
			   
#include <stdlib.h>		
#include "SyntaxNode.h"
#include "Tig.hpp"
#include <io.h>       // isatty
#include <limits.h>  //INT_MIN etc
#include <math.h> //HUGE_VAL 

#define  isatty _isatty  // for some reason isatty is called _isatty in VC..

void yyerror(const char *);


char buf[512]; //for temporarily storing string constants
char* bufptr;


int lineno = 1; //Keeps track of line numbers

char* linestr = 0;
int ArrayBracketsOpen = 0; //keeps track of how many square brackets are open in expressions

%}

%option stack yy_scan_string





	/* Substitutions simplify pattern-matching rules, eg, letter [A-Za-z] or digit [0-9] */
LETTER   [a-zA-Z_]
DIGIT    [0-9]
IDENT    {LETTER}({LETTER}|{DIGIT})*
EOL		'\n'


	/*Strings can require more lexxing due to escape sequences and inset expressions , so create an exclusive state for them.*/

%x STRS	OPEN_INSET COMMENT
%s INSET 

%%
						/* Rules Section: 
						   Here we tell Flex what tokens to look out for and what to do when it finds them. */


^.*		{ // Get & save entire line
			linestr = _strdup (yytext);
			yyless(0);
		}



"/*"					BEGIN(COMMENT);
<COMMENT>[^*\n]*        /* eat anything that's not a '*' */
<COMMENT>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<COMMENT>\n             ++lineno;
<COMMENT>"*"+"/"        BEGIN(INITIAL);

"//"					{	char c;  //eat //comments
							while ((c = yyinput()) != '\n' && c != 0);
							lineno++;
						}

[0-9]+"."[0-9]+		{ /* Matches a floating-point number */
						double n = strtod (yytext, NULL);						
						if (( n == HUGE_VAL) || (n == -HUGE_VAL ) )
							yyerror ("Number out of range!");
						yylval.fValue = (float) n;
						return FLOAT;
					}

[0-9]+      {   /* Matches one or more digits */
                long n = strtol (yytext, NULL, 10);
				if (( n <= INT_MIN) || (n >= INT_MAX ) )
					yyerror ("Number out of range!");
				yylval.iValue = n;
                return INTEGER;
            }

[0-9]+"d"[0-9]+	{  /* matches the random number pattern:  integer 'd' integer, eg 1d20. */
					yylval.str = new char[strlen(yytext)+1];
					strcpy (yylval.str, yytext);
					return RAND;
				}	

[-()<>=+*/%;{}.,] {	/* Matches any one of these nonalphanumeric characters - they're simply returned as themselves rather than a defined token*/
                return *yytext;    /* yytext is a pointer to the string that has been matched */
             }


">="            return GE;    /* Matches the literal string inside " " */
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"&&"			return AND;
"||"			return OR;
"while"         return WHILE;
"for"			return FOR;
"if"            return IF;
"else"          return ELSE;
"print"         return PRINT;
"return"		return FN_RETURN;
"local"			return LOCAL_VAR;
"class"			return CLASS;
"based on"		return BASED_ON;
"has"			return HAS;
"new"			return NEW;
"->"			return ARROW;
"::"			return SUPERCLASS;
"type"			return DATA_TYPE;
"input"			return STR_INPUT;
"array"			return ARRAY;
"table"			return TABLE;
"with"			return WITH;
{IDENT}			{ 	/* 4 ie, a variable or a function name. */
                yylval.str = new char[strlen(yytext)+1];
				strcpy (yylval.str, yytext);
                return IDENTIFIER;
				}
")d("			return RAND2;
"-@"			return PLIB;




\"			{BEGIN STRS; bufptr = buf; ArrayBracketsOpen = 0; }	//We've started lexxing a string. Buffer initialised.

<STRS>\\n	{ *bufptr++ = '\n'; }			//Newline escape sequence? Replace it with the actual Ascii code.
<STRS>\\t	{ *bufptr++ = '\t'; }			//Same for tabs.

<STRS>\"|\[	{								//End of string. But it will resume if we've reached an inset expression.
				*bufptr = 0;				//End the text we've buffered so far with an end-of-string marker.
				int l = strlen(buf);
				yylval.str = new char[l+1];
				strncpy (yylval.str, (char*)buf, l); yylval.str[l] = 0; //Give the text to Yacc.
				

				if (*yytext == '[')  {		//String was interrupted by an inset expression 
				  BEGIN INSET;			//Prepare to start inset-lexxing mode
				  unput('[');				//Put [ back in the input so that it can be the next thing we return.#1 				
				  return STRING;			//Return the current buffered text as a string.
				}
				  else  {
				  BEGIN INITIAL;			//The string ended normally with a quote, so no more to be done.
				  return STRING;
				}
			}

<STRS>.		{ *bufptr++ = *yytext;}			//Any normal text we just add to our string.

											
<OPEN_INSET>\[	{	BEGIN INSET;			//SCRAPPED We're starting to lexx an inset expression...
					return '[' ;			//So send a [, then start parsing inset expression normally
				}

\[				{ 	ArrayBracketsOpen++;   //This will return the '[' we put back in input at #1, thus bracketing the inset 
					return *yytext; 	   //expression to follow, avoiding a shift-reduce error in Bison.													
				}

<INSET>\]				{	if (ArrayBracketsOpen < 2) { //it's not the close of an open array index
							    BEGIN STRS; bufptr = buf;  //must be the end of an inset expression then
							}								//so start handling the next part of the string it's embedded in
							ArrayBracketsOpen--;
							return ']'; // Returning this after an inset expression enables us to avoid a shift/reduce error
						}

"]"				{	ArrayBracketsOpen--; //An 'ordinary' square bracket, ie, the end of an array index, not an inset expression.
					return *yytext;   
				}


\n					{ lineno++;}   //keep track of line number


[ \t]+        ;       /* ignore whitespace */

.         yyerror("Unknown character"); 

%%
			/* Subroutines Section */

int yywrap(void) {   // yywrap is called by Lex when input is exhausted, eg, end of file. reset yyin (the input FILE*) and return 0  
					/// if you want to process another file; otherwise just return 1. 

return 1;
  
}






