#if !defined(STRTAB)
#define STRTAB

#define	STRINGTABLE_SIZE 1024 ///<Max size of the table bytes

/** A structure for storing a series of strings. */
class CStringTable {
public:
	CStringTable ();
	~CStringTable ();
	int Add(char *s);
	int GetSize();
	char*	GetData();

private:
	char* StringBlock; ///<Pointer to the table data.
	int Index; ///<Indexes the next free address in the table.

}; 

#endif
