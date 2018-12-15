/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The WordCharSourceCodeInstruction is a
 * specific instruction that will handle
 * when a WORD instruction is used, and
 * the user is specifying to use a
 * character representation in the source
 * code.
 ******************************************/
#include <string>
#include "DataConverter.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "WordCharSourceCodeInstruction.h"

#define CHAR_ 'C'
#define SINGLE_QUOTE '\''
#define MIN_LENGTH 3

using namespace std;

WordCharSourceCodeInstruction::WordCharSourceCodeInstruction(
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

int WordCharSourceCodeInstruction::GetLength(){return _characters.length() * 3;}
string WordCharSourceCodeInstruction::ToString(){return GetInstructionType() + string(":") + _characters;}
string WordCharSourceCodeInstruction::GetInstructionType(){return SourceCodeInstruction::WORD;}
string WordCharSourceCodeInstruction::GetObjectCode()
{
	string returnValue;

	for(int i = 0; i < _characters.length(); i++)
	{
		int charInt = (int)_characters[i];
		string charStr = DataConverter::PadLeft(DataConverter::ConvertIntToHex(charInt), 6, '0');
		returnValue+= charStr;
	}

	return returnValue;
}
ModificationRecords WordCharSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}

