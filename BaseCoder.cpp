#include "BaseCoder.h"
using namespace std;

CBaseCoder::CBaseCoder() {
	OperandNames[PUSH] = "push";
	OperandNames[POP] = "pop";
	OperandNames[PRINT_STR] = "printStr";
	OperandNames[PRINT_VAL] = "printVal";
	OperandNames[PUSHC] = "pushC";
	OperandNames[EXIT] = "exit";
	OperandNames[LINK] = "link";
	OperandNames[STR] = "str";
	OperandNames[PUSHF] = "pushF";
	OperandNames[ADD] = "add";
	OperandNames[SUB] = "sub";
	OperandNames[MUL] = "mul";
	OperandNames[DIV] = "div";
	OperandNames[MOD] = "mod";
	OperandNames[COMPGT] = "compGT";
	OperandNames[COMPGE] = "compGE";
	OperandNames[COMPLT] = "compLT";
	OperandNames[COMPGE] = "compGE";
	OperandNames[COMPNE] = "compNE";
	OperandNames[COMPEQ] = "compEQ";
	OperandNames[COMPAND] = "compAND";
	OperandNames[COMPAND] = "compOR";
	OperandNames[POPG] = "popG";
	OperandNames[JZ] = "jz";
	OperandNames[JMP] = "jmp";

}

/** Write an instruction without an opcode. */
void CBaseCoder::WriteSingleInstruct(int Opcode) {
	CodeFile.write((char*)&Opcode,OPCODE_SIZE); 	//write opcode;
	if (Verbose) {
		printf("\n%06x ",(unsigned int)CodeFile.tellp()-1);
		cout << "\t" << OperandNames[Opcode] << " ";
	}
}

/** Write a single byte. */
void CBaseCoder::WriteByte(char byte) {
	CodeFile.write((char*)&byte,1);
	if (Verbose)
		//cout << "\t" << OperandNames[Opcode] <<" ";
		printf("%d",byte);
}

void CBaseCoder::WriteInstruct1Op(int OpCode, int Op1) {
	CodeFile.write((char*)&OpCode,OPCODE_SIZE);
	CodeFile.write((char*)&Op1,OPERAND_SIZE); 	//write operand
	if (Verbose) {
		printf("\n%06x ",(unsigned int)CodeFile.tellp()-5);
		cout << "\t" << OperandNames[OpCode] << " ";
		printf("%d", Op1);
	}
}

void CBaseCoder::WriteInstruct1Op(int OpCode, float Op1) {
	CodeFile.write((char*)&OpCode,OPCODE_SIZE);
	CodeFile.write((char*)&Op1,OPERAND_SIZE); 	//write operand
	if (Verbose) {
		printf("\n%06x ",(unsigned int)CodeFile.tellp()-5);
		cout << "\t" << OperandNames[OpCode] << " ";
		printf("%f", Op1);
	}
}

void CBaseCoder::WriteInstruct1OpByte(int OpCode, char Op1) {
	CodeFile.write((char*)&OpCode,OPCODE_SIZE);
	CodeFile.write((char*)&Op1,1); 	//write operand
	if (Verbose) {
		printf("\n%06x ",(unsigned int)CodeFile.tellp()-2);
		cout << "\t" << OperandNames[OpCode] << " ";
		printf("%d", Op1);
	}
}

/** Write a string. */
void CBaseCoder::WriteString(char* Str){
	CodeFile << Str << '\0';

	if (Verbose) { //show the string we're writing, or first 30 chars of it
		cout << "\"";
		char buf[31];
		if (strlen(Str) < 30)
			cout << Str;
		else {
			strncpy(buf,Str,30);
			buf[30] = '\0';
			cout << buf << "...";
		}
		printf("\"");
	}
}

/** Handle a print-literal-string node. */
void CBaseCoder::WritePrintStr(CSyntaxNode* Node) {
	WriteSingleInstruct(PRINT_STR); 
	WriteString(StrData+Node->op[0]->value); //write the string itself to the bytecode file.	
}

/** Write a branch instruction and the branch offset. A negative number for a branch back, positive for foward. The 
subraction/addition takes place from the address after this instruction and offset. */
void CBaseCoder::writeBranch(unsigned int opCode, int branch) {
	CodeFile.write((char*)&opCode,OPCODE_SIZE); //write operator
	CodeFile.write((char*)&branch,BRANCH_SIZE); 	//write offset - but it's just a dummy for now.
	if (Verbose) {
		printf("\n%06x ",(unsigned int)CodeFile.tellp()-3);
		cout << "\t" << OperandNames[opCode] << " ";
		printf(" L%03d", branch);
	}
}





//const char * const CBaseCoder::OpNames[] = {"mon", "tue", "wed", "thur",
                    //                   "fri", "sat", "sun"};
/*
const char * const CBaseCoder::OperandNames[] = { "INTEGER", "IDENTIFIER", "STRING",
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
  "function_def", "func_name", "param_list", "param_name",
  "class_name_dec", "class_parents", "class_list", "data_list",
  "member_func", "member_func_decl", "member_func_name", "stmt",
  "stmt_list", "assignment", "var_or_member", "assignment_var_or_member",
  "memberOf", "deref", "function_call", "$@1", "function_call_return",
  "$@2", "call_func_name", "call_param_list", "complex_str", "ui_list",
  "ui", "for_rules", "dimension_list", "array_list", "$@3", "table_list",
  "expr", "expr_sequence"
}; 
*/
 //const char CBaseCoder::OpNames[PRINT_STR] = "PrintStr";