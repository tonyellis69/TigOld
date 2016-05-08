// Nodes.h interface for the CNodes class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(CNODES_H)
#define CNODES_H

#include <stdarg.h> 
#include "SyntaxNode.h"

class CNodes  
{
public:
	CNodes();
	virtual ~CNodes();
	CSyntaxNode* Operator(int Oper, int Nops, ...);
	CSyntaxNode* IntegerConstant(int Value);
	CSyntaxNode* FloatConstant(float Value);
	CSyntaxNode* CreateStrNode(char* Str);
	CSyntaxNode* IdentifierExpression(char* Name);
	CSyntaxNode* varAssignmentIdentifierNode(char* Name);
	CSyntaxNode* IdentifyVarName(char* Name);
	CSyntaxNode* MemberNode(char* MemberName);
	CSyntaxNode* CreateSuperMembNode(CSyntaxNode* Obj, char* MemberName);
	CSyntaxNode* ClassIdNode(char* Name);
	CSyntaxNode* CreateGlobalFnNameNode(char* Name);
	CSyntaxNode* CreateMembFnNameNode(char* Name);
	CSyntaxNode* CreateFnCallNode(char* Name);
	CSyntaxNode* CreateFnDefNode(CSyntaxNode* Name, CSyntaxNode* Code);

	int TotalMembs;
	char* DiagSymbKind; //Used in diagnostic error messages.
};



#endif
