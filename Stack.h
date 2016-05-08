#pragma once
#include <vector>


class CStateRec
{
public:
	int Seq_Count; ///<For tracking the number of items in an expression sequence. Eg, initialisation expressions for an array.

};

/** A simple stack to record values such as the number of nodes in a list, for occasions when recursion might introduce a new list halfway through. */

class CStateStack
{
public:
	CStateStack(void);
	~CStateStack(void);
	void InitState();
	void IncSeqCount();
	void Push();
	void Pop();

	CStateRec* State;
	int Seq_Count;

private:
	std::vector<CStateRec*> StateVector;
	std::vector<CStateRec*>::iterator itor;

};
