%{			// Definitions Section: -  token declarations and C code 
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



%}

%error-verbose			//Parser will give detailed error messages to user input

	// Definition of YYSTYPE - the type used for symbols, which enables them to hold various values. 
	// Causes this definition to appear in y.tab.h as a C union with these members: 
%union {				 						
    int iValue;                 // integer value - for numeric constants etc 
	float fValue;				//float value - for floating-point constants
    CSyntaxNode *nPtr;          // node pointer - enables symbols to point to syntax nodes
	char    *str;				// a character string
	int iValue2;				//dual integer value, needed for second digit in the random number generator, eg, 1d20
};								//TO DO: wrong!!! can't have to ints in a union! fix!!!!!!

			
	//A terminal symbol (also known as a token type) represents a class of syntactically equivalent tokens (eg, all function names,
	//variable names etc, are represented by the IDENTIFIER token). We use the symbol in grammar rules to mean that a token in 
	//that class is allowed. The symbol is represented in the Bison parser by a numeric code, which the yylex function returns.

	//A nonterminal symbol stands for a class of syntactically equivalent groupings (eg, all expressions are represented by
	//expr). The symbol name is used in writing grammar rules. By convention, it should be all lower case. 


	 //The tokens below will appear in y_tab.h as #defines. Lex has access to y_tab.h, so when Yacc calls yylex, 
	//yylex finds the next token and returns its #define number. The token may or may not have its own value. Eg, the number 42 
	//returns the #define value for the INTEGER token, but it also has the value 42, which is returned in the variable yylval.
	
%token <iValue> INTEGER  	// Associates INTEGER symbols with type iValue. ie they can now hold an integer value.  
%token <str> IDENTIFIER STRING	// Associates these symbols with the str type.   
%token <fValue> FLOAT
%token <str> RAND
%token WHILE FOR IF PRINT PRINT_VALERIC FUNC_CALL FUNC_CALL_RET FN_RETURN LOCAL_VAR CLASS HAS WITH //none of these need a type.
%token ARROW 
%token BASED_ON ARRAY TABLE
%token SUPERCLASS DATA_TYPE STR_INPUT
%token RESERVED_ADD RESERVED_SIZE MEMB_ASSIGN PLIB DEREF_ASSIGN ARRAY_ASSIGN ARRAY_ELEMENT ARRAY_LIST TABLE_LIST
%nonassoc IFX 
%nonassoc ELSE PRINT_COMPLEX FUNC NEW 

%left GE LE EQ NE '>' '<'  OR AND RAND2    // '%left' makes these tokens left associative
%left '+' '-'				  // this ensures that long complex sums are never ambiguous. 
%left '*' '/' '%' 
%left ','
%nonassoc UMINUS			// Last definition has the highest precedence. %nonassoc means no associativity is implied.
							// NB Lex is not programmed to find UMINUS tokens, but when '-' is used to indicate a negative number instead 	
							// of subtraction (see below), the %prec command is used give this rule the precedence of UMINUS, 
							// trumping all others. 

	//Declare the nonterminal symbols whose members have a specific type. They're type node-pointer so that when syntax tree
	//nodes are created to represent operands, they can take a pointer to the node and make it available to the parent node.
	//Eg: Consider x = 5; 'x' and '5' are recognised as expressions, resulting in a node for each. x = 5 is also an 
	//expression, resulting in its own node which can be given the pointers to the x and 5 nodes. 
	//The result is a tree of syntax nodes - exactly what we need.
	//Other nonterminal symbols, like 'code' and 'program', don't have a type because they don't have anything to do with the
	//syntax tree, so they can be declared implicitly.
%type <nPtr> stmt expr stmt_list  complex_str ui_list ui function_def func_name  
%type <nPtr> function_call definition call_param_list function_call_return call_func_name
%type <nPtr> class_name_dec data_list  var_or_member  param_list class_parents class_list class_name
%type <nPtr> param_name member_func member_func_decl member_func_name for_rules assignment dimension_list assignment_var_or_member
%type <nPtr> global_statement 
%type <nPtr> init_list init_pair data_member memberOf deref 
%type <nPtr> expr_sequence array_list
%type <nPtr>  table_list 
%nonassoc NON_SEQ
%glr-parser


