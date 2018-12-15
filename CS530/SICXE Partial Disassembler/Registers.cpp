#include <map>
#include <string>
#include <iostream>
#include "Registers.h"

using namespace std;

const string Registers::A = "A";
const string Registers::X = "X";
const string Registers::L = "L";
const string Registers::B = "B";
const string Registers::S = "S";
const string Registers::T = "T";
const string Registers::F = "F";
const string Registers::PC = "PC";
const string Registers::SW = "SW";

int Registers::Get(string reg)
{
	register_map::iterator i = _registers.find(reg);

	return i->second;
}

void Registers::Insert(string reg, int data)
{
	// Validate that the register passed is
	// correct.
	if(reg.compare(A) == 0 ||
	   reg.compare(X) == 0 ||
	   reg.compare(L) == 0 ||
	   reg.compare(B) == 0 ||
	   reg.compare(S) == 0 ||
	   reg.compare(T) == 0 ||
	   reg.compare(F) == 0 ||
	   reg.compare(PC) == 0 ||
	   reg.compare(SW) == 0)
	 {
		 // If it is. Enter the data.
		 _registers.insert(register_pair(reg, data));
		return;
	 }

	// Otherwise we have a problem.
	throw "Unknown register.";
}


