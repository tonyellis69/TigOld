// Coder.cpp: implementation of the CCoder class.
//
//////////////////////////////////////////////////////////////////////

#include "Coder.h"
#include <stdio.h>
#include "SyntaxNode.h"
#include "Tig.hpp"
#include "Tig.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCoder::CCoder()
{
	lbl = 0;
	CurrentFunc = NULL;
	Diagram = false;
	Verbose = true;
	Depth=0;

	GlobalTree = new CSyntaxNode(typeOpr); //start the global tree off
	//TO DO call GlobalTree Root
	CurrentGlobalNode = GlobalTree;
	//GlobalTree->nops = 2;
	//GlobalTree->oper = ';';
}

/** Open the bytecode output file for writing. */
int CCoder::OpenFile(char* Filename)
{
	CodeFile.open(Filename, std::ios::binary); //open the file we'll write code to
	CodeFile.seekp(HEADER_SIZE); 	//leave file space for header, which we'll fill later

	//write a basic definition for our built-in array class
	/*	CodeFile << '\0\0'; //zero parents or data members
	WriteByte(3);

	Member = Node->op[0]->symbol->MemberFuncs;
	for (x=0;x < Node->op[0]->symbol->NoMemberFuncs; x++) {
	WriteDWord(Member->MemberNo); 
	WriteDWord(Member->Address); 
	Member = Member->Next;
	}
	*/
	return true;
}

/** Get a pointer to the symbol table so we can refer to it. */
int CCoder::SetSymbolTable(CSymbolTable* st)
{
	SymTable = st; //TO DO: make sure we  have to do this!
	return true;
}



