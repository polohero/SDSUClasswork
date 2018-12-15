/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ByteCharSourceCodeInstruction is a
 * specific instruction that will handle
 * when a BYTE instruction is used, and
 * the user is specifying to use a
 * character representation in the source
 * code.
 ******************************************/
#include <string>
#include "DataConverter.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "ByteCharSourceCodeInstruction.h"

#define CHAR_ 'C'
#define SINGLE_QUOTE '\''
#define MIN_LENGTH 3

using namespace std;

ByteCharSourceCodeInstruction::ByteCharSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{
	// First validate the line.
	if( _line.GetOperand().length() < MIN_LENGTH)
	{
		throw "ByteCharSourceCodeInstruction: Operand is not a valid length.";
	}

	if( _line.GetOperand()[0] != CHAR_)
	{
		throw "ByteCharSourceCodeInstruction: Operand does not start with C.";
	}

	if( _line.GetOperand()[1] != SINGLE_QUOTE)
	{
		throw "ByteCharSourceCodeInstruction: Operand does not start with C.";
	}

	bool foundClosingQuote = false;

	for(int i = 2; i < _line.GetOperand().length(); i++)
	{
		if( _line.GetOperand()[i] == SINGLE_QUOTE)
		{
			foundClosingQuote = true;
			break;
		}

		_characters += _line.GetOperand()[i];
	}

	if( foundClosingQuote == false )
	{
		throw "Invalid Byte character defined. No closing single quotes found.";
	}
}

int ByteCharSourceCodeInstruction::GetLength(){return _characters.length();}
string ByteCharSourceCodeInstruction::ToString(){return GetInstructionType() + string(":") + _characters;}
string ByteCharSourceCodeInstruction::GetInstructionType(){return SourceCodeInstruction::BYTE;}
string ByteCharSourceCodeInstruction::GetObjectCode()
{
	string returnValue;

	for(int i = 0; i < _characters.length(); i++)
	{
		int charInt = (int)_characters[i];
		string charStr = DataConverter::PadLeft(DataConverter::ConvertIntToHex(charInt), 2, '0');
		returnValue+= charStr;
	}

	return returnValue;
}
ModificationRecords ByteCharSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}

