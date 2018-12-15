/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SymbolTable is used to store/retrive
 * symbols that have been defined in the
 * source code.
 ******************************************/
#include <map>
#include <iostream>
#include "Symbol.h"
#include "SymbolTable.h"
#include "DataConverter.h"
#include "SourceCodeInstruction.h"

using namespace std;

symbol_map SymbolTable::_symbolTable;


SymbolTable::SymbolTable()
{

}

Symbol* SymbolTable::Get(string label)
{
	if( false == IsSymbolInTable(label) )
	{
		return 0;
	}


	symbol_map::iterator i = _symbolTable.find(label);

	return &i->second;
}

string SymbolTable::ToString()
{
	string returnValue;

	returnValue += "Name\t\tAddress\t\tType\n";

	for(symbol_map::iterator it = _symbolTable.begin(); it != _symbolTable.end(); ++it) {
	 	 Symbol symbol = it->second;

	 	 returnValue += symbol.GetLabel();
		 returnValue += "\t\t";
	 	 returnValue += DataConverter::ConvertIntToHex(symbol.GetAddress());
		 returnValue += "\t\t";
	 	 returnValue += symbol.GetSymbolType();
	 	 returnValue += "\n";
	}

	return returnValue;
}

/**
 * Checks if the symbol is in the table.
 */
bool SymbolTable::IsSymbolInTable(string label)
{
	if( _symbolTable.size() == 0 )
	{
		return false;
	}

	symbol_map::iterator i = _symbolTable.find(label);

	return i != _symbolTable.end();
}

int SymbolTable::Size()
{
	return _symbolTable.size();
}

void SymbolTable::Insert(Symbol symbol)
{
	if(true == IsSymbolInTable(symbol.GetLabel()))
	{
		throw "Symbol is already added. It cannot be added again.";
	}

	_symbolTable.insert(symbol_pair(symbol.GetLabel(), symbol));
}

/*********************************************
UNIT TESTS
g++ SymbolTable.cpp Symbol.cpp
*********************************************/
/*
int main()
{
	Symbol symbol =
		Symbol("SOMELBL", 69);

	string currentTest;

	currentTest = "GetLabel()";
	if( symbol.GetLabel().compare("SOMELBL") == 0)
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}

	currentTest = "GetAddress()";
	if( symbol.GetAddress() == 69)
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}


	SymbolTable table;

	currentTest = "SymbolTable.Size nothing";
	if( table.Size() == 0)
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}

	currentTest = "SymbolTable.Get nothing";
	if( table.Get("AAA") == 0 )
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}

	table.Insert(symbol);

	currentTest = "SymbolTable.Size";
	if( table.Size() == 1)
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}

	currentTest = "SymbolTable.Insert/Get something 1";
	if( table.Get("SOMELBL")->GetAddress() == 69 )
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}
	currentTest = "SymbolTable.Insert/Get something 2";
	if( table.Get("SOMELBL")->GetLabel().compare("SOMELBL") == 0 )
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}

	Symbol symbol2 =
		Symbol("ADS", 56);

	table.Insert(symbol2);

	currentTest = "SymbolTable.Size 2";
	if( table.Size() == 2)
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}

	currentTest = "SymbolTable.Insert/Get something 3";
	if( table.Get("SOMELBL")->GetAddress() == 69 )
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}
	currentTest = "SymbolTable.Insert/Get something 4";
	if( table.Get("SOMELBL")->GetLabel().compare("SOMELBL") == 0 )
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}

	currentTest = "SymbolTable.Insert/Get something 5";
	if( table.Get("ADS")->GetAddress() == 56 )
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}
	currentTest = "SymbolTable.Insert/Get something 6";
	if( table.Get("ADS")->GetLabel().compare("ADS") == 0 )
	{
		cout << "PASSED " << currentTest << endl;
	}
	else
	{
		cout << "FAILED " << currentTest << endl;
	}
}
*/
