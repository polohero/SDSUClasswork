/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Format4SourceCodeInstruction is
 * used for instructions that the developer
 * has specified a + for the prefix operand.
 ******************************************/
#include <string>
#include <ctype.h>
#include "DataConverter.h"
#include "AssemblyOperation.h"
#include "SymbolTable.h"
#include "LiteralTable.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "Format4SourceCodeInstruction.h"

#define COMMA ','
#define PLUS '+'
#define HASH '#'
#define AMP '@'
#define X 'X'
#define EQUALS '='
#define STAR '*'

#define SIMPLE_ADDRESSING 1
#define INDIRECT_ADDRESSING 2
#define IMMEDIATE_ADDRESSING 3
#define INDEXED_ADDRESSING 4

#define FORMAT_4_LENGTH 4

using namespace std;

Format4SourceCodeInstruction::Format4SourceCodeInstruction(
			SourceCodeLine line,
			AssemblyOperation* assemblyOperation) : SourceCodeInstruction(line)
{
	_assemblyOperation = assemblyOperation;

	if( _assemblyOperation->GetMnemonic().compare(string("RSUB")) == 0 &&
	    line.GetOperand().length() > 0 )
	{
		throw "Format4SourceCodeInstruction: RSUB does not have an operand.";
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

int Format4SourceCodeInstruction::GetLength(){return FORMAT_4_LENGTH;}
string Format4SourceCodeInstruction::ToString()
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
string Format4SourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::FORMAT_4;}
ModificationRecords Format4SourceCodeInstruction::GetModificationRecords()
{
	ModificationRecords records;
	if( _createModificationRecords == true &&
		_addressingMode != IMMEDIATE_ADDRESSING )
	{
		ModificationRecord record = ModificationRecord(_location + 1, 5);
		records.Add(record);
	}

	return records;
}

string Format4SourceCodeInstruction::GetObjectCode()
{
	string returnValue;
	string errorMessage;
	int commaIndex = -1;

	if( _line.GetOperationPrefix().length() == 0 )
	{
		errorMessage = string("Extended format was not specified ");
		errorMessage += _line.GetOperation();
		throw errorMessage.c_str();
	}
	else if( _line.GetOperationPrefix().length() != 1 )
	{
		errorMessage = string("Prefix must be only 1 character. ");
		errorMessage += _line.GetOperation();
		throw errorMessage.c_str();
	}
	else if( _line.GetOperationPrefix()[0] != PLUS )
	{
		errorMessage = string("Extended format was not with a valid char ");
		errorMessage += _line.GetOperation();
		throw errorMessage.c_str();
	}

	string e = string("1");
	string b = string("0");
	string p = string("0");

	string n;
	string i;
	string x;

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

	if( true == xIndexed &&
	    _line.GetOperandPrefix().length() != 0)
	{
		throw "Invalid addressing mode.";
	}

	if( true == xIndexed )
	{
		x = string("1");
		n = string("1");
		i = string("1");
		_addressingMode = INDEXED_ADDRESSING;
	}
	else if (_line.GetOperandPrefix().length() == 1 &&
	         _line.GetOperandPrefix()[0] == AMP)
	{
		_addressingMode = INDIRECT_ADDRESSING;
		x = string("0");
		n = string("1");
		i = string("0");
	}
	else if (_line.GetOperandPrefix().length() == 1 &&
	         _line.GetOperandPrefix()[0] == HASH)
	{
		_addressingMode = IMMEDIATE_ADDRESSING;
		x = string("0");
		n = string("0");
		i = string("1");
	}
	else if( _line.GetOperandPrefix().length() == 0 )
	{
		_addressingMode = SIMPLE_ADDRESSING;
		x = string("0");
		n = string("1");
		i = string("1");
	}

	string opCode = _assemblyOperation->GetOpCode();
	opCode = DataConverter::GetBinaryStringFromHexString(opCode);

	opCode[6] = n[0];
	opCode[7] = i[0];

	string xbpe = x;
	xbpe += b;
	xbpe += p;
	xbpe += e;

	opCode += xbpe;

	returnValue = DataConverter::GetHexStringFromBinaryString(opCode);

	Symbol* symbol =
		SymbolTable::Get(operandWithoutIndexed);

	string binaryTargetAddress;
	bool isConstant = false;

	if( symbol == 0 )
	{
		int displacement;

		isConstant = true;
		// RSUB is special that it doesn't require
		// an operand.
		if( operandWithoutIndexed.length() == 0 &&
		    _assemblyOperation->GetMnemonic().compare(string("RSUB")) == 0 )
		{
			displacement = DataConverter::GetStringToInt(operandWithoutIndexed);
		}
		else if( operandWithoutIndexed[0] == EQUALS)
		{
			if( _line.GetOperand().length() > 1 &&
				_line.GetOperand()[1] == STAR)
			{
				displacement = GetNextLocation();
			}
			else
			{
				if( false == LiteralTable::IsLiteralInTable(operandWithoutIndexed) )
				{
					throw "Literal was not found";
				}

				Literal literal =
					LiteralTable::Get(operandWithoutIndexed);

				displacement = 	literal.GetLocation();
			}
		}
		else if(_addressingMode == IMMEDIATE_ADDRESSING)
		{
			for(int i = 0; i < operandWithoutIndexed.length(); i++)
			{
				if( false == isdigit(operandWithoutIndexed[i]) )
				{
					throw "Invalid operand, cannot have characters";
				}
			}
			displacement = DataConverter::GetStringToInt(operandWithoutIndexed);
		}
		else
		{
			string message = "Format4SourceCodeInstruction: Invalid operand ";
			message += operandWithoutIndexed;

			throw message.c_str();
		}

		binaryTargetAddress = DataConverter::ConvertIntToHex(displacement);

		binaryTargetAddress =
			DataConverter::PadLeft(
				DataConverter::GetBinaryStringFromHexString(binaryTargetAddress),
				20,
				'0');
	}
	else
	{
		if( symbol->GetSymbolType().compare(Symbol::REGISTER) == 0 )
		{
			throw "Format4SourceCodeInstruction: Cannot use a REGISTER symbol.";
		}

		int symbolAddress = symbol->GetAddress();

		  binaryTargetAddress =
			DataConverter::PadLeft(
				DataConverter::GetBinaryStringFromHexString(
					DataConverter::ConvertIntToHex(symbolAddress)),
				20,
				'0');

		if( symbol->GetSymbolType().compare(Symbol::EQU_R) == 0 )
		{
			_createModificationRecords = false;
		}
	}



	returnValue += DataConverter::GetHexStringFromBinaryString(binaryTargetAddress);

	return returnValue;
}