/** Walk the syntax tree p, writing the appropriate byte code for each node. The main function of CCoder. Recursive. */
int CCoder::Encode(CSyntaxNode* Node)
{
	if (Diagram) {//We're writing a text tree instead of encoding, so just leave now.
		WriteDiagram(Node);
		return false;
	}
	int lbl1, lbl2;
	unsigned int LoopStart, Dummy, Dummy2;
	unsigned int TableStart; unsigned int MemberFuncsEnd;
	std::vector<SymDesc*>::iterator ParentItor;	

	int Branch;
	float rr = 0.5;
	UserReturn = false; //True when a function ends with a user-written return statement.
	//TO DO: what happens if there's a return in an if statement, but not at the *actual* end of the func??
	//FAIL 

	if (!Node)  
		return false;

	switch(Node->NodeType) {
	case typeIntCon:       //Reached an integer constant. eg, the node for '5' in the expression x = 5
		WriteInstruct1Op(PUSHC, Node->value);	//instruct that it is pushed onto the stack for later use.
		break;
	case typeFloat:       //Reached a float constant. eg, the node for '0.5' in the expression x = 0.5
		WriteInstruct1Op(PUSHF, Node->fvalue);	//instruct that it is pushed onto the stack for later use.
		break;
	case typeArrayMemb:       //The member in an array->member operation. TO DO: find a better way to do this
		WriteInstruct(PUSHC, Node->value);	//wherever we find a numerical constant, we push it onto the stack for later use.
		printf("\tpushC %d\n", Node->value); 
		break;
	case typeId:        //An identifier. eg, the node for 'x' in the expression 2 + x
		if (Node->symbol->Type == GLOBAL_VAR) { 
			WriteInstructByte(PUSHG, Node->symbol->Address);	//push the contents of the identified global variable onto the stack.												
			printf("\tgpush %s (global %d)\n", Node->symbol->Name, (signed char)Node->symbol->Address);
		} else { //it's local
			WriteInstruct1OpByte(PUSH, Node->value); //instruct that the contents of the address associated with this identifier are
												//pushed onto the stack - ie, of the variable it represents.
			//TO DO: I don't think Node->value is set to the variable address when the variable is local
			//test this when reimplementing functions/local variables.
		}
		break;
	case typeStrCon:    //A string, ie, "Hello Tig!".  
		WriteSingleInstruct(STR); 
		WriteString(StrData+Node->value); //write the string itself to the bytecode file.
		break;
	case typeMemb:  //A reference to an object data member. Eg, the address of 'MyObj' and value of 'Str' in 'MyObj->Str'.
		//TO DO: I think this will always be the current object	
		if (Node->symbol == 0) {
			WriteInstructByte(PUSH, 0); //the address of which is always in local variable 0 (this)
			printf("\tpush this (local 0)\n");
			WriteInstruct(PUSHC, Node->value); //the member no
			printf("\tpushC %d\n",Node->value); 
			WriteSingleInstruct(PUSH_PROP); 
			printf("\tPushProp\n");
			break;
		}
		printf("\tpushProp %s member %d\n",Node->symbol->Name,Node->value);
		Write2OpInstruct(PUSH_PROP,Node->symbol->Address,Node->value);		


		break;

	case typeElem:  //A reference to an array element. Eg, x[5].
		Encode(Node->op[0]); //write code for the expression that puts the element number(s) on the stack
		WriteInstructByte(PUSH_ELEM,Node->symbol->Address);	
		printf("\tpushElem %s \n",Node->symbol->Name);
		break;


	case typeClassName:        //A value representing a class
		//	WriteDWord(Node->symbol->Address);	//push the associated VM memory address onto the stack.													//Normally the storage space of a variable.
		//	printf("\t\t\tParent\t%s  %d\n", Node->symbol->Name, Node->symbol->Address);
		break;


	case typeOpr:	  //An operator node. Most nodes are operators, eg, 'PRINT', or '=' in the expression x = 5, etc
		switch(Node->oper) {
	case WHILE:		//A while statement
		LoopStart = CodeFile.tellp(); 			//record loop start position
		printf("L%03d:\n", lbl1 = lbl++);

		Encode(Node->op[0]); //write code for While condition

		//jump out of loop
		printf("\tjz\tL%03d\n", lbl2 = lbl++);
		Dummy = CodeFile.tellp(); //position of dummy address
		WriteBranch(JZ,0); //jump to dummy address

		Encode(Node->op[1]); //write code for While task

		//jump back to loop start
		Branch = LoopStart  - (( int)CodeFile.tellp() + OPCODE_SIZE + BRANCH_SIZE ); 

		printf("\tjmp\tL%03d\n", lbl1);
		printf("L%03d:\n", lbl2);
		WriteBranch(JMP,Branch); 

		//insert loop end address where we put JMP dummy address
		Branch = ( int)CodeFile.tellp()  - (Dummy + BRANCH_SIZE + OPCODE_SIZE);
		InsertBranch(Dummy + OPCODE_SIZE,Branch); 
		UserReturn = false; //Kludge to disregard any return statement within a loop statement.
		break;
	case FOR:		//A for statement
		//do the initialisation:
		Encode(Node->op[0]->op[0]);

		LoopStart = CodeFile.tellp(); 			//record loop start position
		printf("L%03d:\n", lbl1 = lbl++);

		Encode(Node->op[0]->op[1]); //write code for For condition

		//jump out of loop
		printf("\tjz\tL%03d\n", lbl2 = lbl++);
		Dummy = CodeFile.tellp(); //position of dummy address
		WriteBranch(JZ,0); //jump to dummy address

		Encode(Node->op[1]); //write code for For task

		//Do the For increment:
		Encode(Node->op[0]->op[2]);

		//jump back to loop start
		Branch = LoopStart  - ((int)CodeFile.tellp() + OPCODE_SIZE + BRANCH_SIZE ); 

		printf("\tjmp\tL%03d\n", lbl1);
		printf("L%03d:\n", lbl2);
		WriteBranch(JMP,Branch); 

		//insert loop end address where we put JMP dummy address
		Branch = (int)CodeFile.tellp()  - (Dummy + BRANCH_SIZE + OPCODE_SIZE);
		InsertBranch(Dummy + OPCODE_SIZE,Branch); 
		UserReturn = false; //Kludge to disregard any return statement within a loop statement.
		break;
	case IF:
		Encode(Node->op[0]); //write code for test condition
		if (Node->nops > 2) { // it's an if else statement 

			// jump to the Else code 
		//	printf("\tjz\tL%03d\n", lbl1 = lbl++);
			Dummy = CodeFile.tellp(); //position of dummy address
		//	WriteBranch(JZ,0); //write a jump to a dummy address

			writeBranch(JZ, lbl1 = lbl++);

			Encode(Node->op[1]);  //write the If True code

			//jump out of the If statement
			//printf("\tjmp\tL%03d\n", lbl2 = lbl++);
			//printf("L%03d:\n", lbl1);
			Dummy2 = CodeFile.tellp(); //position of dummy address
			//WriteBranch(JMP,0); //jump to dummy address

			writeBranch(JMP, lbl2 = lbl++);
			if (Verbose)
				printf("\nL%03d:", lbl1);


			Branch = (int)CodeFile.tellp()  - (Dummy + BRANCH_SIZE + OPCODE_SIZE );
			InsertBranch(Dummy + OPCODE_SIZE,Branch);
			Encode(Node->op[2]); //write the Else code
			if (Verbose)
				printf("\nL%03d:", lbl2);
			Branch = (int)CodeFile.tellp()  - (Dummy2 + BRANCH_SIZE + OPCODE_SIZE);
			InsertBranch(Dummy2 + OPCODE_SIZE,Branch);	

		} else { //it's an straight if statement
			//jump out of the If statement if the condition is false
			Dummy = CodeFile.tellp(); //position of dummy address
			//WriteBranch(JZ,0); //write a jump to a dummy address
			writeBranch(JZ,lbl1 = lbl++);
			//printf("\tjz\tL%03d\n", lbl1 = lbl++);

			Encode(Node->op[1]); //write the If True code
			if (Verbose)
				printf("\nL%03d:", lbl1);
			Branch = (int)CodeFile.tellp()  - (Dummy + BRANCH_SIZE + OPCODE_SIZE );
			InsertBranch(Dummy + OPCODE_SIZE,Branch);
		}
		UserReturn = false; //Kludge to disregard any return statement within an IF statement.
		break;
	case PRINT:     
		if (Node->op[0]->NodeType == typeStrCon)  {	//we're printing a string constant
			WritePrintStr(Node);
		}
		else {
			Encode(Node->op[0]);  // ensure value to print will end up on the stack
			WriteSingleInstruct(PRINT_VAL); //we're printing a numerical value //TO DO change if we also print objects this way
		}

		if (Node->nops == 2) //we're printing a string followed by an expression
		{
			Encode(Node->op[1]); //encode the expression, 
			WriteSingleInstruct(PRINT_VAL); //print the value of the expression
			printf("\tprint numeric \n");
		}
		break;
	case FUNC: //write the bytecode for a function definition.
		//make a note of which function we're writing, so we know how many local variables etc
		CurrentFunc = Node->op[0]->symbol;
		//record address of function for when we call it elsewhere in our bytecode:
		Node->op[0]->symbol->Address = CodeFile.tellp();
		printf("\n\tFunction %s:\n",CurrentFunc->Name);

		//First operation in a function must be Link, to initialise local variables, etc
		WriteSingleInstruct(LINK);
		WriteByte(CurrentFunc->NoLocals);
		//printf("\n\tlink %d\n",CurrentFunc->NoLocals);



		Encode(Node->op[1]); //do function code
		CurrentFunc = NULL;  //all done, so this is no longer the current function 

		//was this the main function? Ensure it ends with an exit instruction then.
		if (strcmp(Node->op[0]->symbol->Name,"main") == 0)	{
			WriteSingleInstruct(EXIT);
			break;
		}

		if (UserReturn != true) { //user omitted return, so insert a default one							
			printf("\treturn_true \n");
			WriteSingleInstruct(RETURN_TRUE);
		}
		break;
	case FUNC_CALL: //write the bytecode for a function call where the return value is thrown away.
	case FUNC_CALL_RET: //write the bytecode for a function call where the return value is returned.
		//whatever function we're already in, save its local variables and params to the stack until we return:

		//Encode any supplied parameter values for the function we're calling 
		Encode(Node->op[1]);

		//Finally, write the code to jump to the given function

		switch (Node->op[0]->NodeType) {
	case typeOpr:	//TO DO: big mess here, this will always be typeOpr so cases below never reached
		Encode(Node->op[0]);
		/*	if (Node->op[0]->symbol == 0) { //this is a call to a sibling function of the same class
		Write2OpInstruct(CALL_MEMB,0,Node->op[0]->value);
		printf("\tcall_memb (current object) member[%d]\n",Node->op[0]->value);
		}
		else {  //ordinary member function call
		Write2OpInstruct(CALL_MEMB,Node->op[0]->symbol->Address,Node->op[0]->value);
		printf("\tcall_memb %s member[%d]\n",Node->op[0]->symbol->Name,Node->op[0]->value); 
		}*/
		if (Node->op[0]->op[1]->NodeType == typeArrayMemb) { //we've trapped an array-function all
			WriteSingleInstruct(CALL_ARRAY_MEMB);
			printf("\tcall_array_memb ");
		}
		else {
			WriteSingleInstruct(CALL_MEMB);
			printf("\tcall_memb ");
		}

		break;
	//TO DO: are these operators, like FOR and PRINT? if not, move them out of the typeOpr sub-section
	case typeMemb: //trapped a call to a function local to the current object
		WriteInstructByte(PUSH, 0); //the address of which is always in local variable 0 (this)
		printf("\tpush this (local 0)\n");
		WriteInstruct(PUSHC, Node->op[0]->value); //the member no
		printf("\tpushC %d\n",Node->op[0]->value); 
		WriteSingleInstruct(CALL_MEMB);
		printf("\tcall_memb ");

		break;
	case typeSuperMemb:
		if (Node->op[0]->symbol == 0) { //this is a call to a superclassed sibling function of the same class
			Write2OpInstruct(CALL_PARENT_MEMB,0,Node->op[0]->value);
			printf("\tcall_parent_memb (current object) member[%d] ",Node->op[0]->value);
		}
		else {  //ordinary superclassed member function call
			Write2OpInstruct(CALL_PARENT_MEMB,Node->op[0]->symbol->Address,Node->op[0]->value);
			printf("\tcall_parent_memb %s member[%d] ",Node->op[0]->symbol->Name,Node->op[0]->value);
		}

		break;
	case typeArrayMemb:
		Write2OpInstruct(CALL_ARRAY_MEMB,Node->op[0]->symbol->Address,Node->op[0]->value);
		printf("\tcall_array_memb %s member[%d] ",Node->op[0]->symbol->Name,Node->op[0]->value);
		break;
	default: //ordinary function call
		WriteInstruct(CALL, Node->op[0]->symbol->Address);
		printf("\tcall\t%s %d ", Node->op[0]->symbol->Name,Node->op[0]->symbol->Address);
		}


		WriteByte( Node->value); //the number of parameters in the function call
		printf(" (params %d)\n", Node->value); 

		if (Node->oper == FUNC_CALL) { 	//when we return, discard whatever value has been returned on the stack.
			WriteSingleInstruct(DISCARD);
			printf("\n\tdiscard\n"); //TO DO: see if we can use a special CALL opcode to clear the stack, rather than this.
		}
		break;
	case FN_RETURN: //the user has supplied a return-from-function - implement it
		if (Encode(Node->op[0])) {
			WriteSingleInstruct(RETURN); //execute any expression being returned, eg, return x + 1, leaving result on stack
			printf("\n\treturn\n");  }

		else {
			WriteSingleInstruct(RETURN_TRUE); //No expression? Just return 'true'
			printf("\n\treturn_true \n"); }
		UserReturn = true;  //

		break;
	case CLASS: //A class definition 
		//make a note of which class we're writing, so we know how many data members etc
		CurrentClass = Node->op[0]->symbol;
		//record address of class:
		Node->op[0]->symbol->Address = CodeFile.tellp();
		printf("\n\tClass %s at %d,",CurrentClass->Name,Node->op[0]->symbol->Address);

		WriteByte( Node->value); //write number of parent classes this class has
		printf(" parents: %d",Node->op[0]->symbol->NoParents);

		WriteByte( Node->op[0]->symbol->NoDataMembers); //write the number of data members this class has
		printf(" data members: %d",Node->op[0]->symbol->NoDataMembers);

		//write the number of member functions
		WriteByte( Node->op[0]->symbol->NoMemberFuncs); //write the number of member functions this class has
		printf(" funcs: %d :",Node->op[0]->symbol->NoMemberFuncs);

		//list the parent classes of this class, if any
		if (Node->op[0]->symbol->NoParents > 0)
			printf("\n\tparents: ");

		for (ParentItor = Node->op[0]->symbol->ParentList.begin(); ParentItor != Node->op[0]->symbol->ParentList.end();
			ParentItor++) { 
				WriteDWord((*ParentItor)->Address);	//push the associated VM memory address onto the stack.
				printf("%s (%d) ", (*ParentItor)->Name, (*ParentItor)->Address);
		}


		//write a table ofthe member number of each data member this class has
		if (Node->op[0]->symbol->NoDataMembers > 0)
			printf("\n\tdata members: ");
		int x;
		SymDesc* Member;
		Member = Node->op[0]->symbol->DataMembers;
		for (x=0;x < Node->op[0]->symbol->NoDataMembers; x++) {
			WriteDWord(Member->MemberNo); //TO DO: consider having a variable word-length func, in case size changes
			printf("%s (%d) ",Member->Name,Member->MemberNo);
			Member = Member->Next;
		}


		TableStart = CodeFile.tellp(); 			//record table start position

		//write a table of each member function this class has, leaving a space for the function address.
		//printf("\n\t\tFunctions: %d ",Node->op[0]->symbol->NoMemberFuncs);
		Member = Node->op[0]->symbol->MemberFuncs;
		for (x=0;x < Node->op[0]->symbol->NoMemberFuncs; x++) {
			WriteDWord(Member->MemberNo); 
			WriteDWord(0); 
			Member = Member->Next;
		}
		printf("\n");

		Encode(Node->op[2]); //encode member functions

		//only now do we know addresses of member functions. So go back and enter addresses in the class table
		MemberFuncsEnd = CodeFile.tellp(); //record current position

		//Back to table:
		CodeFile.seekp(TableStart);

		Member = Node->op[0]->symbol->MemberFuncs;
		for (x=0;x < Node->op[0]->symbol->NoMemberFuncs; x++) {
			WriteDWord(Member->MemberNo); 
			WriteDWord(Member->Address); 
			Member = Member->Next;
		}

		CodeFile.seekp(MemberFuncsEnd); //back to where we left off

		CurrentClass = NULL;  //all done, so this is no longer the current function 
		break;
	case NEW: //A NEW object operation
		WriteInstruct(PUSHC,Node->op[0]->symbol->Value); //the size of the object to be created
		printf("\tpushC %d\n", Node->op[0]->symbol->Value);
		//TO DO: can we dispense with the above, and work out size at compile time?
		WriteInstruct(NEW_OBJ, Node->op[0]->symbol->Address); //write the class number
		//WriteByte(Node->op[0]->symbol->Value); //write the size of the object to be created
		printf("\tnew %s addr %d\n",Node->op[0]->symbol->Name,Node->op[0]->symbol->Address);
		//Now encode any initialisation expressions for this object
		Encode(Node->op[1]);
		break;
	case DATA_TYPE: //a DATA_TYPE operation
		Encode(Node->op[0]);
		WriteSingleInstruct(TYPE);
		//printf("\ttype %s (local %d)\n", Node->op[0]->symbol->Name, Node->op[0]->symbol->Address);
		printf("\ttype\n");
		break;
	case STR_INPUT: //an INPUT operation
		WriteSingleInstruct(INPUT);
		printf("\tinput\n");
		break;
	case ARRAY: //an instruction to create an ARRAY
		Encode(Node->op[0]); //encode all expressions for the array's dimensions, eg, [n+1]
		WriteInstruct(NEW_OBJ, ARRAY_CLASS); //write the class number for array objects
		//WriteByte(Node->value ); //write the number of dimensions
		printf("\tnew array\n" );
		break;
	case TABLE: //an instruction to create an table
		Encode(Node->op[0]); //encode all expressions for the table's dimensions, eg, [n+1][25]
		Encode(Node->op[1]);
		WriteInstruct(NEW_OBJ, TABLE_CLASS); //write the class number for array objects
		printf("\tnew table\n" );
		break;
	case RAND: //an instruction to generate a random number.
		Encode(Node->op[0]); //encode all expressions for the operands
		Encode(Node->op[1]);
		WriteSingleInstruct(RND);
		printf("\trnd\n");
		break;
	case '=': //An assigment operation
		Encode(Node->op[1]); //calculate the result, then come back when it's on the stack
		if (Node->op[0]->NodeType == typeMemb) {//we've trapped an assignment to a data member 
			//TO DO: won't an assignment to type memb always be a member of the current object?
			if (Node->op[0]->symbol == 0) { //its a member of the current object
				WriteInstructByte(PUSH, 0); //the address of which is always in local variable 0 (this)
				printf("\tpush this (local 0)\n");
				WriteInstruct(PUSHC, Node->op[0]->value); //the member no
				printf("\tpushC %d\n",Node->op[0]->value); 
				WriteSingleInstruct(PUT_PROP); //do the put-into-property instruction
				printf("\tPutProp\n");


				//Write2OpInstruct(PUT_PROP,0,Node->op[0]->value);		//obj = 0 means use the current object
				//printf("\tputProp (current object) member %d\n",Node->op[0]->value);
				break;
			}


			//	Write2OpInstruct(PUT_PROP,Node->op[0]->symbol->Address,Node->op[0]->value);
			//	printf("\tputProp %s member %d\n",Node->op[0]->symbol->Name,Node->op[0]->value); break;
		}
		if (Node->op[0]->oper == MEMB_ASSIGN ) { //trapped an assignment to a obj->mem data member
			//	Node->op[0]->op[1]->oper=';';
			Encode(Node->op[0]);	//resolve the -> sequence

			WriteSingleInstruct(PUT_PROP); //do the put-into-property instruction
			printf("\tPutProp\n");
			break;
		}
		if (Node->op[0]->oper == DEREF_ASSIGN ) { //trapped an assignment to a data member
			Encode(Node->op[0]);	//resolve the -> sequence

			WriteSingleInstruct(PUT_PROP); //do the put-into-property instruction
			printf("\tPutProp\n");
			break;
		}

		/*	if (Node->op[0]->NodeType == typeElem) {   //we've trapped an assignment to an array element
		Encode(Node->op[0]->op[0]); //element no(s), eg, 1,2 for a[1][2] = 5
		WriteInstructByte(PUT_ELEM,Node->op[0]->symbol->Address); 
		printf("\tputElem %s \n",Node->op[0]->symbol->Name);
		break;
		}
		*/
		if (Node->op[0]->oper == ARRAY_ASSIGN ) {   //we've trapped an assignment to an array element
			Encode(Node->op[0]);	//resolve the array-and-element 

			WriteSingleInstruct(PUT_ELEM); //do the put-into-element instruction
			printf("\tPutElem\n");

			//Encode(Node->op[0]->op[0]); //element no(s), eg, 1,2 for a[1][2] = 5
			//WriteInstructByte(PUT_ELEM,Node->op[0]->symbol->Address); 
			//printf("\tputElem %s \n",Node->op[0]->symbol->Name);
			break;
		}

		else { //assignment to a global variable
			if (Node->op[0]->symbol->Type == GLOBAL_VAR) {
				WriteInstruct1OpByte(POPG, Node->op[0]->symbol->Address); 
			//	printf("\tpopG %s (global %d)\n", Node->op[0]->symbol->Name,Node->op[0]->symbol->Address);

			} else { //normal assignment to a variable
				//WriteInstructByte(POP, Node->op[0]->symbol->Address); //pop the result on the stack into it
				//printf("\tpop %s (local %d)\n", Node->op[0]->symbol->Name,Node->op[0]->symbol->Address);
				//call it WriteInstruct1OpByte
				WriteInstruct1OpByte(POP,Node->op[0]->symbol->Address);
			}
		}
		break;
	case UMINUS:    //negative number 
		Encode(Node->op[0]);  //push numeral on stack
		WriteSingleInstruct(NEG); //make it negative 
		printf("\tneg\n");
		break;
	case INIT_STACK: //initialise an object member with the value on the top of the stack
		Encode(Node->op[1]); //evaluate the intitialiser expression 
		WriteInstruct(INIT_STACK, Node->op[0]->value);
		printf("\tInitStack (member %d) \n",Node->op[0]->value );
		break;
	case ARROW: //use the get property instruction
		Encode(Node->op[0]);
		Encode(Node->op[1]);
		WriteSingleInstruct(PUSH_PROP);
		printf("\tPushProp\n ");
		break;
	case ARRAY_ELEMENT: 	

		Encode(Node->op[1]);
		Encode(Node->op[0]); 
		WriteSingleInstruct(PUSH_ELEM);
		printf("\tpushElem\n");				
		break;
	case ARRAY_LIST:  //creating a predefined array
		Encode(Node->op[0]); //will set up all the initialisation values on the stack
		//Stick size of the array on the stack
		WriteInstruct(PUSHC, Node->value);
		printf("\tPusCh %d (array size)\n",Node->value );
		WriteInstruct(NEW_OBJ, PREDEF_ARRAY); //create array 
		printf("\tnew PredefArray\n" );
		break;
	case TABLE_LIST:  //creating a predefined table
		Encode(Node->op[0]); //will set up all the initialisation values on the stack
		//Stick size of the array on the stack
		WriteInstruct(PUSHC, Node->value);
		printf("\tPushC %d (table columns)\n",Node->value );
		WriteInstruct(PUSHC, Node->value2);
		printf("\tPushC %d (array rows)\n",Node->value2 );
		WriteInstruct(NEW_OBJ, PREDEF_TABLE); //create table 
		printf("\tnew PredefTable\n" );
		break;
	default: //default action: two operands and an operator. 
		Encode(Node->op[0]);
		Encode(Node->op[1]);
		switch(Node->oper) {
	case '+':	WriteSingleInstruct(ADD); break;
	case '-':   WriteSingleInstruct(SUB); break; 
	case '*':   WriteSingleInstruct(MUL); break;
	case '/':   WriteSingleInstruct(DIV); break;
	case '%':   WriteSingleInstruct(MOD); break;
	case '<':   WriteSingleInstruct(COMPLT);break;
	case '>':   WriteSingleInstruct(COMPGT); break;
	case GE:    WriteSingleInstruct(COMPGE);break;
	case LE:    WriteSingleInstruct(COMPLE);break;
	case NE:    WriteSingleInstruct(COMPNE);break;
	case EQ:    WriteSingleInstruct(COMPEQ); break;
	case AND:   WriteSingleInstruct(COMPAND); break;
	case OR:    WriteSingleInstruct(COMPOR); break;


		} //NB operator can also be a null operator, eg ';', for when we want to encode a list of parameters etc
		}
	}
	CodeEnd = CodeFile.tellp(); //record point at which code ends
	return true;
}

