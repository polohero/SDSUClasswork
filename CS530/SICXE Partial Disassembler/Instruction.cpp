#include <string>
#include "Instruction.h"
#include "AssemblyOperation.h"

using namespace std;

Instruction::Instruction (AssemblyOperation operation)
{
	_operation = operation;
}

AssemblyOperation Instruction::GetAssemblyOperation()
{
	return _operation;
}

string Instruction::ToString()
{
	return _operation.GetMnemonic();
}
