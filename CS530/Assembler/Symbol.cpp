/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Symbol represents a single symbol
 * that has been written in the source
 * code.
 ******************************************/
#include <string>
#include "Symbol.h"

using namespace std;

const string Symbol::REGISTER = string("REGISTER");
const string Symbol::LABEL = string("LABEL");
const string Symbol::EQU_R = string("EQU_R");
const string Symbol::EQU_A = string("EQU_A");

const string Symbol::REGISTER_A = string("A");
const int Symbol::REGISTER_A_ADDRESS = 0;

const string Symbol::REGISTER_X = string("X");
const int Symbol::REGISTER_X_ADDRESS = 1;

const string Symbol::REGISTER_L = string("L");
const int Symbol::REGISTER_L_ADDRESS = 2;

const string Symbol::REGISTER_B = string("B");
const int Symbol::REGISTER_B_ADDRESS = 3;

const string Symbol::REGISTER_S = string("S");
const int Symbol::REGISTER_S_ADDRESS = 4;

const string Symbol::REGISTER_T = string("T");
const int Symbol::REGISTER_T_ADDRESS = 5;

const string Symbol::REGISTER_F = string("F");
const int Symbol::REGISTER_F_ADDRESS = 6;

const string Symbol::REGISTER_PC = string("PC");
const int Symbol::REGISTER_PC_ADDRESS = 8;

const string Symbol::REGISTER_SW = string("SW");
const int Symbol::REGISTER_SW_ADDRESS = 9;

Symbol::Symbol(string label, int address, string symbolType)
{
	_label = label;
	_address = address;
	_symbolType = symbolType;
}

string Symbol::GetLabel(){return _label;}
int Symbol::GetAddress(){return _address;}
string Symbol::GetSymbolType(){return _symbolType;}
