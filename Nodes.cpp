// Nodes.cpp: implementation of the CNodes class.
//
//////////////////////////////////////////////////////////////////////

#include "Nodes.h"

#include "StringTable.h"
#include "Tig.h"
#include "Tig.hpp"
#include "Coder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CStringTable StrTable;
extern CSymbolTable SymbTable;
extern CCoder CodeObj;	

void Error (const char *format, ...); 
extern int lineno; //TO DO - check if we still use this

CNodes::CNodes(void)
{
	TotalMembs = 0;
}

CNodes::~CNodes(void)
{
}

/** Create a node representing the given operator. Operators include +,-,=, but also if statements, print statements, etc.
Most operators will come with operands - other nodes representing the tokens that they act upon. These are attached as
the children of the operator node, forming a little tree. */
CSyntaxNode* CNodes::Operator(int Oper, int Nops, ...) {
	va_list ap;
	int i;
	CSyntaxNode* Node = new CSyntaxNode(typeOpr);
	va_start(ap, Nops); 
	Node->oper = Oper;
	Node->nops = Nops;

	for (i = 0; i < Nops; i++) { //if this operation has operands... 
		if (((Oper == FUNC_CALL) || (Oper == FUNC_CALL_RET))  && (i == 2 ) ) { //3rd op will be the number of args in the call
			Node->value = va_arg(ap, int); //store number of args in the node
			Node->nops = 2;				//discard third operand
		}
		else
			Node->op[i] = va_arg(ap, CSyntaxNode*);  //...make operands the children of this operator node.
	}
	va_end(ap);

	return Node;
}


/** Create a syntax node for a integer constant, eg 42. The numeric value of the constant is stored in the node. */
CSyntaxNode* CNodes::IntegerConstant(int Value) {
    CSyntaxNode *Node = new CSyntaxNode(typeIntCon);
    Node->value = Value; //TO DO: value and fvalue can be the same variable.
    return Node;
}

/** Create a syntax node for a float constant, eg 4.2. The numeric value of the constant is stored in the node. */
CSyntaxNode*  CNodes::FloatConstant(float Value) {
    CSyntaxNode *Node = new CSyntaxNode(typeFloat);
    Node->fvalue  =  Value; //
	Node->value  =  (float) Value; //TO DO: why? get rid of this
    return Node;
}

/** Create a string constant node representing the given string. The string is stored in the string table, 
the node records the address of the string in the table.*/
CSyntaxNode* CNodes::CreateStrNode(char* Str)  {
	CSyntaxNode *Node = new CSyntaxNode(typeStrCon);
	int	Pos = StrTable.Add(Str); 
	Node->value = Pos; //Record the string's position in the string table.
	return Node;
}

/** Called when we encounter an identifier used as an expression, such as a reference to a variable, member or parameter. Eg '=x'.
If this variable doesn't already exist on the symbol table it hasn't been declared, so throw an error. */
CSyntaxNode* CNodes::IdentifierExpression(char* Name) {
    CSyntaxNode *Node = IdentifyVarName(Name);
	if (Node == NULL) 
		Error("Unrecognised variable: '%s'.",Name);
	return Node; //Should return a node of typeId.
}

/** Called when we've caught the user assigning a value to a variable. 
Returns a node for the variable, and if the variable is new it is added to the symbol table.  */
CSyntaxNode* CNodes::varAssignmentIdentifierNode(char* Name) {
   	//Do all the variable checks
    CSyntaxNode *Node = IdentifyVarName(Name);

	SymDesc* Var;
	if (Node == NULL) { //it's a new variable, so add it to the symbol table
		Node = new CSyntaxNode(typeId); //first create a syntax node for it.

		if (SymbTable.CurrentFn == NULL) {//we're not inside a function, so this is an attempt to declare a global variable
			Var = new SymDesc (Name, GLOBAL_VAR,  lineno); 
			bool Result = SymbTable.Add ( GLOBAL_SCOPE, Var); //add it to the list of global vars
		}
		else { //we're in a function, 
			Var = new SymDesc (Name, LOCAL,  lineno); //so create a new local variable symbol
			bool Result = SymbTable.Add ( CURRENT_FN, Var); //add it to the current function's list of vars
			if (!Result) 
				Error("Too many local variables! Cannot exceed %d.",  TOTAL_LOCALS);
			//TO DO: ensure new memory model doesn't limit variables
		}
		Node->symbol = Var; //associate the syntax node with the symbol.
	}
	/*else {
		//if it's not new, is the user attempting to assign a value to a global name ?
		if ((Node->NodeType == typeId) && (Node->symbol->Type == GLOBAL_VAR))
			Error("%s is already a globally used name.", Name);
	}*/

	return Node;
}

