/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Format0SourceCodeInstruction is
 * a SIC BASIC instruction. It is a single
 * instruction, and will handle creating
 * the object code for this line of source
 * code.
 ******************************************/
#include <string>
#include "DataConverter.h"
#include "AssemblyOperation.h"
#include "SymbolTable.h"
#include "LiteralTable.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "Format0SourceCodeInstruction.h"

#define COMMA ','
#define X 'X'
#define FORMAT_0_LENGTH 3
#define EQUALS '='
#define STAR '*'

using namespace std;

Format0SourceCodeInstruction::Format0SourceCodeInstruction(
			SourceCodeLine line,
			AssemblyOperation* assemblyOperation) : SourceCodeInstruction(line)
{
	_assemblyOperation = assemblyOperation;

	if( _assemblyOperation->GetMnemonic().compare(string("RSUB")) == 0 &&
	    line.GetOperand().length() > 0 )
	{
		throw "Format0SourceCodeInstruction: RSUB does not have an operand.";
	}

	if( line.GetOperand().length() > 0 &&
		    line.GetOperand()[0] == EQUALS)
	{
		if( line.GetOperand().length() > 1 &&
		    line.GetOperand()[1] != STAR)
		{
			Literal literal =
				Literal(line);

			LiteralTable::Insert(literal);
		}
	}

	_createModificationRecords = true;
}

int Format0SourceCodeInstruction::GetLength(){return FORMAT_0_LENGTH;}
string Format0SourceCodeInstruction::ToString()
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
string Format0SourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::FORMAT_0;}
ModificationRecords Format0SourceCodeInstruction::GetModificationRecords()
{
	ModificationRecords records;

	if( true == _createModificationRecords )
	{
		ModificationRecord record = ModificationRecord(_location + 1, 4);
		records.Add(record);
	}

	return records;
}

string Format0SourceCodeInstruction::GetObjectCode()
{
	string returnValue;

	returnValue += _assemblyOperation->GetOpCode();

	int commaIndex = -1;

	bool xIndexed = false;

	for(int i = 0; i < _line.GetOperand().length(); i++)
	{
		if( _line.GetOperand()[i] == COMMA )
		{
			commaIndex = i;
		}

		if( -1 != commaIndex &&
		    _line.GetOperand()[i] == X )
		{
			xIndexed = true;
			break;
		}
	}

	string operandWithoutIndexed = _line.GetOperand();

	if( true == xIndexed )
	{
		operandWithoutIndexed = _line.GetOperand().substr(0, commaIndex);
	}

	Symbol* symbol =
		SymbolTable::Get(operandWithoutIndexed);

	int symbolAddress;

	if(0 == symbol)
	{
		// RSUB is special in that it doesn't
		// require an operand.
		if( operandWithoutIndexed.length() == 0 &&
		    _assemblyOperation->GetMnemonic().compare(string("RSUB")) == 0 )
		{
			symbolAddress = 0;
		}
		else if( operandWithoutIndexed[0] == EQUALS)
		{
			if( _line.GetOperand().length() > 1 &&
				_line.GetOperand()[1] == STAR)
			{
				symbolAddress = GetNextLocation();
			}
			else
			{
				if( false == LiteralTable::IsLiteralInTable(operandWithoutIndexed) )
				{
					throw "Format0SourceCodeInstruction: Literal was not found";
				}
				Literal literal =
					LiteralTable::Get(operandWithoutIndexed);

				symbolAddress = literal.GetLocation();
			}
		}
		else if( operandWithoutIndexed.length() > 0 )
		{
			string errorMsg = string("Invalid symbol ");
			errorMsg += operandWithoutIndexed;
			errorMsg += string(" symbol not found.");
			throw errorMsg.c_str();
		}
	}
	else
	{
		if( symbol->GetSymbolType().compare(Symbol::REGISTER) == 0 )
		{
			throw "Format0SourceCodeInstruction: Cannot use a REGISTER symbol.";
		}

		symbolAddress = symbol->GetAddress();

		if( symbol->GetSymbolType().compare(Symbol::EQU_R) == 0 )
		{
			_createModificationRecords = false;
		}
	}

	string binaryTargetAddress =
		DataConverter::PadLeft(
			DataConverter::GetBinaryStringFromHexString(
				DataConverter::ConvertIntToHex(symbolAddress)),
			16,
			'0');

	if( true == xIndexed )
	{
		binaryTargetAddress[0] = '1';
	}

	returnValue += DataConverter::GetHexStringFromBinaryString(binaryTargetAddress);

	return returnValue;
}
