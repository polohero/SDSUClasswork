/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SourceCodeLine is in charge of
 * parsing a single line of code into
 * it's different parts.
 ******************************************/
#include <string>
#include <iostream>

#include "DataConverter.h"
#include "SourceCodeLine.h"

#define EQUALS '='
#define ZERO_LENGTH 0
#define MIN_LENGTH 35
#define LABEL_START 0
#define LABEL_LENGTH 7
#define OPERATION_PREFIX_START 8
#define OPERATION_PREFIX_LENGTH 1
#define OPERATION_START 9
#define OPERATION_LENGTH 6

#define OPERAND_PREFIX_START 16
#define OPERAND_PREFIX_LENGTH 1
#define OPERAND_START 17
#define OPERAND_LENGTH 18

#define TAB '\t'
#define NEWLINE '\n'
#define CARRIAGE_RETURN '\r'
#define SPACE ' '

using namespace std;

SourceCodeLine::SourceCodeLine(
	string rawLine)
{
	validate(rawLine);
	parse(rawLine);
}

const char SourceCodeLine::COMMENT_CHARACTER = '.';

string SourceCodeLine::GetRawLine(){return _rawLine;}
string SourceCodeLine::GetLabel(){return _label;}
void SourceCodeLine::SetLabel(string label){_label = label;}
string SourceCodeLine::GetOperationPrefix(){return _operationPrefix;}
string SourceCodeLine::GetOperation(){return _operation;}
string SourceCodeLine::GetOperandPrefix(){return _operandPrefix;}
string SourceCodeLine::GetOperand(){return _operand;}
bool SourceCodeLine::IsCommentLine(){return _isCommentLine;}
bool SourceCodeLine::HasLiteral()
{
	if( GetOperand().length() == 0 )
	{
		return false;
	}
	else if( GetOperand()[0] == EQUALS )
	{
		return true;
	}
	else
	{
		return false;
	}
}

int SourceCodeLine::GetLocation(){return _location;}
void SourceCodeLine::SetLocation(int location){ _location = location;}
int SourceCodeLine::GetLength(){return _length;}
void SourceCodeLine::SetLength(int length){ _length = length;}

void SourceCodeLine::parse(string rawLine)
{
	_rawLine = rawLine;
	_isCommentLine = isCommentLine(rawLine);

	// If it's a comment. Then there is
	// no need to parse anything else.
	if( true == _isCommentLine)
	{
		_rawLine = rawLine;
		_label = "";
		_operation = "";
		_operationPrefix = "";
		_operandPrefix = "";
		_operand = "";
		return;
	}

	// Otherwise, go through and
	// find each of the different
	// pieces of the source line.
	_label =
		DataConverter::Trim(
			rawLine.substr(LABEL_START, LABEL_LENGTH));

	hasInvalidCharacters(_label, string("Label"));

	_operationPrefix =
		DataConverter::Trim(
			rawLine.substr(
				OPERATION_PREFIX_START,
				OPERATION_PREFIX_LENGTH));

	_operation =
		DataConverter::Trim(
			rawLine.substr(
				OPERATION_START,
				OPERATION_LENGTH));

	hasInvalidCharacters(_operation, string("Operation"));

	_operandPrefix =
		DataConverter::Trim(
			rawLine.substr(
				OPERAND_PREFIX_START,
				OPERAND_PREFIX_LENGTH));

	_operand = getOperand(rawLine);
}

string SourceCodeLine::getOperand(string rawLine)
{
	string operandReturn;
	string operandStart =
		DataConverter::Trim(
			rawLine.substr(
				OPERAND_START,
				OPERAND_LENGTH));

	for(int i = 0; i < operandStart.length(); i++)
	{
		if( operandStart[i] == COMMENT_CHARACTER)
		{
			break;
		}

		operandReturn+=operandStart[i];
	}

	return operandReturn;
}

void SourceCodeLine::hasInvalidCharacters(
	string data,
	string message)
{
	string errorMessage;

	for(int i = 0; i < data.length(); i++)
	{
		if( data[i] == COMMENT_CHARACTER )
		{
			cout << data << endl;
			cout << data[0] << endl;
			cout << (int)data[0] << endl;
			errorMessage += message;
			errorMessage += string(". ");
			errorMessage += string("Contains a comma, which is not valid.");
			throw errorMessage.c_str();
		}
	}
}



bool SourceCodeLine::isCommentLine(string rawLine)
{
	if( ZERO_LENGTH == rawLine.length() )
	{
		return true;
	}

	if( rawLine[ZERO_LENGTH] == SourceCodeLine::COMMENT_CHARACTER )
	{
		return true;
	}

	return false;
}

void SourceCodeLine::validate(string rawLine)
{
	// First check if this is a comment line.
	// If it is, there is no validation that needs
	// to be done.
	bool isComment = isCommentLine(rawLine);

	if( true == isComment)
	{
		return;
	}

	// Otherwise this is some sort of
	// source code line. Perform the rest
	// of the validations.
	if( ZERO_LENGTH == rawLine.length() )
	{
		throw "Line cannot be empty. Cannot parse.";
	}

	if( rawLine.length() < MIN_LENGTH )
	{
		throw "Line is too short. Cannot parse.";
	}
}

/*****************************************
UNIT TESTS
g++ SourceCodeLine.cpp DataConverter.cpp
*****************************************/
/*
int main()
{
	string currentTest;

	try
	{

		SourceCodeLine line =
			SourceCodeLine(
				"RLOOP   +TD     #INPUT             TEST INPUT DEVICE");

		currentTest = "START GetLabel";
		if(line.GetLabel().compare("RLOOP") == 0)
		{
			cout << currentTest << " PASSED" << endl;
		}
		else
		{
			cout << currentTest << " FAILED" << endl;
		}

		currentTest = "START GetOperationPrefix";
		if(line.GetOperationPrefix().compare("+") == 0)
		{
			cout << currentTest << " PASSED" << endl;
		}
		else
		{
			cout << currentTest << " FAILED" << endl;
		}

		currentTest = "START GetOperation";
		if(line.GetOperation().compare("TD") == 0)
		{
			cout << currentTest << " PASSED" << endl;
		}
		else
		{
			cout << currentTest << " FAILED" << endl;
		}

		currentTest = "START GetOperandPrefix";
		if(line.GetOperandPrefix().compare("#") == 0)
		{
			cout << currentTest << " PASSED" << endl;
		}
		else
		{
			cout << currentTest << " FAILED" << endl;
		}

		currentTest = "START GetOperand";
		if(line.GetOperand().compare("INPUT") == 0)
		{
			cout << currentTest << " PASSED" << endl;
		}
		else
		{
			cout << currentTest << " FAILED" << endl;
		}

		cout << "GetRawLine: " << line.GetRawLine() << endl;
		cout << "GetLabel: " << line.GetLabel() << endl;
		cout << "GetOperationPrefix: " << line.GetOperationPrefix() << endl;
		cout << "GetOperation: " << line.GetOperation() << endl;
		cout << "GetOperandPrefix: " << line.GetOperandPrefix() << endl;
		cout << "GetOperand: " << line.GetOperand() << endl;


	}
	catch(char const* exception)
	{
		cerr << "Exception: " << exception << endl;
		return 1;
	}

}
*/