/** Identify the named variable if already declared and return an appropriate node. */
CSyntaxNode* CNodes::IdentifyVarName(char* Name) {
    CSyntaxNode *Node = new CSyntaxNode(typeId);

	//Is this variable a data member of the current class?
	SymDesc* Var = SymbTable.Find(CURRENT_CLASS,Name); 
	if (Var != NULL) {
		Node->symbol = 0;
		Node->value = Var->MemberNo;
		Node->NodeType = typeMemb;
		return Node;
	}  

	//Is this variable a data member of a parent class?
	Var = SymbTable.Find(CURRENT_CLASS_PARENT,Name); 
	if (Var != NULL) {
		Node->symbol = 0;
		Node->value = Var->MemberNo;
		Node->NodeType = typeMemb;
		return Node;
	} 


	Var = SymbTable.Find(CURRENT_FN,Name); //Is this an already declared parameter or local variable of the current function?
	if (Var != NULL) {
		Node->symbol = Var; //TO DO - try get rid of these and just use Node->value as below
		Node->value = Var->Address;  //The variable's address IS the syntactical value of the node!

		return Node;
	}  

	//TO DO: NodeType typeId is ambiguous - needs to be typeLocalVar or typeGlobalVar
		
	Var = SymbTable.Find(GLOBAL_SCOPE,Name); 	//Is Name an existing global symbol?
	if ((Var != NULL) && (Var->Type == GLOBAL_VAR)) {  //not a variable?
		Node->symbol = Var;
		return Node;
	}

	//Got here? It's an unrecognised variable name.
	delete Node;
	return NULL;
}


//TO DO: Currently, nowhere calls this
/** Create a syntax node for a reference to an object member. */
/*
CSyntaxNode *MemberNode(CSyntaxNode* Obj, char* MemberName) {
	CSyntaxNode *Node; 

	SymDesc* Member = SymbTable.Find(MEMBERS,MemberName); //Is this a previously declared member name?
	if ( Member == NULL) {								  //TO DO: will have to scrap this check  when we start using libraries
		Error("Unrecognised member name: %s",MemberName);
		return Node;
	}

	if (Member->MemberNo < FREE_MEMBER_NOS)
		Node = new CSyntaxNode(typeArrayMemb);
	else
		Node = new CSyntaxNode(typeMemb);
	Node->symbol = Obj->symbol; 
	Node->value = Member->MemberNo;

	return Node;
} */

CSyntaxNode* CNodes::MemberNode(char* MemberName) {
	CSyntaxNode *Node; 

	SymDesc* Member = SymbTable.Find(MEMBERS,MemberName); //Is this a previously declared member name?
	if ( Member == NULL) {								  //TO DO: will have to scrap this check  when we start using libraries
		Error("Unrecognised member name: %s",MemberName);
		return NULL;
	}

	if (Member->MemberNo < FREE_MEMBER_NOS)
		Node = new CSyntaxNode(typeArrayMemb);
	else
		Node = new CSyntaxNode(typeIntCon);
    Node->value = Member->MemberNo;;
    return Node;
}

/** Create a syntax node for a reference to a superclassed object member function. */
CSyntaxNode* CNodes::CreateSuperMembNode(CSyntaxNode* Obj, char* MemberName) {
	CSyntaxNode *Node = new CSyntaxNode(typeSuperMemb);

	SymDesc* Member = SymbTable.Find(MEMBERS,MemberName); //Is this a previously declared member name?
	if ( Member == NULL) {
		Error("Unrecognised member name: %s",MemberName);
		return Node;
	}
	Node->symbol = Obj->symbol; 
	Node->value = Member->MemberNo;

	return Node;
}


/** Create a syntax node for the named class. If this identifier doesn't already exist on the symbol table it hasn't been 
declared, so throw an error. */
CSyntaxNode* CNodes::ClassIdNode(char* Name) {
	CSyntaxNode *Node = new CSyntaxNode(typeClassName); //TO DO: probably doesn't need a special type
	//TO DO: class node currently isn't encoded, Coder action for NEW handles it all - ClassNode should do its own work

	SymDesc* Class	 = SymbTable.Find (GLOBAL_SCOPE,Name);	 	//is this an existing class?
	if (( Class != NULL) && (Class->Type == CLASS_SYM)) {
		Node->symbol = Class; //pass on the type of this class
		TotalMembs += Class->Value; //keep running total, for classes with parents. Used in class declarations.
		//set current object tracker to this class. Used for error-checking member names when initialising
		SymbTable.CurrentObj = Class;
		return Node;
	}
	else
		Error("Unrecognised class: '%s'.",Name);

	return Node;

}

