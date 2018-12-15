/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The EquSourceCodeInstruction is
 * used for equating variables.
 ******************************************/
#include <string>
#include <ctype.h>
#include "DataConverter.h"
#include "SymbolTable.h"
#include "LiteralTable.h"
#include "SourceCodeLine.h"
#include "SourceCodeInstruction.h"
#include "ModificationRecords.h"
#include "EquSourceCodeInstruction.h"

#define COMMA ','
#define PLUS '+'
#define MINUS '-'
#define HASH '#'
#define AMP '@'
#define X 'X'
#define STAR '*'
#define EQUALS '='

using namespace std;

EquSourceCodeInstruction::EquSourceCodeInstruction(
			SourceCodeLine line,
			int currentLocation) : SourceCodeInstruction(line)
{
	string currentValue;
	bool isAllDigits = true;
	bool started = false;
	bool isRelative = false;

	bool openSubtraction = false;
	bool openAddition = false;

	for(int i = 0; i < line.GetOperand().length(); i++)
	{
		if( line.GetOperand()[i] == STAR )
		{
			currentValue = DataConverter::GetIntToString(currentLocation);
		}
		else if( line.GetOperand()[i] == MINUS )
		{
			Symbol* symbol =
				SymbolTable::Get(currentValue);

			if( symbol != 0 )
			{
				if( false == started )
				{
					_address = symbol->GetAddress();
					isRelative = true;
					openSubtraction = true;
				}
				else
				{
					_address = _address - symbol->GetAddress();
					openSubtraction = false;
					isRelative = true;
				}
			}
			else if( isAllDigits == true )
			{
				if( false == started )
				{
					throw "EQU: Subtraction from a constant doesn't make sense.";
				}
				else
				{
					_address -= DataConverter::GetStringToInt(currentValue);
					openSubtraction = false;
				}
			}
			else
			{
				string errorMessage = "Unable to parse operand: ";
				errorMessage += line.GetOperand();

				throw errorMessage.c_str();
			}

			currentValue = string("");
			started = true;
		}
		else if( line.GetOperand()[i] == PLUS )
		{
			Symbol* symbol =
				SymbolTable::Get(currentValue);

			if( symbol != 0 )
			{
				throw "EQU: Addtion of a symbol doesn't make sense.";
			}
			else if( isAllDigits == true )
			{
				if( false == started )
				{
					_address = DataConverter::GetStringToInt(currentValue);
					isRelative = false;
					openAddition = true;
				}
				else
				{
					_address += DataConverter::GetStringToInt(currentValue);
					openAddition = false;
				}
			}
			else
			{
				string errorMessage = "Unable to parse operand: ";
				errorMessage += line.GetOperand();

				throw errorMessage.c_str();
			}

			currentValue = string("");
			started = true;
		}
		else
		{
			if( false == isdigit(line.GetOperand()[i]) )
			{
				isAllDigits = false;
			}

			currentValue += line.GetOperand()[i];
		}
	}

	if( false == started )
	{
		Symbol* symbol =
				SymbolTable::Get(currentValue);

		if( symbol != 0 )
		{
			_address = symbol->GetAddress();
		}
		else if( isAllDigits == true )
		{
			_address = DataConverter::GetStringToInt(currentValue);
		}
		else
		{
			string errorMessage = "Unable to parse operand: ";
			errorMessage += line.GetOperand();

			throw errorMessage.c_str();
		}
	}

	if( openSubtraction == true )
	{
		Symbol* symbol =
				SymbolTable::Get(currentValue);

		if( symbol == 0 )
		{
			_address -= DataConverter::GetStringToInt(currentValue);
		}
		else
		{
			_address -= symbol->GetAddress();
			isRelative = true;
		}
	}
	else if( openAddition == true )
	{
		Symbol* symbol =
				SymbolTable::Get(currentValue);

		if( symbol == 0 )
		{
			_address += DataConverter::GetStringToInt(currentValue);
		}
		else
		{
			throw "EQU: Addtion of a symbol doesn't make sense.";
		}
	}

	Symbol symbol =
		Symbol(line.GetLabel(), _address, Symbol::EQU_A);

	if( true == isRelative )
	{
		symbol =
			Symbol(line.GetLabel(), _address, Symbol::EQU_R);
	}

	SymbolTable::Insert(symbol);
}

int EquSourceCodeInstruction::GetLength(){return 0;}
string EquSourceCodeInstruction::ToString()
{
	return GetInstructionType() +
		   string(":") +
		    GetSourceCodeLine().GetLabel() +
		    " " +
		    GetSourceCodeLine().GetOperationPrefix() +
		    GetSourceCodeLine().GetOperation() +
		   " " +
		    GetSourceCodeLine().GetOperandPrefix() +
		    GetSourceCodeLine().GetOperand();
}
string EquSourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::EQU;}
ModificationRecords EquSourceCodeInstruction::GetModificationRecords()
{
	ModificationRecords records;

	return records;
}

string EquSourceCodeInstruction::GetObjectCode()
{
	return string("");
}
