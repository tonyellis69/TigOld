#include <stdio.h>
#include <string.h>
#include "symtab.h"
#include "Tig.h"


/** Create and initialise a new Symbol Table symbol. Typically a variable, function, etc. */
SymDesc::SymDesc (char *_name, SymType _type,  int _line)    {
	Name = new char[strlen(_name) +1];  
	strcpy (Name, _name);
	Type = _type;
    Line = _line;
	Next = NULL;			
	NoParameters = 0;
	LocalVars = NULL;
	Value = 0;
	NoLocals = 0;
	DataMembers = NULL;
	MemberFuncs = NULL;
	NoDataMembers = 0;
	NoMemberFuncs = 0;
	MemberNo = 0;
	NoParents = 0;
	//ParentList = NULL;
}

SymDesc::~SymDesc ()  {
   if (this == NULL)   return;
   if (Name != NULL)   delete [] Name;
}



/** The table of every unique symbol in the source code. Symbols are named objects such as variables, functions etc. */
CSymbolTable::CSymbolTable()   {
	TableStart = NULL; //The symbol table starts empty
	FreeGlobalVarNo = 1;// TOTAL_LOCALS + 1; //first free register for global variables
	CurrentFn = NULL;  
	CurrentClass = NULL;
	CurrentObj = NULL;
	CurrentMemberNo = 1; //we'll reserve 0.

	//create a class symbol for our built-in array class.
	SymDesc* ArrayClass = new SymDesc("CArray", CLASS_SYM,  0 );
	Add(GLOBAL_SCOPE, ArrayClass);


	//Add some built-in member names
	SymDesc* BuiltIn = new SymDesc("size", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("add", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("delete", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("insert", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("swap", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	ClearCurrentClass();

	//create a class symbol for our built-in table class.
	SymDesc* TableClass = new SymDesc("CTable", CLASS_SYM,  0 );
	Add(GLOBAL_SCOPE, TableClass);


	//Add some built-in member names
		BuiltIn = new SymDesc("rows", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("columns", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("add_row", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("delete_row", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("insert_row", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("add_column", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("delete_column", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("insert_column", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("swap_row", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);

	BuiltIn = new SymDesc("swap_column", MEMBER_FN,  0 );
	Add(CURRENT_CLASS, BuiltIn);





	CurrentMemberNo = FREE_MEMBER_NOS;
	ClearCurrentFn();
	ClearCurrentClass();

}

CSymbolTable::~CSymbolTable()   {
   delete TableStart;
}


/** Add another symbol to the global list or a sub-list, as determined by scope. */
bool CSymbolTable::Add (int Scope, SymDesc *symb)  {
	SymDesc* Result;
	
	switch(symb->Type) {
    case GLOBAL_VAR:   
		symb->Address = FreeGlobalVarNo;       //Record this global variable's register number
		FreeGlobalVarNo++; 
		break;
	case FN:
		CurrentFn = symb;  //symbol becomes the current function for the purposes of adding any local symbols that follow.
		break;
	case CLASS_SYM:	
		if (Scope == GLOBAL_SCOPE)
			CurrentClass = symb;  //symbol becomes the current class for the purposes of adding any local symbols.
		break;
	}

	switch(Scope) {
	case GLOBAL_SCOPE: 	
		Append(TableStart,symb); //Add this global symbol to the main (global) list
		break;
	case CURRENT_FN: //Add symbol to the list belonging to the current function 
		Append(CurrentFn->LocalVars,symb);

		//what type of local symbol is this?
		if (symb->Type == PAR) {
			symb->Address = -( (CurrentFn->NoParameters)  + FRAME_HEADER_OFFSET) ;
			CurrentFn->NoParameters++;
		}
		else if (symb->Type == LOCAL) {
			symb->Address = (CurrentFn->NoLocals + THIS_OFFSET );
			CurrentFn->NoLocals++;
		}
		if ((CurrentFn->NoLocals > TOTAL_LOCALS ) || (CurrentFn->NoParameters > TOTAL_PARAMS ))
			return false;
		break;
	case CURRENT_CLASS:		//Add this symbol to the list of members belonging to the current class
		Result = Find(MEMBERS,symb->Name);		//Search the list of unique member names for this name
		if (Result == NULL) {	//This is a new membername
			MemberNameList.push_back(symb);		//so add it to the list
			symb->MemberNo = CurrentMemberNo;	//and give it a unique member number.
			CurrentMemberNo++;					//Ensure every member gets its own unique code number.
		}
		else
			symb->MemberNo = Result->MemberNo;	//This member name already exists, so give the symbol its code number.
		if (symb->Type == DATA_MEMBER) {
			Append(CurrentClass->DataMembers,symb);	//Add the symbol to the current class's data members 
			CurrentClass->NoDataMembers++;			
		}
		if (symb->Type == MEMBER_FN) { //TO DO: see if we need a separate mem_func pointer or not
			Append(CurrentClass->MemberFuncs,symb);	//Add the symbol to the current class's data members 
			CurrentClass->NoMemberFuncs++;	
			CurrentFn = symb; //Make this the current function for the purposes of adding params etc.
		}

		break;
	case CURRENT_CLASS_PARENT:	//Add this symbol to the parent list of the current class
			CurrentClass->ParentList.push_back(symb);		//so add it to the list
			CurrentClass->NoParents++;
	break;

	}	  
   return true;
}


/** Add a symbol to the end of a list pointed to by List. */
void CSymbolTable::Append(SymDesc* &List, SymDesc* symb)
{
	if (List == NULL) //end of the list
      List = symb;
	else  {			 //no? Find the end of the list
      SymDesc *search = List;
      while (search->Next != NULL)
         search = search->Next;
      search->Next = symb;
   }	
}



/** Search for the named symbol in the symbol list. Either a global symbol, or a local symbol belonging to another, 
depending on scope. We also maintain a list of unique member names. */
SymDesc *CSymbolTable::Find (int Scope, char *Name)   {
   SymDesc* search, *Holder;
   std::vector<SymDesc*>::iterator ParentItor;
   switch (Scope) { //Scope determines where to search
   case CURRENT_FN:
	   if (CurrentFn == NULL)
		   return NULL;
	   search = CurrentFn->LocalVars; break;
   case CURRENT_CLASS:
	   if (CurrentClass == NULL)
		   return NULL;
	   search = CurrentClass->DataMembers; 
	   while (search != NULL && strcmp (search->Name, Name) != 0) //search for the named symbol among the data members
			search = search->Next;
	   if (search != NULL) 
		   return search;
	   search = CurrentClass->MemberFuncs; //Not found? Look among the member functions.
	    while (search != NULL && strcmp (search->Name, Name) != 0) //search for the named symbol among the data members
			search = search->Next;
		return search;
	break;
 case CURRENT_CLASS_PARENT:
		if (CurrentClass == NULL)
		   return NULL;
	   Holder = CurrentClass; 
		for (ParentItor = CurrentClass->ParentList.begin(); ParentItor != CurrentClass->ParentList.end();
			ParentItor++) { //search parent list
			CurrentClass = *ParentItor;
			search = Find(CURRENT_CLASS,Name);
			if (search == NULL)
				search = Find(CURRENT_CLASS_PARENT,Name);
			CurrentClass = Holder;
			if (search != NULL) 
				return search; 
		}
		CurrentClass = Holder;
		return NULL;
   case CURRENT_OBJ:
	   if (CurrentObj == NULL)
		   return NULL;
	   	//if ( (SymbTable.Find (CURRENT_CLASS,name) == NULL) && (SymbTable.Find (CURRENT_CLASS_PARENT,name) == NULL) ) {
		Holder = CurrentClass;
		CurrentClass = CurrentObj;
		search = Find(CURRENT_CLASS,Name);
		if (search == NULL)
			search = Find(CURRENT_CLASS_PARENT,Name);
		CurrentClass = Holder;
		return search;
	break;
   case GLOBAL_SCOPE:
	   search = TableStart; break;
   case MEMBERS:
		itor = MemberNameList.begin();
		while (itor != MemberNameList.end() && strcmp((*itor)->Name, Name) != 0 ) //search member name list
			itor++;
		if (itor == MemberNameList.end()) 
			return NULL; //not found
		return *itor;
   }
   while (search != NULL && strcmp (search->Name, Name) != 0) //We know where to look, now search for the named symbol
      search = search->Next;
   return search;
}

// Routines for iterating through list - not used currently.

/**	Set GetNext back to start of list. */
void CSymbolTable::ResetGet() 
{
	Next = TableStart;
}

/** Return the next symbol in the list. This ignores local symbols - we have no need to iterate through those. */
SymDesc* CSymbolTable::GetNext()
{
	SymDesc* result = Next;
	if (Next != NULL)
		Next = Next->Next;

	return result;
}




void CSymbolTable::ClearCurrentClass()
{
	CurrentClass = NULL;	
}


void CSymbolTable::ClearCurrentFn()
{
	CurrentFn = NULL;
}