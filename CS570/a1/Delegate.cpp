using namespace std;

#include "Delegate.h"

#define NULL 0

Delegate::Delegate(
	functionPointer function)
{
	Delegate::_function = function;
	Delegate::_argument = NULL;
}

Delegate::Delegate(
	functionPointer function,
	void* argument)
{
	Delegate::_function = function;
	Delegate::_argument = argument;
}

Delegate::Delegate()
{

}


functionPointer Delegate::GetFunction()
{
	return Delegate::_function;
}

void* Delegate::GetArgument()
{
	return Delegate::_argument;
}
