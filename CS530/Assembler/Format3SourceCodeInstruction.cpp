/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Format3SourceCodeInstruction is
 * used for 3 byte instructions.
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
#include "Format3SourceCodeInstruction.h"
#include "LiteralSourceCodeInstruction.h"

#define COMMA ','
#define PLUS '+'
#define HASH '#'
#define AMP '@'
#define X 'X'
#define EQUALS '='

#define SIMPLE_ADDRESSING 1
#define INDIRECT_ADDRESSING 2
#define IMMEDIATE_ADDRESSING 3
#define INDEXED_ADDRESSING 4

#define PC_MAX 2047
#define PC_MIN -2048
#define BASE_MAX 4095
#define BASE_MIN 0
#define EQUALS '='
#define STAR '*'

#define FORMAT_3_LENGTH 3

using namespace std;

Format3SourceCodeInstruction::Format3SourceCodeInstruction(
			SourceCodeLine line,
			AssemblyOperation* assemblyOperation) : SourceCodeInstruction(line)
{
	_assemblyOperation = assemblyOperation;

	if( _assemblyOperation->GetMnemonic().compare(string("RSUB")) == 0 &&
	    line.GetOperand().length() > 0 )
	{
		throw "Format3SourceCodeInstruction: RSUB does not have an operand.";
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
}

int Format3SourceCodeInstruction::GetLength(){return FORMAT_3_LENGTH;}
string Format3SourceCodeInstruction::ToString()
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
string Format3SourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::FORMAT_3;}
ModificationRecords Format3SourceCodeInstruction::GetModificationRecords()
{
	ModificationRecords records;

	return records;
}

string Format3SourceCodeInstruction::GetObjectCode()
{
	string returnValue;
	string errorMessage;
	int commaIndex = -1;

	if( _line.GetOperationPrefix()[0] == PLUS )
	{
		errorMessage = string("Extended format was not with a valid operation ");
		errorMessage += _line.GetOperation();
		throw errorMessage.c_str();
	}

	string e = string("0");
	string b;
	string p;
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
		throw "Format3SourceCodeInstruction: Invalid addressing mode.";
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

	int displacement;

	int displacementPC;
	int displacementBase;

	bool isConstant = false;

	Symbol* symbol =
		SymbolTable::Get(operandWithoutIndexed);

	if(  symbol != 0 )
	{
		int symbolAddress = symbol->GetAddress();

		if( symbol->GetSymbolType().compare(Symbol::REGISTER) == 0 )
		{
			throw "Format3SourceCodeInstruction: Cannot use a REGISTER symbol.";
		}

	 	displacementPC = symbolAddress - GetNextLocation();
	 	displacementBase = symbolAddress - SourceCodeInstruction::BASE_VALUE;
	}
	else
	{
		// RSUB is special that the operand can be blank.
		if( operandWithoutIndexed.length() == 0 &&
			_assemblyOperation->GetMnemonic().compare(string("RSUB")) == 0 )
		{
			isConstant = true;
			displacement = DataConverter::GetStringToInt(operandWithoutIndexed);
		}
		else if( operandWithoutIndexed[0] == EQUALS)
		{
			if( _line.GetOperand().length() > 1 &&
				_line.GetOperand()[1] == STAR)
			{
				displacement = GetNextLocation();

				displacementPC = displacement - GetNextLocation();
				displacementBase = displacement - SourceCodeInstruction::BASE_VALUE;
			}
			else
			{
				if( false == LiteralTable::IsLiteralInTable(operandWithoutIndexed) )
				{
					throw "Format3SourceCodeInstruction: Literal was not found";
				}
				isConstant = false;
				Literal literal =
					LiteralTable::Get(operandWithoutIndexed);

				displacement = literal.GetLocation();

				displacementPC = displacement - GetNextLocation();
				displacementBase = displacement - SourceCodeInstruction::BASE_VALUE;
			}
		}
		else if(_addressingMode == IMMEDIATE_ADDRESSING)
		{
			isConstant = true;
			for(int i = 0; i < operandWithoutIndexed.length(); i++)
			{
				if( false == isdigit(operandWithoutIndexed[i]) )
				{
					throw "Format3SourceCodeInstruction: Invalid operand, cannot have characters";
				}
			}
			displacement = DataConverter::GetStringToInt(operandWithoutIndexed);
		}
		else
		{
			string message = "Format3SourceCodeInstruction: Invalid operand ";
			message += operandWithoutIndexed;

			throw message.c_str();
		}
	}


	if( isConstant == false &&
		displacementPC >= PC_MIN &&
	    displacementPC <= PC_MAX)
	{
		p = string("1");
		b = string("0");
		displacement = displacementPC;
	}
	else if( isConstant == false &&
			 displacementBase >= BASE_MIN &&
	         displacementBase <= BASE_MAX)
	{
		p = string("0");
		b = string("1");
		displacement = displacementBase;
	}
	else if( isConstant == true )
	{
		p = string("0");
		b = string("0");
	}
	else
	{
		throw "Format3SourceCodeInstruction: Instruction cannot be created because it's outside the range.";
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

	string binaryTargetAddress;

	if( displacement < 0 )
	{
		string hex = DataConverter::ConvertIntToHex(displacement);
		string binary = DataConverter::GetBinaryStringFromHexString(hex);

		binaryTargetAddress = DataConverter::PadLeft(binary, 12, '0');

		binaryTargetAddress =
			binaryTargetAddress.substr(
				binaryTargetAddress.length() - 12,
				12);
	}
	else
	{
		binaryTargetAddress =
			DataConverter::PadLeft(
				DataConverter::GetBinaryStringFromHexString(
					DataConverter::ConvertIntToHex(displacement)),
				12,
				'0');

	}

	returnValue += DataConverter::GetHexStringFromBinaryString(binaryTargetAddress);

	return returnValue;
}
