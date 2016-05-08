#if !defined(SYMTAB)
#define SYMTAB

#include <iostream>
#include <string.h>
#include <vector>

/** The different types of symbol: global variable, function etc. */
enum SymType   {
   GLOBAL_VAR,    // Global variable
   FN,  // function
   LOCAL,  //local variable
   PAR,		//parameter
   CLASS_SYM, //class
   DATA_MEMBER, //data member of a class
   MEMBER_FN, //member function of a class
};


/** A data structure for representing symbols such as variables etc. Includes such useful data as the address in
VM memory of a variable, the name of the symbol, etc. One symbol can point to another to create a series, such as
the paramaters of a function. */
class SymDesc {
public:
	SymDesc (char *_name, SymType _type,  int _line);
	~SymDesc ();
	
	char    *Name;   ///<Name of the symbol.
	unsigned int Address; ///<Address in VM memory of the data object (eg, variable) this symbol represents
	SymType  Type;   ///<Type of the symbol.
	int      Line;   ///<Line where the symbol was first encountered in the source code.
	SymDesc *Next;   ///<Next symbol in the table.
	unsigned char NoParameters; ///<If this is a function, the number of its parameters.
	SymDesc *LocalVars;  ///<If this is a function, points to the symbols representing its local variables.
	unsigned char NoLocals; ///<The number of local variables, if this is a function.
	int Value; ///< eg, initial value of a global variable.
	SymDesc *DataMembers; ///<If this is a class, points to the symbols representing its data members.
	SymDesc *MemberFuncs; ///<If this is a class, points to the symbols representing its  member functions.
	unsigned char NoDataMembers; ///<The number of data members, if this is a class.
	unsigned char NoMemberFuncs;///<The number of member functions, if this is a class.
	int MemberNo; ///<Identifies which data member this is.
	unsigned char NoParents; ///<Number of parents if this is a class
	std::vector<SymDesc*> ParentList; ///<If this is a class, points to its parent classes.
	std::vector<SymDesc*>::iterator itor;
 
};


//typedef std::vector<SymDesc*> MyList;
//typedef std::vector<SymDesc*>::iterator itor;


/** A searchable structure for storing symbols. Symbols can have their own sub-lists of symbols, for example the 
local variables of function. */
class CSymbolTable  {
public:
	CSymbolTable();
	~CSymbolTable();
	bool Add (int Scope, SymDesc *symb);
 	SymDesc *Find (int Scope, char *name);
	void ResetGet();
	SymDesc* GetNext();
	void ClearCurrentClass();
	void ClearCurrentFn();
	SymDesc* CurrentFn;  ///<The current function being processed, if any.  
	SymDesc* CurrentObj;

private:
	void Append(SymDesc* &List, SymDesc* symb); ///<Add a symbol to the end of List.
	SymDesc *TableStart; ///<Points to the start of the list of symbols.
	int FreeGlobalVarNo;  ///<The next free register number for global variables.
	SymDesc* CurrentClass; ///<Most recent class symbol added.
	SymDesc* Next; ///<Keeps track of the next symbol for GetNext calls.
	int	CurrentMemberNo; ///<Current code number to use for a class member..

	//MyList MemberNameList;
	std::vector<SymDesc*> MemberNameList;
	std::vector<SymDesc*>::iterator itor;


};

#define GLOBAL_SCOPE 1
#define CURRENT_FN 2
#define CURRENT_CLASS 3
#define CURRENT_CLASS_PARENT 4
#define MEMBERS 5
#define CURRENT_OBJ 6


#endif