/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Format2SourceCodeInstruction is
 * a SIC BASIC instruction. It is a single
 * instruction, and will handle creating
 * the object code for this line of source
 * code.
 ******************************************/
#include <string>
#include <ctype.h>
#include "DataConverter.h"
#include "AssemblyOperation.h"
#include "SymbolTable.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "Format2SourceCodeInstruction.h"

#define COMMA ','

#define FORMAT_2_LENGTH 2

using namespace std;

Format2SourceCodeInstruction::Format2SourceCodeInstruction(
			SourceCodeLine line,
			AssemblyOperation* assemblyOperation) : SourceCodeInstruction(line)
{
	_assemblyOperation = assemblyOperation;

}

int Format2SourceCodeInstruction::GetLength(){return FORMAT_2_LENGTH;}
string Format2SourceCodeInstruction::ToString()
{
	return GetInstructionType() +
		   string(":") +
		    GetSourceCodeLine().GetLabel() +
		    " " +
		    GetSourceCodeLine().GetOperationPrefix() +
		   _assemblyOperation->GetMnemonic() +
		   " " +
		    GetSourceCodeLine().GetOperandPrefix() +
		    GetSourceCodeLine().GetOperand();
}
string Format2SourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::FORMAT_2;}
ModificationRecords Format2SourceCodeInstruction::GetModificationRecords()
{
	ModificationRecords records;

	return records;
}

string Format2SourceCodeInstruction::GetObjectCode()
{
	string empty = string("");
	string errorMessage;
	string returnValue;

	string operand1;
	string operand2;
	int operand1Address;
	int operand2Address;

	bool hasCommaArrived = false;

	for(int i = 0; i < _line.GetOperand().length(); i++)
	{
		if( _line.GetOperand()[i] == COMMA)
		{
			hasCommaArrived = true;
			continue;
		}

		if( false == hasCommaArrived )
		{
			operand1 += _line.GetOperand()[i];
		}
		else
		{
			operand2 += _line.GetOperand()[i];
		}
	}

	Symbol* operandOneSymbol =
		SymbolTable::Get(operand1);

	if( 0 == operandOneSymbol )
	{
		errorMessage = string("Invalid symbol ");
		errorMessage += operand1;
		errorMessage += string(" symbol not found.");
		throw errorMessage.c_str();
	}

	if( operandOneSymbol->GetSymbolType().compare(Symbol::REGISTER) != 0 )
	{
		throw "Format2SourceCodeInstruction: MUST use a REGISTER symbol.";
	}

	operand1Address = operandOneSymbol->GetAddress();

	Symbol* operandTwoSymbol =
		SymbolTable::Get(operand2);

	if( operand2.compare(empty) == 0 )
	{
		// Special operations that allow
		// for one 1 operand.
		if( _assemblyOperation->GetMnemonic().compare(string("SVC")) == 0 ||
		    _assemblyOperation->GetMnemonic().compare(string("CLEAR")) == 0 ||
		    _assemblyOperation->GetMnemonic().compare(string("TIXR")) == 0 )
		{
			operand2Address = 0;
		}
		else
		{
			throw "Format2SourceCodeInstruction: Second operand must be blank.";
		}
	}
	else if( 0 == operandTwoSymbol )
	{
		// Special operations that allow an integer for
		// the second operand.
		if( _assemblyOperation->GetMnemonic().compare(string("SHIFTL")) == 0 ||
		    _assemblyOperation->GetMnemonic().compare(string("SHIFTR")) == 0 )
		{
			for(int i = 0; i < operand2.length(); i++)
			{
				if( false == isdigit(operand2[i] ))
				{
					errorMessage = string("Second operand must be a number: ");
					errorMessage += operand2;
					throw errorMessage.c_str();
				}
			}

			operand2Address =
				DataConverter::GetStringToInt(operand2);
		}
		else
		{
			throw "Format2SourceCodeInstruction: Second operand is incorrect.";
		}
	}
	else
	{
		if( _assemblyOperation->GetMnemonic().compare(string("SHIFTL")) == 0 ||
		    _assemblyOperation->GetMnemonic().compare(string("SHIFTR")) == 0 ||
		    _assemblyOperation->GetMnemonic().compare(string("SVC")) == 0 ||
		    _assemblyOperation->GetMnemonic().compare(string("CLEAR")) == 0 ||
		    _assemblyOperation->GetMnemonic().compare(string("TIXR")) == 0 )
		{
			throw "Format2SourceCodeInstruction: Second operand is invalid for operation.";
		}

		if( operandTwoSymbol->GetSymbolType().compare(Symbol::REGISTER) != 0 )
		{
			throw "Format2SourceCodeInstruction: MUST use a REGISTER symbol.";
		}
		operand2Address =
			operandTwoSymbol->GetAddress();
	}

	returnValue += _assemblyOperation->GetOpCode();
	returnValue +=
		DataConverter::PadLeft(
			DataConverter::ConvertIntToHex(operand1Address),
			1,
			'0');
	returnValue +=
		DataConverter::PadLeft(
			DataConverter::ConvertIntToHex(operand2Address),
			1,
			'0');

	return returnValue;
}
