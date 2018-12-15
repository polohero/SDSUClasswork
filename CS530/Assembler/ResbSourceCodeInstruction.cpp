/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ResbSourceCodeInstruction is a
 * specific instruction that will handle
 * when a RESB instruction is used. There is
 * no object code that gets created, just to
 * reserve a specific number of bytes.
 ******************************************/
#include <string>
#include <ctype.h>
#include <sstream>
#include "DataConverter.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "ResbSourceCodeInstruction.h"

#define MIN_LENGTH 1
#define SPACE ' '

using namespace std;

ResbSourceCodeInstruction::ResbSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{
	// First validate the line.
	if( _line.GetOperand().length() < MIN_LENGTH)
	{
		throw "ResbSourceCodeInstruction: Operand is not a valid length.";
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
			throw "ResbSourceCodeInstruction: Must be an integer value.";
		}
	}

	_length = DataConverter::GetStringToInt(integers);
}

int ResbSourceCodeInstruction::GetLength(){return _length;}
string ResbSourceCodeInstruction::ToString(){return GetInstructionType() + string(":") +  DataConverter::GetIntToString(_length);}
string ResbSourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::RESB;}
string ResbSourceCodeInstruction::GetObjectCode(){return string("");}
ModificationRecords ResbSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}

