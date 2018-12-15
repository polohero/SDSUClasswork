#include <string>
#include "Instruction.h"
#include "AssemblyOperation.h"
#include "FormatOneInstruction.h"

using namespace std;

FormatOneInstruction::FormatOneInstruction(
	AssemblyOperation operation,
	string instructionString
	) : Instruction(operation)
{
	_instructionString = instructionString;
}

string FormatOneInstruction::ToString()
{
	string returnString = "";
	returnString.append(_operation.GetMnemonic());
	returnString.append("\t - - - - - - n/a\tn/a\tfmt 1\t");
	returnString.append(_operation.GetExample());

	return returnString;
}

