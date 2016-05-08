#pragma once

#define ADDR_SIZE 4  //memory addresses use 4 bytes
#define OPCODE_SIZE	1  //opcodes use 1 byte
#define BRANCH_SIZE 2 //branch offsets use 2 bytes
#define OPERAND_SIZE 4  //operands use 4 bytes
#define HEADER_SIZE  4// was 8  //how many bytes to reserve at start of file of bytecode
#define DWORD_SIZE 4
//#define LOCAL_VAR_SPACE 128  //size of VM memory reserved for local variables/parameters //SCRAP!!
#define CLASS_HEADER_SIZE 3

#define TOTAL_LOCALS 31
#define TOTAL_PARAMS 31

#define PARAMTER_BIT 128

#define FRAME_HEADER_OFFSET 4
#define THIS_OFFSET 1

#define MAX_STRING 512

#define TIG_WORD  4		//size of a standard word of data in TIG

#define TYPE_SIZE 2		//number of bits needed to hold a variable's type

#define CODE_START HEADER_SIZE //Memory for storing functions etc starts here

#define DEFAULT_TOTAL_GLOBALS 32
	
#define	NOP		0
#define	PUSH	1
#define	POP		2  
#define	JZ		3
#define	JMP		4
#define	NEG		5
#define	ADD		6
#define	SUB		7
#define	MUL		8
#define	DIV		9
#define	COMPLT	10
#define	COMPGT	11
#define	COMPGE	12
#define	COMPLE	13
#define	COMPNE	14
#define	COMPEQ	15
#define PRINT_STR	16
#define PRINT_VAL	17
#define PUSHC	18
#define CALL	21
#define RETURN_TRUE 22
#define RETURN	23
#define DISCARD 24
#define EXIT	25
#define NEW_OBJ 26
#define PUT_PROP	27
#define PUSH_PROP	28
#define CALL_MEMB	29
#define CALL_PARENT_MEMB  30
#define	MOD		31
#define	COMPAND	32
#define	COMPOR	33
#define LINK	34
#define TYPE	35
#define STR		36
//#define CONCAT	37
#define INPUT	38
#define PUSHF	39
#define PUSH_ELEM 40
#define PUT_ELEM 41
#define CALL_ARRAY_MEMB 42
#define RND 43
#define PUSHG 44
#define POPG 45
#define INIT_STACK 49

#define MAX_OPCODES 60

//TO DO - this is a psuodo operator. Replace with LINK, or rename LINK to FUNC
//#define FUNC 77

//built-in classes
#define ARRAY_CLASS	0 
#define TABLE_CLASS	1 
#define PREDEF_ARRAY 2
#define PREDEF_TABLE 3



//built-in member names
#define MEMB_SIZE 1
#define MEMB_ADD 2
#define MEMB_DELETE 3
#define MEMB_INSERT 4
#define MEMB_SWAP 5
#define MEMB_ROWS 6
#define MEMB_COLS 7
#define MEMB_ADD_ROW 8
#define MEMB_DEL_ROW 9
#define MEMB_INSERT_ROW 10
#define MEMB_ADD_COL 11
#define MEM_DEL_COL 12
#define MEM_INSERT_COL 13
#define MEMB_SWAP_ROW 14
#define MEMB_SWAP_COL 15


#define FREE_MEMBER_NOS 20




/*
Object data structure:

Object class		4 bytes
Size of type data	1 byte //ACTUALLY THIS NUMBER OF DATA ITEMS WHEN OBJ CREATED - CHECK WE ARE CONSISTENT IN THIS
Member data			n DWords (where n is the number of members)
Type data			s bytes (where s is Size of type data)
*/



/* 
Virtual Machine memory map

Unused DWord				0000 - 0003
Local variables				0004 - 0252
Global variables			0256 - 0511
Code						0512 - 4999  
Objects						5000 - 9999


Class header structure

byte	Number of parents
byte	Number of data members
byte	Number of functions

*/

