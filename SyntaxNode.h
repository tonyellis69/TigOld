#if !defined(NODETYPE_H)
#define NODETYPE_H


#include "symtab.h"


/** The different types of syntax node available: */
typedef enum { typeIntCon, typeId, typeFloat, typeOpr, typeStrCon, typeMemb, typeClassName, typeSuperMemb, typeElem, typeArrayMemb, typeError } nodeEnum;


/** This class defines the nodes that make up a syntax tree. 'x = 5' would create 3 nodes, one for '=', one for 'x' and one
for '5'. Nodes can represent identifiers, operators, numeric constants etc. */ 
class CSyntaxNode {
public:
	CSyntaxNode (nodeEnum Type) { symbol = NULL;  NodeType = Type; value = 0; oper =';'; nops=0; op[0] = NULL; op[1] = NULL;};
   ~CSyntaxNode () { };

    nodeEnum NodeType;          ///<The type of this node - numeric constant, operator, etc.  
	int value;					///<If this node represents a value, eg '5', store it here.
	int value2;					///<Handy second value store
	float fvalue;					///<If this node represents a floating point value, store it here.
	SymDesc *symbol;			///<The symbol in the symbol table represented by this node, if any. 
	int oper;                   ///<If this symbol represents an operator, record it here.
    int nops;                   ///<The number of operands of this symbol, if any. Eg, '=' would have two operands, x and 5.
    CSyntaxNode *op[12];		///<Pointers to nodes that are the operands of this node, if any.
};






#endif 


