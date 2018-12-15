/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Format1SourceCodeInstruction is
 * a single byte instruction. It only
 * contains the OP code, and does not have
 * any operands.
 ******************************************/
#include <string>
#include "DataConverter.h"
#include "AssemblyOperation.h"
#include "SymbolTable.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "Format1SourceCodeInstruction.h"

#define FORMAT_1_LENGTH 1

using namespace std;

Format1SourceCodeInstruction::Format1SourceCodeInstruction(
			SourceCodeLine line,
			AssemblyOperation* assemblyOperation)
			: SourceCodeInstruction(line)
{
	_assemblyOperation = assemblyOperation;
}

int Format1SourceCodeInstruction::GetLength(){return FORMAT_1_LENGTH;}
string Format1SourceCodeInstruction::ToString(){return GetInstructionType() + string(":") +  _assemblyOperation->GetMnemonic();}
string Format1SourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::FORMAT_1;}
ModificationRecords Format1SourceCodeInstruction::GetModificationRecords()
{
	ModificationRecords records;

	return records;
}

string Format1SourceCodeInstruction::GetObjectCode()
{
	string empty = string("");
	string errorMessage;
	string returnValue;

	if( _line.GetOperationPrefix().compare(empty) != 0)
	{
		errorMessage += _assemblyOperation->GetMnemonic();
		errorMessage += " does not allow for any operation prefixes.";
		throw errorMessage.c_str();
	}
	else if( _line.GetOperandPrefix().compare(empty) != 0)
	{
		errorMessage += _assemblyOperation->GetMnemonic();
		errorMessage += " does not allow for any operand prefixes.";
		throw errorMessage.c_str();
	}
	else if( _line.GetOperand().compare(empty) != 0)
	{
		errorMessage += _assemblyOperation->GetMnemonic();
		errorMessage += " does not allow for any operands.";
		throw errorMessage.c_str();
	}

	returnValue += _assemblyOperation->GetOpCode();

	return returnValue;
}