%%
										/* Rules Section */
		//Yacc tries to match the stream of tokens from yylex to the 'rules' below. Many rules are actually made up of 
		//several smaller rules. For example, the rule that identifies a while loop is made up of rules identifying expressions
		//and statements. Yacc recurses into each 'child' rule as it goes to find matches, and then climbs back out. 
		// Each time it makes a match, we create an appropriate node, and put it on the $$ stack, a stack of elements
		//of type YYSTYPE. Thus, as the parser 'climbs out' of the smaller rules into their parent rules, or 'reduces'
		//them, action it finds is placed on the stack as a series of nodes which the node of the parent rule is then
		//made to point to. These parent rule nodes will themselves be pointed to by nodes higher up the chain. 
		//For example, 'Print 2+3': the nodes for 2 and 3 go on the stack, then the node for +, which, as parent, will 
		//point to those 2 nodes. Then the node for Print will go on the stack, and it will point to the + node. 
		//The practical upshot is that statements end up as a synyax tree with the most basic parts as the leaves. 
		//When you walk that tree you get Print, +, 2,3, which can be used to create machine code intstructions.


		//The grammar rules that define our language:

code:										// Our first rule: code is zero or more definitions and/or global statements
		code definition						{ CodeObj.Encode($2); FreeNode($2); }   //Once we've matched a whole definition, encode it into bytecode.
		| code global_statement				{ CodeObj.AppendGlobal($2); } //global statements are collected, then encoded last
	//	| code global_statement				{  CodeObj.Encode($2); FreeNode($2); }//For now, encode them at the same time
        | /* NULL */																  
        ;
        
											//global objects, what was I thinking? Mothball all this for now
										
global_statement:							//Global statements such as creating a new global object
		//  class_name IDENTIFIER ';'			{ $$ =  SyntaxObj.Operator('=', 2,SyntaxObj.varAssignmentIdentifierNode($2), SyntaxObj.Operator(NEW,1,$1) );} 
		//| class_name IDENTIFIER '(' init_list ')' ';' { $$ =  SyntaxObj.Operator('=', 2,SyntaxObj.varAssignmentIdentifierNode($2), SyntaxObj.Operator(NEW,2,$1,$4) );} 		 
		stmt								{ $$ = $1; } //ordinary statements.
		;

class_name:
		IDENTIFIER							{ $$ = SyntaxObj.ClassIdNode($1); }
		;
		
init_list:									//A list of member initialisations, eg, 'Str 20, Wiz 14, Con 13' etc
		 init_pair							{ $$ = $1;}
		| init_list ',' init_pair			{ $$  = SyntaxObj.Operator(';', 2, $1, $3); }
		;
	
init_pair:									//initialise a data member in a NEW statement or array creation
		 data_member expr		%prec NON_SEQ				{ $$ = SyntaxObj.Operator(INIT_STACK, 2, $1, $2);}
		;
		
data_member:
		IDENTIFIER							{ $$ = InitMemberNode($1);  }
		;	

definition:								//A defintion defines a function or class.
		  function_def '{' stmt_list '}'	{ $$ = SyntaxObj.CreateFnDefNode( $1, $3); SymbTable.ClearCurrentFn(); }	//Process a function declaration.  
		| function_def '{'  '}'				{ $$ = SyntaxObj.CreateFnDefNode( $1, NULL); SymbTable.ClearCurrentFn();}	//Process an empty function declaration.  
		| CLASS class_name_dec HAS data_list ';'{ $$ = ClassOpNode( $2,NULL, $4,0);NoParents = 0; }   //Process a class declaration
		| CLASS class_name_dec class_parents HAS data_list ';'{ $$ = ClassOpNode( $2,$3, $5, NoParents); NoParents = 0; SyntaxObj.TotalMembs = 0;}   //Process a class declaration with parents
//		| error ';'							{ yyerrok;} //Report errors then skip to this symbol.
		;



		//Function definition rules:

