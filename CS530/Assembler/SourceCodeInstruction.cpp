/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SourceCodeInstruction is a base class.
 * All other instructions inherit from this
 * class. Each specific class contains
 * the logic to create the object code.
 * Methods have been stubbed out, but will not
 * be used.
 ******************************************/
#include <string>
#include <iostream>

#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"

using namespace std;

const int SourceCodeInstruction::SIC_BASIC = 1;
const int SourceCodeInstruction::SIC_XE = 2;

const string SourceCodeInstruction::NONE = string("NONE");
const string SourceCodeInstruction::BYTE = string("BYTE");
const string SourceCodeInstruction::BASE = string("BASE");
const string SourceCodeInstruction::NOBASE = string("NOBASE");
const string SourceCodeInstruction::WORD = string("WORD");
const string SourceCodeInstruction::EQU = string("EQU");
const string SourceCodeInstruction::START = string("START");
const string SourceCodeInstruction::END = string("END");
const string SourceCodeInstruction::RESB = string("RESB");
const string SourceCodeInstruction::RESW = string("RESW");
const string SourceCodeInstruction::FORMAT_0 = string("FORMAT_0");
const string SourceCodeInstruction::FORMAT_1 = string("FORMAT_1");
const string SourceCodeInstruction::FORMAT_2 = string("FORMAT_2");
const string SourceCodeInstruction::FORMAT_3 = string("FORMAT_3");
const string SourceCodeInstruction::FORMAT_4 = string("FORMAT_4");
const string SourceCodeInstruction::COMMENT = string("COMMENT");
const string SourceCodeInstruction::LITERAL = string("LITERAL");
const string SourceCodeInstruction::LTORG = string("LTORG");


int SourceCodeInstruction::BASE_VALUE = 0;

SourceCodeInstruction::SourceCodeInstruction(
	string line)
{
	_line = SourceCodeLine(line);
}

SourceCodeInstruction::SourceCodeInstruction(
	SourceCodeLine line)
{
	_line = line;
}

bool SourceCodeInstruction::HasLabel()
{
	return _line.GetLabel().compare("") != 0;
}
SourceCodeLine SourceCodeInstruction::GetSourceCodeLine(){ return _line;}
string SourceCodeInstruction::ToString(){ return (GetInstructionType() + string(":") + _line.GetRawLine());}
int SourceCodeInstruction::GetLength(){return 0;}
int SourceCodeInstruction::GetLocation(){return _location;}
int SourceCodeInstruction::GetNextLocation(){return _nextLocation;}
string SourceCodeInstruction::GetInstructionType(){return SourceCodeInstruction::NONE;}
ModificationRecords SourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}
void SourceCodeInstruction::SetLocation(int location){_location = location;}
void SourceCodeInstruction::SetNextLocation(int location){_nextLocation = location;}

string SourceCodeInstruction::GetObjectCode(){return string("");}


/***********************************************
UNIT TESTS
g++ SourceCodeLine.cpp SourceCodeInstruction.cpp DataConverter.cpp
**********************************************/
/*
int main()
{
	SourceCodeInstruction instruction =
		SourceCodeInstruction("COPY     +START  #0                                                            ");

		cout << SourceCodeInstruction::SIC_BASIC << endl;


	return 0;
}
\*/
