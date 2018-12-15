/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SourceCodeInstructionFactory is
 * in charge of determining what type of
 * instruction this line of source code
 * is, and return a specific source code
 * instruction class.
 ******************************************/
#include <string>
#include <iostream>
#include "SymbolTable.h"
#include "Literal.h"
#include "LiteralTable.h"
#include "SourceCodeLine.h"
#include "SourceCodeFile.h"
#include "AssemblyOperation.h"
#include "SourceCodeInstruction.h"
#include "AssemblyOperationTable.h"
#include "SourceCodeInstructionFactory.h"

#include "EquSourceCodeInstruction.h"
#include "EndSourceCodeInstruction.h"
#include "BaseSourceCodeInstruction.h"
#include "ResbSourceCodeInstruction.h"
#include "ReswSourceCodeInstruction.h"
#include "StartSourceCodeInstruction.h"
#include "WordIntSourceCodeInstruction.h"
#include "WordHexSourceCodeInstruction.h"
#include "WordCharSourceCodeInstruction.h"
#include "CommentSourceCodeInstruction.h"
#include "ByteHexSourceCodeInstruction.h"
#include "ByteIntSourceCodeInstruction.h"
#include "ByteCharSourceCodeInstruction.h"

#include "LiteralSourceCodeInstruction.h"
#include "LiteralPoolSourceCodeInstruction.h"

#include "Format0SourceCodeInstruction.h"
#include "Format1SourceCodeInstruction.h"
#include "Format2SourceCodeInstruction.h"
#include "Format3SourceCodeInstruction.h"
#include "Format4SourceCodeInstruction.h"

#define CHAR_ 'C'
#define HEX_ 'X'
#define PLUS '+'
#define EQUAL '='

using namespace std;