function_def:								//A function defintion may or may not have a parameter list.
		  func_name '(' param_list ')'		{ $$ = $1; }    
		| func_name '(' ')'					{ $$ = $1;  }  
		;

func_name:									//Record the name of a function declaration. Forcing Bison to parse func_name now
		IDENTIFIER 							{ $$ = SyntaxObj.CreateGlobalFnNameNode($1); } //ensures parameter symbols aren't created before there's a 
		;															//function symbol to attach them to.

param_list:									//Go through the names in the parameter list
		  param_name						{ $$ = $1; }  //TO DO: may want to link these rather than discard
		| param_list ',' param_name			{ $$ = $3; }  
		;

param_name:									//Record parameter names so we can recognise them later.
		  IDENTIFIER						{ DeclParam($1,NULL); } 
		;		 


		//Class declaration rules:
class_name_dec:									//Record the name of the class
		 IDENTIFIER							{ $$ = DeclClassNode($1); } 
		;
		
class_parents:
	BASED_ON class_list						{ $$ = $2;}
		;

class_list:
		  IDENTIFIER						{ $$ = SyntaxObj.ClassIdNode($1); NoParents++; AddParentToCurrentClass($1);}  
		| class_list ',' IDENTIFIER			{ $$ = SyntaxObj.Operator(';', 2, $1, SyntaxObj.ClassIdNode($3)); NoParents++; AddParentToCurrentClass($3);}  
		;
							
			

data_list:									//Record the names of this class's data members.
		 IDENTIFIER							{ DeclDataMember($1);}  //No syntax node is created for this
		| data_list ',' IDENTIFIER			{ DeclDataMember($3); }
		| member_func						{ $$ = $1; }
		| data_list ',' member_func			{ $$  = SyntaxObj.Operator(';', 2, $1, $3); }
		;

member_func:
		  member_func_decl '{' stmt_list '}'	{ $$ = SyntaxObj.Operator(FUNC, 2, $1, $3); SymbTable.ClearCurrentFn();}	//Process a function declaration.  
		| member_func_decl '{'  '}'				{ $$ = SyntaxObj.Operator(FUNC, 2, $1, NULL); SymbTable.ClearCurrentFn();}	//Process a function declaration.  
												//TO DO: why do we have the above line - a function declaration without statements???
		;
member_func_decl:								//A function declaration may or may not have a parameter list.
		  member_func_name '(' param_list ')'		{ $$ = $1;  }    
		| member_func_name '(' ')'					{ $$ = $1;  }  
		;

member_func_name:									//Record the name of a function declaration. Forcing Bison to parse func_name now
		IDENTIFIER 							{ $$ = SyntaxObj.CreateMembFnNameNode($1); } //ensures parameter symbols aren't created before there's a 
		;															//function symbol to attach them to.



		//Statement rules:
stmt:										//The different kinds of statement we recognise
         ';'								{ $$ = SyntaxObj.Operator(';', 2, NULL, NULL); }  //An empty statement
        | '{' stmt_list '}'					{ $$ = $2; }	//A block of statements is also a kind of statement.
        | assignment			 ';'		{ $$ = $1; }	//Assigning a value to a variable
		| PRINT expr ';'					{ $$ = SyntaxObj.Operator(PRINT, 1, $2); }	//Printing an expression
		| PRINT complex_str  ';'			{ $$ = $2; } //Printing a 'complex string' containing inset code
        | WHILE '(' expr ')' stmt			{ $$ = SyntaxObj.Operator(WHILE, 2, $3, $5); }  //A WHILE loop
		| FOR '(' for_rules ')' stmt		{ $$ = SyntaxObj.Operator(FOR, 2, $3, $5); }  //A FOR loop
        | IF '(' expr ')' stmt %prec IFX	{ $$ = SyntaxObj.Operator(IF, 2, $3, $5); }	//An if statement
        | IF '(' expr ')' stmt ELSE stmt	{ $$ = SyntaxObj.Operator(IF, 3, $3, $5, $7); }  //An if statement with an else
		| function_call		';'				{ $$ = $1; }	//A function call that throws away the returned value.
		| FN_RETURN ';'						{ $$ = SyntaxObj.Operator(FN_RETURN,1,NULL); }	//A return-from-function statement with nothing to return (actually returns 1)
		| FN_RETURN expr ';'				{ $$ = SyntaxObj.Operator(FN_RETURN,1,$2); }	//A return-from-function statement that returns the result of an expression
		| error ';'							{ yyerrok;}		
        ;

