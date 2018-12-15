#include <string>
#include "Registers.h"
#include "Instruction.h"
#include "DataConverter.h"
#include "AssemblyOperation.h"
#include "FormatTwoInstruction.h"

using namespace std;

#define EXPECTED_LENGTH 4

FormatTwoInstruction::FormatTwoInstruction(
	AssemblyOperation operation,
	string instructionString) : Instruction(operation)
{
	// Validate.
	if(0 == instructionString.length())
	{
		throw "FormatTwoInstruction.Instruction cannot be empty.";
	}

	if(0 == instructionString.compare(""))
	{
		throw "FormatTwoInstruction.Instruction cannot be and empty string.";
	}

	if(instructionString.length() < EXPECTED_LENGTH)
	{
		throw "Instruction is too short. The Instruction is not valid.";
	}

	_instructionString = instructionString;

	_r1 = " ";
	_r2 = " ";

	_r1 = _instructionString[2];
	_r2 = _instructionString[3];

}

string FormatTwoInstruction::ToString()
{
	string returnString = "";
	returnString.append(_operation.GetMnemonic());
	returnString.append("\t - - - - - -");

	returnString.append(" ");
	returnString.append(_r1);
	returnString.append(",");
	returnString.append(_r2);

	returnString.append("\t");
	returnString.append("n/a");
	returnString.append("\t");
	returnString.append("fmt 2\t");
	returnString.append(_operation.GetExample());

	return returnString;
}

