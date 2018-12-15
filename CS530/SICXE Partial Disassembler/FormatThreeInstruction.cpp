#include <string>
#include "Memory.h"
#include "Registers.h"
#include "Instruction.h"
#include "DataConverter.h"
#include "AssemblyOperation.h"
#include "FormatThreeInstruction.h"

using namespace std;

#define EXPECTED_LENGTH 6
#define DISPLACEMENT_START 3
#define DISPLACEMENT_END 5

FormatThreeInstruction::FormatThreeInstruction(
	AssemblyOperation operation,
	string instructionString,
	Memory memory,
	Registers registers) : Instruction(operation)
{
	// Validate everything is good with the instructionString
	if(0 == instructionString.length())
	{
		throw "FormatThreeInstruction.Instruction cannot be empty.";
	}

	if(0 == instructionString.compare(""))
	{
		throw "FormatThreeInstruction.Instruction cannot be and empty string.";
	}

	if(instructionString.length() < EXPECTED_LENGTH)
	{
		throw "FormatThreeInstruction. Instruction is too short. The Instruction is not valid.";
	}

	_instructionString = instructionString;

	string flags = DataConverter::GetNibbles(1, 2, _instructionString);

	_n = DataConverter::GetBoolFromChar(flags[2]);
	_i = DataConverter::GetBoolFromChar(flags[3]);
	_x = DataConverter::GetBoolFromChar(flags[4]);
	_b = DataConverter::GetBoolFromChar(flags[5]);
	_p = DataConverter::GetBoolFromChar(flags[6]);
	_e = DataConverter::GetBoolFromChar(flags[7]);

	if( true == _p && true == _b)
	{
		throw "FormatThreeInstruction. Cannot have Base and PC offseting.";
	}

	// Get the displacement value.
	// For this variable it will be returned as 4
	// bytes in binary format.
	string displacement =
		DataConverter::GetNibbles(
					DISPLACEMENT_START,
					DISPLACEMENT_END,
					_instructionString);

	// Now that we have masked the displacement.
	// Convert it into an integer value.
	_displacement = DataConverter::GetIntFromBinaryString(displacement);

	_targetAddress =
		getTargetAddress(
			registers,
			memory);

	_addressingMode = determineAddressingMode();
}


string FormatThreeInstruction::determineAddressingMode()
{
	if(false == _n && true == _i)
	{
		return "immediate addressing";
	}
	else if(true == _n && false == _i)
	{
		return "indirect addressing";
	}
	// Both true, and both false are the same.
	/*else if(true == _n && true == _i)
	{
		return "simple addressing";
	}*/
	else
	{
		return "simple addressing";
	}
}

int FormatThreeInstruction::getTargetAddress(
		Registers registers,
		Memory memory)
{
	int targetAddress = _displacement;

	// Handle any PC, B, or X addressing.
	// Then we can use the target address.
	if(true == _b)
	{
		targetAddress += registers.Get(Registers::B);
	}
	if(true == _p)
	{
		targetAddress += registers.Get(Registers::PC);
	}
	if(true == _x)
	{
		targetAddress += registers.Get(Registers::X);
	}

	return targetAddress;
}

string FormatThreeInstruction::ToString()
{
	string returnString = "";
	returnString.append(_operation.GetMnemonic());
	returnString.append("\t");
	returnString.append(" ");
	returnString.append(DataConverter::GetStringFromBool(_n));
	returnString.append(" ");
	returnString.append(DataConverter::GetStringFromBool(_i));
	returnString.append(" ");
	returnString.append(DataConverter::GetStringFromBool(_x));
	returnString.append(" ");
	returnString.append(DataConverter::GetStringFromBool(_b));
	returnString.append(" ");
	returnString.append(DataConverter::GetStringFromBool(_p));
	returnString.append(" ");
	returnString.append(DataConverter::GetStringFromBool(_e));
	returnString.append(" ");

	returnString.append(DataConverter::ConvertIntToHex(_displacement));
	returnString.append("\t");
	
	if( _addressingMode.compare(string("indirect addressing")) == 0)
	{
		returnString.append("(");	
		returnString.append(DataConverter::ConvertIntToHex(_targetAddress));
		returnString.append(")");
	}
	else
	{
		returnString.append(DataConverter::ConvertIntToHex(_targetAddress));
	}	

	returnString.append("\tfmt 3\t");
	returnString.append(_operation.GetExample());
	returnString.append(" ");
	returnString.append(_addressingMode);

	return returnString;
}