stmt_list:						//A statement list consists of at least one statement.
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = SyntaxObj.Operator(';', 2, $1, $2); }	
        ;







		//Rules for assigning a value to a variable or object member
assignment:
		assignment_var_or_member '=' expr 		{ $$ = SyntaxObj.Operator('=', 2, $1, $3); }	//Assigning a value to a variable
		;

var_or_member:
		  IDENTIFIER							{ $$ = SyntaxObj.IdentifierExpression($1); }
		| IDENTIFIER	memberOf				{ $$ = SyntaxObj.Operator(ARROW, 2, SyntaxObj.IdentifierExpression($1), $2); } 
		//| IDENTIFIER dimension_list				{ $$ = SyntaxObj.Operator(ARRAY_ELEMENT, 2, SyntaxObj.IdentifierExpression($1),$2); } //an array or table element    
		;										
		
assignment_var_or_member:						//when a value is being assigned to a variable
		  IDENTIFIER							{ $$ = SyntaxObj.varAssignmentIdentifierNode($1); } 
		//| IDENTIFIER	memberOf				{ $$ = SyntaxObj.Operator(MEMB_ASSIGN, 2, SyntaxObj.IdentifierExpression($1), $2); RemoveFinalGetproperty();FinalMembNode = NULL; } 
		//| IDENTIFIER dimension_list			{ $$ = ArrayElementNode(SyntaxObj.IdentifierExpression($1),$2,NoArgs); NoArgs=0; } //an array or table element    
		|   deref ARROW IDENTIFIER				{ $$ = SyntaxObj.Operator(MEMB_ASSIGN, 2, $1,  SyntaxObj.MemberNode($3)); } 
	//	| deref dimension_list					{ $$ = SyntaxObj.Operator(ARRAY_ASSIGN,2, $2, $1);  } //an array or table element; }
		;	

	
memberOf: 
		ARROW IDENTIFIER						{ $$ = SyntaxObj.Operator(ARROW,1, SyntaxObj.MemberNode($2)); FinalMembNode = $$; }
		| memberOf ARROW IDENTIFIER				{ $$ = SyntaxObj.Operator(';',2, $1,SyntaxObj.Operator(ARROW,1, SyntaxObj.MemberNode($3))); FinalMembNode = $$->op[1];}
		;
		
		
deref:
		IDENTIFIER  							{  $$ = SyntaxObj.IdentifierExpression($1); }
		| deref ARROW IDENTIFIER 				{ $$ = SyntaxObj.Operator(';',2, $1,SyntaxObj.Operator(ARROW,1, SyntaxObj.MemberNode($3)));  }
	//	| deref dimension_list					{ $$ = SyntaxObj.Operator(';',2, SyntaxObj.Operator(ARRAY_ELEMENT,1,$2), $1);  }
		| deref dimension_list					{ $$ = SyntaxObj.Operator(';',2,$1,  SyntaxObj.Operator(ARRAY_ELEMENT,1,$2));  }

		//| dimension_list						{ $$ = $1;}
		//TO DO: got rid of above to avoid reduce/reduce conflict, not sure if I should
		;
		
		//Function call rules:

function_call:										//A function call may or may not include parameters.
		   call_func_name '('			{State.Push(); }
		   call_param_list ')'	{ $$ = SyntaxObj.Operator(FUNC_CALL,3,$1,$4,State.Seq_Count);State.Pop(); }
		// | call_func_name '('  ')'					{ $$ = SyntaxObj.Operator(FUNC_CALL,2,$1,0); }
		 ;