SourceCodeInstruction*
	SourceCodeInstructionFactory::GetSourceCodeInstruction(
		string line,
		int machineType,
		SourceCodeFile* file)
{
    int currentLocation = file->GetLocationCounter();

	SourceCodeLine sourceLine =
		SourceCodeLine(line);
	AssemblyOperationTable opTable;

	AssemblyOperation* operation =
		opTable.Get(sourceLine.GetOperation());

	// Check if the line is a comment.
	// If it is, create a new comment
	// instruction type.
	if( sourceLine.IsCommentLine() )
	{
		return new CommentSourceCodeInstruction(sourceLine);
	}
	// Check if this is an actual machine instruction
	// and figure out what type of
	// instruction class needs to be used.
	else if( operation != 0 )
	{
		if( machineType == SourceCodeInstruction::SIC_BASIC )
		{
			return new Format0SourceCodeInstruction(
					line,
					operation);

		}
		else
		{
			int numberOfFormats = operation->NumberOfFormatsPossible();

			// If it has 0 formats. It must be a data setup issue.
			if(0 == numberOfFormats)
			{
				throw "Invalid Operation. This indicates the AssemblyOperation.load method is missing data";
			}
			// If there is one. We know what the format is.
			else if(1 == numberOfFormats)
			{
				return handleSingleOperation(
							line,
							operation
						);

			}
			// If there is > 1. Then we'll have to
			// figure it out.
			else if( sourceLine.GetOperationPrefix().length() == 1 &&
			         sourceLine.GetOperationPrefix()[0] == PLUS)
			{
				return new Format4SourceCodeInstruction(
						line,
						operation);


			}
			else
			{
				return new Format3SourceCodeInstruction(
						line,
						operation);
			}
		}
	}
	// Check if this is a EQU compiler
	// directive.
	else if (sourceLine.GetOperation().compare(SourceCodeInstruction::EQU) == 0)
	{
		return new EquSourceCodeInstruction(
				line,
				currentLocation);
	}
	// Check if this is a BASE compiler
	// directive.
	else if (sourceLine.GetOperation().compare(SourceCodeInstruction::BASE) == 0)
	{
		return new BaseSourceCodeInstruction(
				line);
	}
	// Check if this is a LTORG compiler
	// directive.
	else if (sourceLine.GetOperation().compare(SourceCodeInstruction::LTORG) == 0)
	{
		return new LiteralPoolSourceCodeInstruction(
				line);
	}
	else if (sourceLine.GetOperation().compare(SourceCodeInstruction::WORD) == 0)
	{
		if( sourceLine.GetOperand()[0] == CHAR_ )
		{
			return new WordCharSourceCodeInstruction(sourceLine);
		}
		else if( sourceLine.GetOperand()[0] == HEX_ )
		{
			return new WordHexSourceCodeInstruction(sourceLine);
		}
		else
		{
			return new WordIntSourceCodeInstruction(sourceLine);
		}
	}
	// Check if this is a BYTE compiler
	// directive.
	else if (sourceLine.GetOperation().compare(SourceCodeInstruction::BYTE) == 0)
	{
		if( sourceLine.GetOperand()[0] == CHAR_ )
		{
			return new ByteCharSourceCodeInstruction(sourceLine);
		}
		else if( sourceLine.GetOperand()[0] == HEX_ )
		{
			return new ByteHexSourceCodeInstruction(sourceLine);
		}
		else
		{
			return new ByteIntSourceCodeInstruction(sourceLine);
		}
	}
	// Check if this is a START compiler
	// directive.
	else if (sourceLine.GetOperation().compare(SourceCodeInstruction::START) == 0)
	{
		return new StartSourceCodeInstruction(sourceLine);
	}
	// Check if this is a END compiler
	// directive.
	else if (sourceLine.GetOperation().compare(SourceCodeInstruction::END) == 0)
	{
		return new EndSourceCodeInstruction(sourceLine);
	}
	// Check if this is a RESB compiler
	// directive.
	else if (sourceLine.GetOperation().compare(SourceCodeInstruction::RESB) == 0)
	{
		return new ResbSourceCodeInstruction(sourceLine);
	}
	// Check if this is a RESW compiler
	// directive.
	else if (sourceLine.GetOperation().compare(SourceCodeInstruction::RESW) == 0)
	{
		return new ReswSourceCodeInstruction(sourceLine);
	}

	string errorMessage = "Unknown instruction: ";
	errorMessage += sourceLine.GetOperation();

	throw errorMessage.c_str();
}

SourceCodeInstruction* SourceCodeInstructionFactory::handleSingleOperation(
	string line,
	AssemblyOperation* operation)
{
	// Pretty simple. Check the format
	// and create the specific
	// instruction type based on it.
	string format = operation->GetFormat();

    // Is it a format 1?
	if(format.compare(AssemblyOperation::FORMAT_1) == 0)
	{
		return new Format1SourceCodeInstruction(
				line,
				operation);
	}
	// Is it a format 2?
	else if(format.compare(AssemblyOperation::FORMAT_2) == 0)
	{
		return new Format2SourceCodeInstruction(
					line,
					operation);
	}

	// No format found. Return 0
	// and let the caller decide what to do.
	return 0;
}



