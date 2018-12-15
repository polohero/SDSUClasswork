#include <string>
#include <iostream>
#include <sstream>

#include "Memory.h"
#include "Registers.h"
#include "Instruction.h"
#include "DataConverter.h"
#include "AssemblyOperation.h"
#include "FormatZeroInstruction.h"

using namespace std;

#define EXPECTED_LENGTH 6
#define X_INDEX 2
#define FALSE_FLAG '0'
#define DISPLACEMENT_START 2
#define DISPLACEMENT_END 5

FormatZeroInstruction::FormatZeroInstruction(
	AssemblyOperation operation,
	string instructionString,
	Memory memory,
	Registers registers) : Instruction(operation)
{
	// Validate everything is good with the instructionString
	if(0 == instructionString.length())
	{
		throw "FormatZeroInstruction.Instruction cannot be empty.";
	}

	if(0 == instructionString.compare(""))
	{
		throw "FormatZeroInstruction.Instruction cannot be and empty string.";
	}

	if(instructionString.length() < EXPECTED_LENGTH)
	{
		throw "FormatZeroInstruction. Instruction is too short. The Instruction is not valid.";
	}

	_instructionString = instructionString;

	// Get the X value from the instruction.
	// This x variable will be the 2 bits, stored as binary.
	// But we only care about the first BIT.
	string x = DataConverter::GetNibble(X_INDEX, _instructionString);

	// Interpret the X bit.
	if(x[0] == FALSE_FLAG)
	{
		_x = false;
	}
	else
	{
		_x = true;
	}

	// Get the displacement value.
	// For this variable it will be returned as 4
	// bytes in binary format.
	string displacement =
		DataConverter::GetNibbles(
							DISPLACEMENT_START,
							DISPLACEMENT_END,
							_instructionString);


	// Mask the X bit. This will
	// always be interpreted as 0.
	displacement[0] = '0';

	// Now that we have masked the displacement.
	// Convert it into an integer value.
	_displacement = DataConverter::GetIntFromBinaryString(displacement);

	// Depending on X set the target address.
	if(true == GetX())
	{
		_targetAddress = _displacement + registers.Get(Registers::X);
	}
	else
	{
		_targetAddress = _displacement;
	}
}


string FormatZeroInstruction::ToString()
{
	string returnString = "";
	returnString.append(_operation.GetMnemonic());
	returnString.append("\t -");
	returnString.append(" -");
	returnString.append(" ");
	if(true == GetX())
	{
		returnString.append("1");
	}
	else
	{
		returnString.append("0");
	}

	returnString.append(" -");
	returnString.append(" -");
	returnString.append(" -");

	returnString.append(" ");
	returnString.append(DataConverter::ConvertIntToHex(_displacement));
	returnString.append("\t");

	returnString.append(DataConverter::ConvertIntToHex(_targetAddress));
	returnString.append("\tfmt 0\t");
	returnString.append(_operation.GetExample());


	return returnString;
}


bool FormatZeroInstruction::GetX()
{
	return _x;
}

int FormatZeroInstruction::GetDisplacement()
{
	return _displacement;
}

int FormatZeroInstruction::GetTargetAddress()
{
	return _targetAddress;
}

