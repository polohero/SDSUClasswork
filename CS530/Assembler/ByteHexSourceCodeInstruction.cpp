/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ByteHexSourceCodeInstruction is a
 * specific instruction that will handle
 * when a BYTE instruction is used, and
 * the user is specifying to use a
 * hexidecimal representation in the source
 * code.
 ******************************************/
#include <string>
#include "DataConverter.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "ByteHexSourceCodeInstruction.h"

#define HEX_ 'X'
#define SINGLE_QUOTE '\''
#define MIN_LENGTH 3

ByteHexSourceCodeInstruction::ByteHexSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{
	// First validate the line.
	if( _line.GetOperand().length() < MIN_LENGTH)
	{
		throw "ByteHexSourceCodeInstruction: Operand is not a valid length.";
	}

	if( _line.GetOperand()[0] != HEX_)
	{
		throw "ByteHexSourceCodeInstruction: Operand does not start with X.";
	}

	if( _line.GetOperand()[1] != SINGLE_QUOTE)
	{
		throw "ByteHexSourceCodeInstruction: Operand does not have an opening.";
	}

	bool foundClosingQuote = false;

	for(int i = 2; i < _line.GetOperand().length(); i++)
	{
		if( _line.GetOperand()[i] == SINGLE_QUOTE)
		{
			foundClosingQuote = true;
			break;
		}

		_hexCharacters += _line.GetOperand()[i];
	}

	if( foundClosingQuote == false )
	{
		throw "Invalid Hex character defined. No closing single quotes found.";
	}

	if( _hexCharacters.length() > 2 )
	{
		throw "Invalid Hex character defined. Length too long.";
	}
}

void ByteHexSourceCodeInstruction::validateHex(char character)
{
		switch (toupper(character))
		{
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					case 'A':
					case 'B':
					case 'C':
					case 'D':
					case 'E':
					case 'F': return;
		}

		throw "ByteHexSourceCodeInstruction: Invalid hex character.";
}



int ByteHexSourceCodeInstruction::GetLength(){return _hexCharacters.length() / 2;}
std::string ByteHexSourceCodeInstruction::ToString(){return GetInstructionType() + std::string(":") +  _hexCharacters;}
std::string ByteHexSourceCodeInstruction::GetInstructionType(){return SourceCodeInstruction::BYTE;}
std::string ByteHexSourceCodeInstruction::GetObjectCode(){return DataConverter::PadLeft(_hexCharacters, 2, '0');}
ModificationRecords ByteHexSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}