int CCoder::WriteDiagram(CSyntaxNode* Node)
{
	int OpNo;

	printf("\n");
	for (int t=0;t<Depth;t++) //indent correctly
		printf(" ");

	if (!Node)  {
		printf("Null node");
		//Depth--;
		return false;
	}


	switch (Node->NodeType) {
		case typeIntCon:			printf("constant "); break;
		case typeId:			printf("identifier %s ", Node->symbol->Name); break;
		case typeFloat:			printf("float "); break;
		case typeOpr:			printf("operator %s ", OpNamer(Node->oper)); break;
		case typeStrCon:		printf("string "); break;
		case typeMemb:		printf("member "); break;
		case typeClassName:		printf("class name "); break;
		case typeSuperMemb:		printf("super member "); break;
		case typeElem:			printf("element "); break;
		case typeArrayMemb:		printf("array member "); break;
		case typeError:			printf("error "); break;

	}



	printf("Nops %d ",Node->nops);
	//if (Node->nops > 0)
	Depth++;
	for (OpNo=0;OpNo < Node->nops;OpNo++) {//For each child node this node has
		WriteDiagram(Node->op[OpNo]);
	}
	Depth--;
	return true;
}

/** Return a pointer to a string holding the name of the given operator. */
char* CCoder::OpNamer(int Op)
{
	if (Op > INTEGER) 
		return (char*) OpNames[Op - INTEGER]; //Kludge! Requires INTEGER to always be the first token.
	if (Op == ';')
		return (char*) "list";
	static char buf[2];
	buf[0] = Op;
	buf[1] = 0;
	return (char*) buf;
}