/** Create a symbol table entry for the named global variable. We don't create a node because no code is required. 
 During the final stages of compilation, the memory address of this variable will be initialised with the given value. 
void DeclGlobalVar(char* Name, int val) {
	 if (SymbTable.Find (GLOBAL_SCOPE,Name) == NULL)  {  	//has this name been used yet?
		SymDesc* Var = new SymDesc (Name, GLOBAL_VAR,  lineno );  //Create an entry for the symbol table 
		Var->Value = val; //initialise it
		bool Result = SymbTable.Add ( GLOBAL_SCOPE, Var); //add it to the symbol table
		if (!Result) {
			Error("Too many global variables! Cannot exceed %d.",  TOTAL_LOCALS);
		}
	}
	else
		Error("Global identifier '%s' is already in use.",Name); 
}
*/


/**	Create a function name node for the named global function; add it to the symbol table. But return an error
 if this name has already been used in a global declaration.*/
CSyntaxNode* CNodes::CreateGlobalFnNameNode(char* Name) {
    CSyntaxNode *Node = new CSyntaxNode(typeId);

	SymDesc* Symb = SymbTable.Find (GLOBAL_SCOPE, Name); //Does a global object of this name already exist?

	if ( Symb == NULL)   { // No?
		Node->symbol = new SymDesc (Name, FN,  lineno); //create an entry for the symbol table
		SymbTable.Add ( GLOBAL_SCOPE, Node->symbol);
	}
	else  //yes
	{
		if (Symb->Type == FN)
			Error("A global function called '%s' has already been declared.",Name); 
		if (Symb->Type == GLOBAL_VAR)
			Error("A global object called '%s' has already been declared.",Name);
		Node->NodeType = typeError;
		return Node;
	}

    return Node;
}


/**	Create a member function declaration node for the named member function; add the function to the symbol table. 
 But return an error if this name has already been used in this class.*/
CSyntaxNode* CNodes::CreateMembFnNameNode(char* Name) {
    CSyntaxNode *Node = new CSyntaxNode(typeId);

	if (SymbTable.Find (CURRENT_CLASS,Name) == NULL) { //has this member name been used by this class?
		Node->symbol = new SymDesc (Name, MEMBER_FN,  lineno);
		SymbTable.Add(CURRENT_CLASS, Node->symbol);
	}
	else
		Error("'%s' already declared as a member name for this class.",Name);

    return Node;
}


/** Create a function node for a call to the named function. Assuming a function with this name exists in the symbol table. */
CSyntaxNode* CNodes::CreateFnCallNode(char* Name) {
    CSyntaxNode *Node = new CSyntaxNode(typeId);

	//Search for it as a member func of the current class (including parents) first.
	SymDesc* Fn = SymbTable.Find (CURRENT_CLASS, Name);
	if (Fn != NULL) {
		Node->symbol = 0;
		Node->value = Fn->MemberNo;
		Node->NodeType = typeMemb;
		return Node;
	}	


	//No? then see if this is a global function
	Fn = SymbTable.Find (GLOBAL_SCOPE, Name);
	if ( Fn == NULL)   { // doesn't exist yet; 
		Error("No such function as '%s'.",Name);
		return Node;
	}
	else if (Fn->Type != FN) {
		switch (Fn->Type)
		{ 
			case GLOBAL_VAR: 
				DiagSymbKind = "a global variable"; break;
			case LOCAL: 
				DiagSymbKind = "a local variable"; break;
			case PAR: 
				DiagSymbKind = "a parameter"; break;
			case CLASS_SYM: 
				DiagSymbKind = "a class definition"; break;
			case DATA_MEMBER: 
				DiagSymbKind = "a data member"; break;
			case MEMBER_FN: 
				DiagSymbKind = "a member function"; break;
		}
		Error("The name '%s' belongs to %s.",Name,DiagSymbKind);

	}
	Node->symbol = Fn;
    return Node;
}

/** Create a (global) function defintion node. */
CSyntaxNode* CNodes::CreateFnDefNode(CSyntaxNode* Name, CSyntaxNode* Code) {
	CSyntaxNode* Node = new CSyntaxNode(typeOpr);

	if (Name->NodeType == typeError) {
		Error("This name has already been used globally.");
		return Node;
	}

	Node->oper = FUNC;
    Node->nops = 2;
	Node->op[0] = Name;
	Node->op[1] = Code;

	//Is this function 'main'? 
	if (strcmp(Name->symbol->Name,"main") == 0) {
	//If so, we don't add it to the standard syntax tree, but the global tree, to ensure it gets encoded right after any global statements
		CodeObj.AddMain(Node); 
		return NULL;
	}
	return Node;
}

