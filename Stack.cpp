#include "Stack.h"

CStateStack::CStateStack(void)
{

	InitState();


}

///<Initialise the settings of the current state.
void CStateStack::InitState()
{
	//Create an initial blank state. 
	State = new CStateRec;
	Seq_Count = 0;
}

///<Push the current state onto to stack and start a new, initialised state.
void CStateStack::Push()
{
	State->Seq_Count = Seq_Count;
	StateVector.push_back(State);
	InitState();
}

///<Pop the last state off of the stack.
void CStateStack::Pop()
{
	delete State;
	State = StateVector.back();
	Seq_Count = State->Seq_Count;
	StateVector.pop_back();
}

	///<Function to read Seq_Count for the current state
	///<Function to push the current state onto the stack and start a fresh state








CStateStack::~CStateStack(void)
{
}