/**	Append this node to the list of global syntax nodes. */
void CCoder::AppendGlobal(CSyntaxNode* Node)
{
	//add this node to the tree of global nodes

	//attach node the current node
	CurrentGlobalNode->op[0] = Node;

	//create a new child node
	CSyntaxNode* NextGlobalNode = new CSyntaxNode(typeOpr);
	CurrentGlobalNode->oper = ';';

	//TO DO: give ; it's own syntaxnode type, typeIntConnector or something
	//ChildNode->nops = 2;
	//ChildNode->oper = ';';

	//make sure this node points to it 
	CurrentGlobalNode->op[1] = NextGlobalNode;
	CurrentGlobalNode->nops =2;
	CurrentGlobalNode = NextGlobalNode;
}


int CCoder::GetStrTablePtr(char* Str)
{
	StrData = Str;
	return true;
}



/** Write an instuction and operand. */
int CCoder::WriteInstruct(unsigned int Opcode, unsigned  int Operand)
{
	//write opcode
	CodeFile.write((char*)&Opcode,OPCODE_SIZE);
	CodeFile.write((char*)&Operand,OPERAND_SIZE); 	//write operand
	return true;
}

/** Write an instuction and a floating-point operand. */
int CCoder::WriteInstructF(unsigned int Opcode, float Operand)
{
	//write opcode
	CodeFile.write((char*)&Opcode,OPCODE_SIZE);
	CodeFile.write((char*)&Operand,OPERAND_SIZE); 	//write operand
	return true;
}