int SourceCodeInstructionFactory::DetermineMachineType(string line)
{
	SourceCodeLine sourceLine =
		SourceCodeLine(line);

	AssemblyOperation* operation =
		_opTable.Get(sourceLine.GetOperation());

	// If this is a comment line, then it doesn't matter
	// what machine type.
	if(true == sourceLine.IsCommentLine())
	{
		return SourceCodeInstruction::SIC_BASIC;
	}
	// This must not be an operation.
	// Check if it's a compiler directive.
	else if( NULL == operation )
	{
		return SourceCodeInstruction::SIC_BASIC;
	}
	// Then this must be an operation. To
	// know what machine we are targeting we
	// need to do some more checking.
	else
	{
		// If there is only one format allowed for this
		// operation, it's easy. Just check if that one
		// is a format 0.
		if( 1 == operation->NumberOfFormatsPossible() )
		{
			if( operation->GetFormat().compare(AssemblyOperation::FORMAT_0) == 0 )
			{
				return SourceCodeInstruction::SIC_BASIC;
			}
			else
			{
				return SourceCodeInstruction::SIC_XE;
			}
		}


		// Otherwise we have to check all of the
		// different format types.
		bool allowsBasic = false;

		// Check and see what formats are allowed
		// for this operation. If XE is not allowed
		// then we know that it has to be basic.
		for(int i = 0; i < operation->GetFormat().length(); i++)
		{
			// TODO.. pull out '0' to a const somewhere.
			if( operation->GetFormat()[i] == '0' )
			{
				allowsBasic = true;
			}
		}

		if( false == allowsBasic )
		{
			return SourceCodeInstruction::SIC_XE;
		}

		// Now it gets a little complicated.

		// Check for extended format.
		if( sourceLine.GetOperationPrefix().compare("") != 0 )
		{
			return SourceCodeInstruction::SIC_XE;
		}
		// Check for different addressing modes.
		else if( sourceLine.GetOperandPrefix().compare("") != 0 )
		{
			return SourceCodeInstruction::SIC_XE;
		}
		else
		{
			return SourceCodeInstruction::SIC_BASIC;
		}
	}
}


SourceCodeInstruction* SourceCodeInstructionFactory::GetLiteral(Literal literal, SourceCodeLine line)
{
	return new LiteralSourceCodeInstruction(line, literal);
}



/***************************************************
UNIT TESTS
g++ SourceCodeLine.cpp SourceCodeInstruction.cpp DataConverter.cpp AssemblyOperationTable.cpp AssemblyOperation.cpp SourceCodeInstructionFactory.cpp
**************************************************/
/*
int main()
{
	SourceCodeInstructionFactory factory;

	string currentTest;


	currentTest = "Comment Line";
	int commentLine =
		factory.DetermineMachineType(".COPY     +START  #0                                                            ");
	if(commentLine == SourceCodeInstruction::SIC_BASIC)
	{
		cout << "PASSED MachineType: " << commentLine << endl;
	}
	else
	{
		cout << "FAILED MachineType: " << commentLine << endl;
	}

	currentTest = "Compiler Directive Line";
	int directive =
		factory.DetermineMachineType("COPY      START   0                                                            ");
	if(directive == SourceCodeInstruction::SIC_BASIC)
	{
		cout << "PASSED directive: " << directive << endl;
	}
	else
	{
		cout << "FAILED directive: " << directive << endl;
	}

	currentTest = "LDX basic";
	int ldxBasic =
		factory.DetermineMachineType("COPY      LDX   0                                                            ");
	if(directive == SourceCodeInstruction::SIC_BASIC)
	{
		cout << "PASSED ldxBasic: " << ldxBasic << endl;
	}
	else
	{
		cout << "FAILED ldxBasic: " << ldxBasic << endl;
	}

	currentTest = "LDX XE";
	int ldxXE =
		factory.DetermineMachineType("COPY     +LDX   0                                                            ");
	if(ldxXE == SourceCodeInstruction::SIC_XE)
	{
		cout << "PASSED +ldxXE: " << ldxXE << endl;
	}
	else
	{
		cout << "FAILED +ldxXE: " << ldxXE << endl;
	}

	currentTest = "LDX XE";
	ldxXE =
		factory.DetermineMachineType("COPY      LDX   #0                                                            ");
	if(ldxXE == SourceCodeInstruction::SIC_XE)
	{
		cout << "PASSED #ldxXE: " << ldxXE << endl;
	}
	else
	{
		cout << "FAILED #ldxXE: " << ldxXE << endl;
	}

	currentTest = "LDB XE";
	int ldxBXE =
		factory.DetermineMachineType("COPY      LDB   0                                                      ");
	if(ldxBXE == SourceCodeInstruction::SIC_XE)
	{
		cout << "PASSED ldxBXE: " << ldxBXE << endl;
	}
	else
	{
		cout << "FAILED ldxBXE: " << ldxBXE << endl;
	}


	return 0;
}
*/
