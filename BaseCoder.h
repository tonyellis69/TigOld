#pragma once

//#include <iostream>
#include <fstream>
#include "SyntaxNode.h"
//#include "Tig.hpp"
#include "Tig.h"
#include <string>

class CBaseCoder
{
public:
	CBaseCoder();
	//virtual ~CBaseCoder();
	void WriteSingleInstruct(int Opcode);
	void WriteByte( char byte);
	void WriteInstruct1Op(int OpCode, int Op1);
	void WriteInstruct1Op(int OpCode, float Op1);
	void WriteInstruct1OpByte(int OpCode, char Op1);
	void WriteString(char* Str);

	void WritePrintStr(CSyntaxNode* Node);
	void writeBranch(unsigned int opCode, int branch);


	
	std::ofstream CodeFile; ///<The output stream we write to.
	char* StrData; ///<Pointer to the string table
	bool Verbose; ///<True if we want line by line output of what's being compiled.


//	static const char * const OpNames[];
	std::string OperandNames[MAX_OPCODES];
};