/** Write an instuction and 1-byte operand. */
int CCoder::WriteInstructByte(unsigned int Opcode, unsigned  char Operand)
{
	//write opcode
	CodeFile.write((char*)&Opcode,OPCODE_SIZE);
	CodeFile.write((char*)&Operand,1); 	//write operand
	return true;
}


/** Go back to the given address and insert the give branch offset. Used for forward branches, where the jump forward
couldn't be calculated at the time. */
int CCoder::InsertBranch(unsigned int Address,  int Branch)
{
	int Current = CodeFile.tellp();
	CodeFile.seekp(Address);
	CodeFile.write((char*)&Branch,BRANCH_SIZE);
	CodeFile.seekp(Current);
	return true;
}

/** Write a branch instruction and the branch offset. A negative number for a branch back, positive for foward. The 
subraction/addition takes place from the address after this instruction and offset. */
int CCoder::WriteBranch(unsigned int Opcode, int Branch)
{
	CodeFile.write((char*)&Opcode,OPCODE_SIZE); //write operator
	CodeFile.write((char*)&Branch,BRANCH_SIZE); 	//write offset
	return true;
}



/** Write an instruction with two opcodes. */
int CCoder::Write2OpInstruct(unsigned int Opcode, unsigned int Operand1,unsigned int Operand2)
{
	CodeFile.write((char*)&Opcode,OPCODE_SIZE); 	//write opcode
	CodeFile.write((char*)&Operand1,1);	//write operand
	CodeFile.write((char*)&Operand2,OPERAND_SIZE);	//write operand
	return true;
}





