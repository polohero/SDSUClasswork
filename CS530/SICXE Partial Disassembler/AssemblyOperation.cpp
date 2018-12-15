#include "AssemblyOperation.h"
#include <iostream>

using namespace std;

AssemblyOperation::AssemblyOperation(
	int opcode,
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
int AssemblyOperation::GetOpCode(){return _opcode;}
string AssemblyOperation::GetMnemonic(){return _mnemonic;}
string AssemblyOperation::GetFormat(){return _format;}
string AssemblyOperation::GetEffect(){return _effect;}
string AssemblyOperation::GetNotes(){return _notes;}
string AssemblyOperation::GetExample(){return _example;}


bool AssemblyOperation::operator <(AssemblyOperation other)
{
	return GetOpCode() < other.GetOpCode();
}
bool AssemblyOperation::operator >(AssemblyOperation other)
{
	return GetOpCode() > other.GetOpCode();
}
bool AssemblyOperation::operator ==(AssemblyOperation other)
{
	return GetOpCode() == other.GetOpCode();
}
bool AssemblyOperation::operator <=(AssemblyOperation other)
{
	return GetOpCode() <= other.GetOpCode();
}
bool AssemblyOperation::operator >=(AssemblyOperation other)
{
	return GetOpCode() >= other.GetOpCode();
}


