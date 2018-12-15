/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The StartSourceCodeInstruction is a
 * specific instruction that is the first
 * instruction in the source file.
 ******************************************/
#include <string>
#include <ctype.h>
#include <sstream>
#include "DataConverter.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "StartSourceCodeInstruction.h"

#include "DataConverter.h"

#define MIN_LENGTH 1
#define SPACE ' '

using namespace std;

StartSourceCodeInstruction::StartSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{
	// First validate the line.
	if( _line.GetOperand().length() < MIN_LENGTH)
	{
		throw "StartSourceCodeInstruction: Operand is not a valid length.";
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
			throw "StartSourceCodeInstruction: Must be an integer value.";
		}
	}

	DataConverter::ConvertToIntFromHexString(_startingLocation, integers, hex);
	_location = _startingLocation;
}

int StartSourceCodeInstruction::GetLength(){return 0;}
string StartSourceCodeInstruction::ToString(){return GetInstructionType() + string(":") +  DataConverter::GetIntToString(_startingLocation);}
string StartSourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::START;}
string StartSourceCodeInstruction::GetObjectCode(){return string("");}
ModificationRecords StartSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}