function_call_return:								//A function call where we don't throw away the returned value.
		   call_func_name '('			{State.Push(); }
		   
		   call_param_list ')'	{ $$ = SyntaxObj.Operator(FUNC_CALL_RET,3,$1,$4,State.Seq_Count); State.Pop(); }
		// | call_func_name '('  ')'					{ $$ = SyntaxObj.Operator(FUNC_CALL_RET,2,$1,NULL); }
		 ;

call_func_name:										//Name of a function being called. May be a member function.
		  IDENTIFIER 								{ $$ = SyntaxObj.CreateFnCallNode($1) ; } 
		| SUPERCLASS IDENTIFIER 					{ $$ = SupMembFnCallNode($2) ; }   
		//| IDENTIFIER ARROW IDENTIFIER				{ $$ = MemberNode(SyntaxObj.IdentifierExpression($1),$3); }
	//	| IDENTIFIER	memberOf					{ $$ = SyntaxObj.Operator('m', 2, SyntaxObj.IdentifierExpression($1), $2); RemoveFinalGetproperty();FinalMembNode = NULL; }  
		| deref ARROW IDENTIFIER						{ $$ = SyntaxObj.Operator('m', 2, $1, SyntaxObj.MemberNode($3) ); } 
		//above should be MembCallNode for clarity
		| IDENTIFIER SUPERCLASS IDENTIFIER			{ $$ = SyntaxObj.CreateSuperMembNode(SyntaxObj.IdentifierExpression($1),$3); }
		;
		
call_param_list:							//The parameter list of a function call.
	//	  expr								{ $$ = $1; State.Seq_Count++;}  //collect arguments, to push on stack
	//	| call_param_list ',' expr 		{ $$ = SyntaxObj.Operator(';', 2, $1, $3); State.Seq_Count++;;} 
		expr_sequence					{ $$ = $1;}
		|								{ $$ = NULL; }
		;

										
		//Rules for 'complex strings' (eg, "Text [inset expression] more text"):

complex_str:					//A complex string is a string with inset expressions, chopped up by the lexer.
								//We turn it into a series of print statements 	
		    ui_list STRING  { $$ = SyntaxObj.Operator(';', 2,$1,  SyntaxObj.Operator(PRINT,1,SyntaxObj.CreateStrNode($2)) ); }	   
		  ;

ui_list:						//A ui list consists of one or more ui groupings.
			  ui				{ $$ = $1; }
			| ui_list ui		{ $$ = SyntaxObj.Operator(';',2, $1, $2); }
			;

ui:								//A ui grouping is a string followed by a square-bracketed expression.
			  STRING '[' expr ']'	{ $$ = SyntaxObj.Operator(PRINT, 2 ,  SyntaxObj.CreateStrNode($1), $3); }
			;


for_rules:
			assignment ';' expr ';' assignment 	{ $$ = SyntaxObj.Operator(';',3,$1,$3,$5); }
		;
		
dimension_list:	
		'[' expr ']'				{ $$ = $2; }
		| '[' expr ',' expr ']' 	{ $$ = SyntaxObj.Operator(';',2, $2, $4); }
		;											//TO DO: throwError if sequence above 2
		
array_list:
		'{'							{State.Push(); }
		expr_sequence '}'			{$$ = $3; }
		;
			
table_list:
		 array_list								{ $$ = $1; TableRows++;}
		| table_list ','  array_list 			{ $$ = SyntaxObj.Operator(';',2, $1, $3); TableRows++;}
		;

		//Rules for expressions: 

		//idea! Use 2 words to describe actions, eg, IntegerConstant: it's an INTEGER token, and here we're treating it as a constant
expr:
          INTEGER								{ $$ = SyntaxObj.IntegerConstant($1); }  
		| STRING								{ $$ = SyntaxObj.CreateStrNode($1);}	
		| FLOAT									{ $$ = SyntaxObj.FloatConstant($1); }	
        | IDENTIFIER							{ $$ = SyntaxObj.IdentifierExpression($1); }
		| function_call_return					{ $$ = $1; }	//A function used as an expression - so we keep the return value.
		| NEW IDENTIFIER						{ $$ = SyntaxObj.Operator(NEW,1,SyntaxObj.ClassIdNode($2));}	//create a new instance of a class;
		| NEW class_name  '(' init_list ')'		{ $$ =  SyntaxObj.Operator(NEW,2,$2,$4);} 
