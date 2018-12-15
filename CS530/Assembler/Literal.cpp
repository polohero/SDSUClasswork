/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Literal is an
 * instruction to tell the assembler
 * about a specific literal.
 ******************************************/
#include <string>
#include "DataConverter.h"
#include "SourceCodeLine.h"
#include "SourceCodeInstruction.h"
#include "Literal.h"

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

const int Literal::HEX = 1;
const int Literal::CHAR = 2;
const int Literal::INT = 3;


Literal::Literal(
	SourceCodeLine line)
{
	_line = line;

	// First validate the line.
	if( _line.GetOperand().length() < MIN_LENGTH)
	{
		throw "Literal: Operand is not a valid length.";
	}

	if( _line.GetOperand()[0] != EQUAL )
	{
		throw "Literal: Operand does not start with =.";
	}

	if( _line.GetOperand()[1] == HEX_)
	{
		_literalType = Literal::HEX;
		if( _line.GetOperand().length() < CHAR_HEX_MIN_LENGTH)
		{
			throw "Literal: Operand is not a valid length.";
		}

		if( _line.GetOperand()[2] != SINGLE_QUOTE)
		{
			throw "Literal: Operand does not start with '.";
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
			throw "Literal: Operand is not a valid length.";
		}

		if( _line.GetOperand()[2] != SINGLE_QUOTE)
		{
			throw "Literal: Operand does not start with '.";
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
				throw "Literal: Must be an integer value.";
			}
		}
		_integer = DataConverter::GetStringToInt(integers);
	}

	_literalString = _line.GetOperand();
	//_line.SetLabel("*");
	_hasBeenPooled = false;
}

int Literal::GetLocation(){return _location;}
void Literal::SetLocation(int location){_location = location;}
SourceCodeLine Literal::GetSourceCodeLine()
{
	return _line;
}

int Literal::GetLength()
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

string Literal::ToString(){return GetInstructionType() + string(":") + _literalString;}
string Literal::GetInstructionType(){return SourceCodeInstruction::LITERAL;}
string Literal::GetObjectCode()
{
	string returnValue;

	if( _literalType == Literal::CHAR )
	{
		for(int i = 0; i < _characters.length(); i++)
		{
			int charInt = (int)_characters[i];
			string charStr = DataConverter::PadLeft(DataConverter::ConvertIntToHex(charInt), 2, '0');
			returnValue+= charStr;
		}
	}
	else if( _literalType == Literal::HEX )
	{
		return _hexCharacters;
	}
	else
	{
		return DataConverter::PadLeft(DataConverter::ConvertIntToHex(_integer), 6, '0');
	}

	return returnValue;
}
bool Literal::HasBeenPooled(){return _hasBeenPooled;}
void Literal::SetHasBeenPooled(bool hasBeenPooled){_hasBeenPooled = hasBeenPooled;}
int Literal::GetLiteralType(){return _literalType;}
string Literal::GetLiteralString(){return _literalString;}

