/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ByteIntSourceCodeInstruction is a
 * specific instruction that will handle
 * when a BYTE instruction is used, and
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
#include "ByteIntSourceCodeInstruction.h"

#define MIN_LENGTH 1
#define SPACE ' '
#define SIC_INT_LENGTH 1

using namespace std;

ByteIntSourceCodeInstruction::ByteIntSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{
	// First validate the line.
	if( _line.GetOperand().length() < MIN_LENGTH)
	{
		throw "ByteIntSourceCodeInstruction: Operand is not a valid length.";
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
			throw "ByteIntSourceCodeInstruction: Must be an integer value.";
		}
	}

	_integer = DataConverter::GetStringToInt(integers);

	if( _integer > 255 )
	{
		throw "ByteIntSourceCodeInstruction: Integer length only be 1 byte.";
	}
}

int ByteIntSourceCodeInstruction::GetLength(){return SIC_INT_LENGTH;}
string ByteIntSourceCodeInstruction::ToString(){return GetInstructionType() + string(":") +  DataConverter::GetIntToString(_integer);}
string ByteIntSourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::BYTE;}
string ByteIntSourceCodeInstruction::GetObjectCode(){return DataConverter::PadLeft(DataConverter::ConvertIntToHex(_integer), 2, '0');}
ModificationRecords ByteIntSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}
