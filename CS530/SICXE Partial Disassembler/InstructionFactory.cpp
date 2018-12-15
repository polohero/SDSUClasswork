#include <string>
#include "Memory.h"
#include "Registers.h"
#include "Instruction.h"
#include "DataConverter.h"
#include "AssemblyOperation.h"
#include "InstructionFactory.h"
#include "FormatOneInstruction.h"
#include "FormatTwoInstruction.h"
#include "FormatZeroInstruction.h"
#include "FormatFourInstruction.h"
#include "FormatThreeInstruction.h"
#include "AssemblyOperationTable.h"

#define ZERO_FORMAT '0'
#define THREE_FORMAT '3'
#define FOUR_FORMAT '4'
#define TRUE_FLAG '1'
#define FALSE_FLAG '0'
#define MACHINE_TYPE_INDEX 1
#define E_INDEX 2
#define E_NIBBLE_INDEX 3
#define N_INDEX 2
#define I_INDEX 3

using namespace std;

Instruction* InstructionFactory::Create(
	string instruction,
	Memory memory,
	Registers registers,
	AssemblyOperationTable assemblyOperations)
{
	// Validatet the instruction.
	if( 0 == instruction.length())
	{
		throw "Instruction cannot be empty.";
	}

	if( "" == instruction)
	{
		throw "Instruction cannot be a blank line.";
	}
;
	// First thing we need to do to pre-process
	// this Instruction is to determine the
	// op code for this instruction.
	int opCode = getOpCode(instruction);

	// Check if we know what this operation is.
	// If not, we have a problem.
	if(false == assemblyOperations.IsValidOpcode(opCode))
	{
		throw "Opcode was not found.";
	}

	AssemblyOperation operation = assemblyOperations.Get(opCode);

	// Based on the data for this operation
	// we need to determine what format/s
	// the instruction could be.
	int numberOfFormats = operation.NumberOfFormatsPossible();

	// If it has 0 formats. It must be a data setup issue.
	if(0 == numberOfFormats)
	{
		throw "Invalid Operation. This indicates the AssemblyOperation.load method is missing data";
	}
	// If there is one. We know what the format is.
	else if(1 == numberOfFormats)
	{
		return handleSingleOperation(
					instruction,
					operation,
					memory,
					registers
				);
	}
	// If there is > 1. Then we'll have to
	// figure it out.
	else if(numberOfFormats >= 2)
	{
		return handleMultiOperation(
					instruction,
					operation,
					memory,
					registers
				);
	}

	return 0;
}


Instruction* InstructionFactory::handleMultiOperation(
	string instructionString,
	AssemblyOperation operation,
	Memory memory,
	Registers registers)
{
	string formats = operation.GetFormat();

	// Loop through each of the formats
	// and decide what format it is based on
	// the data we can find in the instruction string.
	for(int i = 0; i < formats.length(); i++)
	{
		// If 0 is an option. Check if we're using
		// SIC basic or XE.
		if(ZERO_FORMAT  == formats[i] )
		{
			string nibble =
				DataConverter::GetNibble(MACHINE_TYPE_INDEX, instructionString);

			// If both of these bytes are 0, then  we know
			// it's a SIX basic instruction and must
			// be a format 0.
			if(nibble[N_INDEX] == FALSE_FLAG &&
			   nibble[I_INDEX] == FALSE_FLAG)
			{
				return new FormatZeroInstruction(
						operation,
						instructionString,
						memory,
						registers);
			}
		}
		// If three is an option.
		else if(THREE_FORMAT == formats[i])
		{
			string nibbleInstruction =
				DataConverter::GetNibble(MACHINE_TYPE_INDEX, instructionString);

			// First check the instruction is an XE.
			// Otherwise it cannot be a format 3.
			if(nibbleInstruction[N_INDEX] == TRUE_FLAG ||
			   nibbleInstruction[I_INDEX] == TRUE_FLAG)
			{
				string nibbleE =
					DataConverter::GetNibble(E_INDEX, instructionString);
				// Next check the E bit. If
				// E is set, it cannot be a format 3.
				if(nibbleE[E_NIBBLE_INDEX] == FALSE_FLAG)
				{
					return new FormatThreeInstruction(
							operation,
							instructionString,
							memory,
							registers);
				}
			}
		}
		// If four is an option.
		else if(FOUR_FORMAT == formats[i])
		{
			// Check if it's a SIC XE machine.
			string nibbleInstruction =
				DataConverter::GetNibble(MACHINE_TYPE_INDEX, instructionString);

			if(nibbleInstruction[N_INDEX] == TRUE_FLAG ||
			   nibbleInstruction[I_INDEX] == TRUE_FLAG)
			{
				// Next check the E bit.
				string nibbleE =
					DataConverter::GetNibble(E_INDEX, instructionString);
				if(nibbleE[E_NIBBLE_INDEX] == TRUE_FLAG)
				{
					return new FormatFourInstruction(
							operation,
							instructionString,
							memory,
							registers);
				}
			}
		}
	}


	return 0;
}


Instruction* InstructionFactory::handleSingleOperation(
	string instructionString,
	AssemblyOperation operation,
	Memory memory,
	Registers registers)
{
	// Pretty simple. Check the format
	// and create the specific
	// instruction type based on it.
	string format = operation.GetFormat();

	// Is it a format 0?
	if(format.compare(AssemblyOperation::FORMAT_0) == 0)
	{
		return new FormatZeroInstruction(
				operation,
				instructionString,
				memory,
				registers);
	}
    // Is it a format 1?
	else if(format.compare(AssemblyOperation::FORMAT_1) == 0)
	{
		return new FormatOneInstruction(
				operation,
				instructionString);
	}
	// Is it a format 2?
	else if(format.compare(AssemblyOperation::FORMAT_2) == 0)
	{
		return new FormatTwoInstruction(
			operation,
			instructionString);
	}
	// Is it a format 3?
	else if(format.compare(AssemblyOperation::FORMAT_3) == 0)
	{
		return new FormatThreeInstruction(
				operation,
				instructionString,
				memory,
				registers);
	}
	// Is it a format 4?
	else if(format.compare(AssemblyOperation::FORMAT_4) == 0)
	{
		 return new FormatFourInstruction(
			 	operation,
			 	instructionString,
			 	memory,
			 	registers);
	}

	// No format found. Return 0
	// and let the caller decide what to do.
	return 0;
}

int InstructionFactory::getOpCode(string instruction)
{
	if( instruction.length() < 2)
	{
		throw "OpCode cannot be determined. The Instruction is not the correct length.";
	}

	string opCode = "";
	opCode.append(DataConverter::GetBinaryStringFromHexChar(instruction[0]));
	opCode.append(DataConverter::GetBinaryStringFromHexChar(instruction[1]));

	if( opCode.length() != 8)
	{
		throw "OpCode cannot be determined. The binary code returned by the DataConverter is not valid.";
	}

	// Mask the last 2 bits. This method doesn't
	// care if it's an XE or Basic. It just wants
	// to get the Op Code from the instruction.
	opCode[6] = '0';
	opCode[7] = '0';

	return DataConverter::GetIntFromBinaryString(opCode);
}
