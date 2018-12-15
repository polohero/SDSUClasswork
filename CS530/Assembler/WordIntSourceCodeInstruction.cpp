/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The WordIntSourceCodeInstruction is a
 * specific instruction that will handle
 * when a WORD instruction is used, and
 * the user is specifying to use a
 * integer representation in the source
 * code.
 ******************************************/
#include <string>
#include <ctype.h>
#include "DataConverter.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "WordIntSourceCodeInstruction.h"

#define MIN_LENGTH 1
#define SPACE ' '
#define SIC_INT_LENGTH 3
#define MAX_INT 16777215

using namespace std;

WordIntSourceCodeInstruction::WordIntSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{
	// First validate the line.
	if( _line.GetOperand().length() < MIN_LENGTH)
	{
		throw "WordIntSourceCodeInstruction: Operand is not a valid length.";
	}

	string integers;

	for(int i = 0; i < _line.GetOperand().length(); i++)
	{
		if( _line.GetOperand()[i] == SPACE)
		{
			break;
		}
		else if( isdigit(_line.GetOperand()[i]) )
		{
			integers += _line.GetOperand()[i];
		}
		else
		{
			throw "WordIntSourceCodeInstruction: Must be an integer value.";
		}
	}

	_integer = DataConverter::GetStringToInt(integers);

	if( _integer > MAX_INT )
	{
		"WordIntSourceCodeInstruction: Integer is too large.";
	}
}

int WordIntSourceCodeInstruction::GetLength(){return SIC_INT_LENGTH;}
string WordIntSourceCodeInstruction::ToString(){return GetInstructionType() + string(":") +  DataConverter::GetIntToString(_integer);}
string WordIntSourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::WORD;}
string WordIntSourceCodeInstruction::GetObjectCode(){return DataConverter::PadLeft(DataConverter::ConvertIntToHex(_integer), 6, '0');}
ModificationRecords WordIntSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}
