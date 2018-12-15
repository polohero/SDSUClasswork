/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The BaseSourceCodeInstruction is a
 * compiler instruction that helps it keep
 * track of the current value of the base
 * register.
 ******************************************/
#include <string>
#include <ctype.h>
#include <sstream>
#include "Symbol.h"
#include "SymbolTable.h"
#include "DataConverter.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "BaseSourceCodeInstruction.h"

#define MIN_LENGTH 1
#define SPACE ' '

using namespace std;

BaseSourceCodeInstruction::BaseSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{
	// First validate the line.
	if( _line.GetOperation().compare(string(SourceCodeInstruction::BASE)) != 0)
	{
		throw "BaseSourceCodeInstruction: Operation is not a BASE.";
	}
}

int BaseSourceCodeInstruction::GetLength(){return 0;}
string BaseSourceCodeInstruction::ToString(){return GetInstructionType() + string(":") +  _line.GetOperand();}
string BaseSourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::BASE;}
string BaseSourceCodeInstruction::GetObjectCode()
{
	string errorMessage;

	Symbol* symbol =
		SymbolTable::Get(_line.GetOperand());

	if( symbol == 0 )
	{
		errorMessage += "Invalid symbol. Symbol: ";
		errorMessage += _line.GetOperand();
		errorMessage += " not found. ";
		throw errorMessage.c_str();
	}

	SourceCodeInstruction::BASE_VALUE = symbol->GetAddress();

	return string("");
}
ModificationRecords BaseSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}
