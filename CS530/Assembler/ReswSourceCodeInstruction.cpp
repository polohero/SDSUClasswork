/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ReswSourceCodeInstruction is a
 * specific instruction that will handle
 * when a RESW instruction is used. There is
 * no object code that gets created, just to
 * reserve a specific number of words.
 ******************************************/
#include <string>
#include <ctype.h>
#include <sstream>
#include "DataConverter.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "ReswSourceCodeInstruction.h"

#define MIN_LENGTH 1
#define SPACE ' '

using namespace std;

ReswSourceCodeInstruction::ReswSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{
	// First validate the line.
	if( _line.GetOperand().length() < MIN_LENGTH)
	{
		throw "ReswSourceCodeInstruction: Operand is not a valid length.";
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
			throw "ReswSourceCodeInstruction: Must be an integer value.";
		}
	}

	_length = DataConverter::GetStringToInt(integers);
	_length *= 3;
}

int ReswSourceCodeInstruction::GetLength(){return _length;}
string ReswSourceCodeInstruction::ToString(){return GetInstructionType() + string(":") +  DataConverter::GetIntToString(_length);}
string ReswSourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::RESW;}
string ReswSourceCodeInstruction::GetObjectCode(){return string("");}
ModificationRecords ReswSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}