//		| IDENTIFIER ARROW IDENTIFIER	{ $$ = MemberNode(SyntaxObj.IdentifierExpression($1),$3); }	//put member def here, create a getmember func and node  
	//	| IDENTIFIER	memberOf				{ $$ = SyntaxObj.Operator(';', 2, SyntaxObj.IdentifierExpression($1), $2); }  
		| deref ARROW IDENTIFIER				{ $$ = SyntaxObj.Operator(ARROW, 2, $1,  SyntaxObj.MemberNode($3)); }  
        | '-' expr %prec UMINUS					{ $$ = SyntaxObj.Operator(UMINUS, 1, $2); }
        | expr '+' expr							{ $$ = SyntaxObj.Operator('+', 2, $1, $3); }
        | expr '-' expr							{ $$ = SyntaxObj.Operator('-', 2, $1, $3); }
        | expr '*' expr							{ $$ = SyntaxObj.Operator('*', 2, $1, $3); }
        | expr '/' expr							{ $$ = SyntaxObj.Operator('/', 2, $1, $3); }
        | expr '%' expr							{ $$ = SyntaxObj.Operator('%', 2, $1, $3); }
        | expr '<' expr							{ $$ = SyntaxObj.Operator('<', 2, $1, $3); }
        | expr '>' expr							{ $$ = SyntaxObj.Operator('>', 2, $1, $3); }	        
		| expr AND expr							{ $$ = SyntaxObj.Operator(AND, 2, $1, $3); }
        | expr OR expr							{ $$ = SyntaxObj.Operator(OR, 2, $1, $3); }
        | expr GE expr							{ $$ = SyntaxObj.Operator(GE, 2, $1, $3); }
        | expr LE expr							{ $$ = SyntaxObj.Operator(LE, 2, $1, $3); }
        | expr NE expr							{ $$ = SyntaxObj.Operator(NE, 2, $1, $3); }
        | expr EQ expr							{ $$ = SyntaxObj.Operator(EQ, 2, $1, $3); }

        | '(' expr ')'						{ $$ = $2; }
		| DATA_TYPE var_or_member				{ $$ = SyntaxObj.Operator(DATA_TYPE,1,$2); }
		| STR_INPUT								{ $$ = SyntaxObj.Operator(STR_INPUT,0); }
	//	| ARRAY  '[' expr ']'  					{ $$ = DeclArrayNode($3 ); }
	//	| TABLE '[' expr ',' expr ']'			{ $$ = DeclTableNode($3,$5); }
	//	| '{' array_list '}' 					{ $$ = NewListArrayNode($2,NoElems); NoElems = 0;}
		|  array_list							{ $$ = NewListArrayNode($1,State.Seq_Count);State.Pop(); }
		| '[' table_list ']'					{ $$ = NewListTableNode($2,State.Seq_Count,TableRows);  TableRows=0;}
	//	| IDENTIFIER dimension_list				{ $$ = ArrayElementNode(SyntaxObj.IdentifierExpression($1),$2); } //an array or table element  
		| deref dimension_list				 { $$ = SyntaxObj.Operator(ARRAY_ELEMENT,2,$1,$2); } //an array or table element  
		| RAND									{ $$ = RandNode($1, NULL,NULL); }
		|  expr RAND2 expr 						{ $$ = RandNode(NULL,$1,$3); }
  
        ;

expr_sequence:									//TO DO: make this empty if needed. What happens if we create an empty array?1`	1`	1`	1`	1`	1`	1`	1`	1`	1`	\A
	  expr 										{$$ = $1; State.Seq_Count++; }
	 | expr_sequence ',' expr					{$$ = SyntaxObj.Operator(';',2, $1, $3); State.Seq_Count++; }
	;	  

%%









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



