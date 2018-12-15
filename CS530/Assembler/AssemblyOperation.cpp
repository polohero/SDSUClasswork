/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The AssemblyOperation class contains all the
 * information for a specific assembly command.
 ******************************************/
#include "AssemblyOperation.h"

#include <string>
#include <iostream>

using namespace std;

AssemblyOperation::AssemblyOperation(
	string opcode,
	string mnemonic,
	string format,
	string effect,
	string notes,
	string example)
{
	_opcode = opcode;
	_mnemonic = mnemonic;
	_format = format;
	_effect = effect;
	_notes = notes;
	_example = example;
}


const string AssemblyOperation::FORMAT_0 = "0";
const string AssemblyOperation::FORMAT_1 = "1";
const string AssemblyOperation::FORMAT_2 = "2";
const string AssemblyOperation::FORMAT_3 = "3";
const string AssemblyOperation::FORMAT_4 = "4";

int AssemblyOperation::NumberOfFormatsPossible(){return _format.length();}
string AssemblyOperation::GetOpCode(){return _opcode;}
string AssemblyOperation::GetMnemonic(){return _mnemonic;}
string AssemblyOperation::GetFormat(){return _format;}
string AssemblyOperation::GetEffect(){return _effect;}
string AssemblyOperation::GetNotes(){return _notes;}
string AssemblyOperation::GetExample(){return _example;}

bool AssemblyOperation::operator ==(AssemblyOperation other)
{
	return GetMnemonic().compare(other.GetMnemonic()) == 0;
}

bool AssemblyOperation::Compare(AssemblyOperation other)
{
	return GetMnemonic().compare(other.GetMnemonic()) == 0;
}

/******************************************************
UNIT TESTS
******************************************************/
/*
int main()
{
	string currentTest;

	AssemblyOperation operation =
		AssemblyOperation(1,"LDA","034","A <-- (m..m+2)","","LDA m");

	currentTest = string("GetOpCode");
	if(operation.GetOpCode() == 1)
	{
		cout << currentTest << " PASSED" << endl;
	}
	else
	{
		cout << currentTest << " FAILED" << endl;
	}

	currentTest = string("GetMnemonic");
	if(operation.GetMnemonic().compare("LDA") == 0)
	{
		cout << currentTest << " PASSED" << endl;
	}
	else
	{
		cout << currentTest << " FAILED" << endl;
	}

	currentTest = string("GetFormat");
	if(operation.GetFormat().compare("034") == 0)
	{
		cout << currentTest << " PASSED" << endl;
	}
	else
	{
		cout << currentTest << " FAILED" << endl;
	}

	currentTest = string("GetEffect");
	if(operation.GetEffect().compare("A <-- (m..m+2)") == 0)
	{
		cout << currentTest << " PASSED" << endl;
	}
	else
	{
		cout << currentTest << " FAILED" << endl;
	}

	currentTest = string("GetNotes");
	if(operation.GetNotes().compare("") == 0)
	{
		cout << currentTest << " PASSED" << endl;
	}
	else
	{
		cout << currentTest << " FAILED" << endl;
	}

	currentTest = string("GetExample");
	if(operation.GetExample().compare("LDA m") == 0)
	{
		cout << currentTest << " PASSED" << endl;
	}
	else
	{
		cout << currentTest << " FAILED" << endl;
	}

	currentTest = string("operation == operation2");
	AssemblyOperation operation2 =
		AssemblyOperation(1,"LDA","034","A <-- (m..m+2)","","LDA m");

	if(operation == operation2)
	{
		cout << currentTest << " PASSED" << endl;
	}
	else
	{
		cout << currentTest << " FAILED" << endl;
	}

	currentTest = string("operation != operation2");
	AssemblyOperation operation3 =
		AssemblyOperation(1,"AAAA","034","A <-- (m..m+2)","","LDA m");

	if(operation == operation3)
	{
		cout << currentTest << " FAILED" << endl;
	}
	else
	{
		cout << currentTest << " PASSED" << endl;
	}

	return 0;
}
*/

