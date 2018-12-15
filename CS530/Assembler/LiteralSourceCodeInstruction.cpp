/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SourceCodeInstruction is an
 * instruction to tell the assembler
 * about a specific literal.
 ******************************************/
#include <string>
#include "Literal.h"
#include "DataConverter.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "LiteralSourceCodeInstruction.h"

#define SPACE ' '
#define CHAR_ 'C'
#define HEX_ 'X'
#define INT_ 'X'
#define EQUAL '='
#define SINGLE_QUOTE '\''
#define MIN_LENGTH 1
#define CHAR_HEX_MIN_LENGTH 4
#define SIC_INT_LENGTH 3

using namespace std;

LiteralSourceCodeInstruction::LiteralSourceCodeInstruction(
	SourceCodeLine line,
	Literal literal) : SourceCodeInstruction(line)
{
	_literal = literal;

	// First validate the line.
	if( _line.GetOperand().length() < MIN_LENGTH)
	{
		throw "LiteralSourceCodeInstruction: Operand is not a valid length.";
	}

	if( _line.GetOperand()[0] != EQUAL )
	{
		throw "LiteralSourceCodeInstruction: Operand does not start with =.";
	}


	if( _line.GetOperand()[1] == HEX_)
	{
		_literalType = Literal::HEX;
		if( _line.GetOperand().length() < CHAR_HEX_MIN_LENGTH)
		{
			throw "LiteralSourceCodeInstruction: Operand is not a valid length.";
		}

		if( _line.GetOperand()[2] != SINGLE_QUOTE)
		{
			throw "LiteralSourceCodeInstruction: Operand does not start with '.";
		}
		bool foundClosingQuote = false;

		for(int i = 3; i < _line.GetOperand().length(); i++)
		{
			if( _line.GetOperand()[i] == SINGLE_QUOTE)
			{
				foundClosingQuote = true;
				break;
			}

			_hexCharacters += _line.GetOperand()[i];
		}

		if( foundClosingQuote == false )
		{
			throw "Invalid Byte character defined. No closing single quotes found.";
		}
	}
	else if( _line.GetOperand()[1] == CHAR_ )
	{
		_literalType = Literal::CHAR;

		if( _line.GetOperand().length() < CHAR_HEX_MIN_LENGTH)
		{
			throw "LiteralSourceCodeInstruction: Operand is not a valid length.";
		}


		if( _line.GetOperand()[2] != SINGLE_QUOTE)
		{
			throw "LiteralSourceCodeInstruction: Operand does not start with '.";
		}


		bool foundClosingQuote = false;

		for(int i = 3; i < _line.GetOperand().length(); i++)
		{
			if( _line.GetOperand()[i] == SINGLE_QUOTE)
			{
				foundClosingQuote = true;
				break;
			}

			_characters += _line.GetOperand()[i];
		}

		if( foundClosingQuote == false )
		{
			throw "Invalid Byte character defined. No closing single quotes found.";
		}
	}
	else
	{
		_literalType = Literal::INT;
		string integers;

		for(int i = 1; i < _line.GetOperand().length(); i++)
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
				throw "LiteralSourceCodeInstruction: Must be an integer value.";
			}
		}
		_integer = DataConverter::GetStringToInt(integers);
	}
}

int LiteralSourceCodeInstruction::GetLength()
{
	if( _literalType == Literal::CHAR )
	{
		return _characters.length();
	}
	else if( _literalType == Literal::HEX )
	{
		return _hexCharacters.length() / 2;
	}
	else
	{
		return SIC_INT_LENGTH;
	}
}

string LiteralSourceCodeInstruction::ToString(){return GetInstructionType();}
string LiteralSourceCodeInstruction::GetInstructionType(){return SourceCodeInstruction::LITERAL;}
string LiteralSourceCodeInstruction::GetObjectCode()
{
	return _literal.GetObjectCode();
}
ModificationRecords LiteralSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}