/** Write a double word. */
int CCoder::WriteDWord(unsigned int DWord)
{
	CodeFile.write((char*)&DWord,DWORD_SIZE);
	return true;
}

/** Write floating point value as a double word. */
int CCoder::WriteDWordF(float DWord)
{
	CodeFile.write((char*)&DWord,DWORD_SIZE);
	return true;
}


int CCoder::EncodeGlobal()
{
	printf("\n\n\t[Main code]\n");

	//record where in the file we're writing this
	EntryPt = (int)CodeFile.tellp();

	//Complain if there is no 'main' function. 
	//TO DO: if we have global statements, main may no longer be compulsory.
	if (SymTable->Find(GLOBAL_SCOPE,"main") == NULL) {
		fprintf(stdout, "Function 'main' not found. Every program must have a function called 'main' as its entrypoint.");
		//return false;
		WriteSingleInstruct(LINK);
		WriteByte(0);

	}

	

	//	if (GlobalTree->op[0]->op[0] != NULL) {
	//printf("\n\n\t[Main code]\n");
	//Turn the contents of the global syntax tree into bytecode
	Encode(GlobalTree);
	//	}

	return true;
}


/** Add the syntax nodes for the 'main' function to the global syntax tree. */
int CCoder::AddMain(CSyntaxNode* MainFn) {
	CSyntaxNode* NewGlobalRoot = new CSyntaxNode(typeOpr);

	NewGlobalRoot->op[0] = GlobalTree;
	NewGlobalRoot->op[1] = MainFn;
	NewGlobalRoot->nops = 2;

	GlobalTree = NewGlobalRoot;
	return true;
}


/** Write the header details and then close the file. Such details include the address to start execution at, the 
address of the string table, etc. */
int CCoder::CloseFile()
{	
	//write the header
	CodeFile.seekp(0);

	CodeFile.write(reinterpret_cast<char*>(&EntryPt),ADDR_SIZE); //record point at which to start execution

	//CodeEnd = CodeEnd - HEADER_SIZE;
//	CodeFile.write(reinterpret_cast<char*>(&CodeEnd),ADDR_SIZE); //record point at which code ends

	CodeFile.close();
	return true;
}



CCoder::~CCoder()
{

}

