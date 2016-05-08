

#include "StringTable.h"
#include <string.h>


CStringTable::CStringTable()
{
	StringBlock = new char[STRINGTABLE_SIZE];

	Index = 0;
}

/** Add string s to the table, returning its position. */
int CStringTable::Add(char *s)
{
	strcpy((char*)(StringBlock+Index),s);
	
	int StringPos = Index;

	Index = Index + strlen(s) + 1;

	return StringPos;
}

/** Return the size of the block of strings. */
int CStringTable::GetSize()
{

	return Index;
}

/**	Return a pointer to the block of strings. */
char* CStringTable::GetData()
{
	return StringBlock;
}


CStringTable::~CStringTable()
{
	delete StringBlock;
}