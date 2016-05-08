// Coder.h: interface for the CCoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODER_H__C5A85C30_1BB0_4D1B_B622_E8A47903804D__INCLUDED_)
#define AFX_CODER_H__C5A85C30_1BB0_4D1B_B622_E8A47903804D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <fstream>
#include "SyntaxNode.h"
#include "BaseCoder.h"


/** Walks a given syntax tree, writing it to a file as bytecode. The string table, variable table etc are appended
to the file, and the addresses of these various sections written to a header. */
class CCoder :  public CBaseCoder
{
public:
	CCoder();
	int OpenFile(char* Filename); 
	int Encode(CSyntaxNode* p);
	int CloseFile();
	int SetSymbolTable(CSymbolTable* st);
	int GetStrTablePtr(char* Str);
	void AppendGlobal(CSyntaxNode* Node);
	int EncodeGlobal();
	int AddMain(CSyntaxNode* MainFn);
	int WriteDiagram(CSyntaxNode* Node);
	bool Diagram; ///<True if we want to write a text diagram of the syntax tree rather than encode it.
	virtual ~CCoder();

private:
	int WriteInstruct(unsigned int Opcode, unsigned int Operand);
	int WriteInstructF(unsigned int Opcode, float Operand);
	int WriteInstructByte(unsigned int Opcode, unsigned  char Operand);
	int WriteBranch(unsigned int Opcode, int Branch);
	int InsertBranch(unsigned int Address, int Branch); 
	int Write2OpInstruct(unsigned int Opcode, unsigned int Opcode1,unsigned int Opcode2);
	int WriteDWord(unsigned int DWord);
	int WriteDWordF(float DWord);
	char* OpNamer(int Op);
	int Depth; ///< Used by WriteDiagram to record how deep down the layers of the syntax tree we are.

	
	int lbl;	//?????????????	   
	int CodeEnd; //?????????????
	SymDesc* CurrentFunc; ///<The symbol table entry for the function we're in. Useful for number of local vars, etc
	SymDesc* CurrentClass; ///<The symbol table entry for the class we're in. 
	bool UserReturn;  ///<True if we reach a return statement. Used to see if we need to insert one. 
	CSymbolTable* SymTable;
	CSyntaxNode* GlobalTree;
	CSyntaxNode* CurrentGlobalNode;
	int EntryPt; ///<Address at which execution should start. Eg, the address of the 'main' fucntion
};



static const char* const OpNames[] = { "INTEGER", "IDENTIFIER", "STRING",
  "FLOAT", "RAND", "WHILE", "FOR", "IF", "PRINT", "PRINT_VALERIC",
  "FUNC_CALL", "FUNC_CALL_RET", "FN_RETURN", "LOCAL_VAR", "CLASS", "HAS",
  "WITH", "ARROW", "BASED_ON", "ARRAY", "TABLE", "SUPERCLASS", "DATA_TYPE",
  "STR_INPUT", "RESERVED_ADD", "RESERVED_SIZE", "MEMB_ASSIGN", "PLIB",
  "DEREF_ASSIGN", "ARRAY_ASSIGN", "ARRAY_ELEMENT", "ARRAY_LIST",
  "TABLE_LIST", "IFX", "NEW", "FUNC", "PRINT_COMPLEX", "ELSE", "'>'",
  "'<'", "RAND2", "AND", "OR", "NE", "EQ", "LE", "GE", "'+'", "'-'", "'*'",
  "'/'", "'%'", "','", "UMINUS", "NON_SEQ", "';'", "'('", "')'", "'{'",
  "'}'", "'='", "'['", "']'", "$accept", "code", "global_statement",
  "class_name", "init_list", "init_pair", "data_member", "declaration",
  "function_decl", "func_name", "param_list", "param_name",
  "class_name_dec", "class_parents", "class_list", "data_list",
  "member_func", "member_func_decl", "member_func_name", "stmt",
  "stmt_list", "assignment", "var_or_member", "assignment_var_or_member",
  "memberOf", "deref", "function_call", "$@1", "function_call_return",
  "$@2", "call_func_name", "call_param_list", "complex_str", "ui_list",
  "ui", "for_rules", "dimension_list", "array_list", "$@3", "table_list",
  "expr", "expr_sequence"
};




#endif // !defined(AFX_CODER_H__C5A85C30_1BB0_4D1B_B622_E8A47903804D__INCLUDED_)
