/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The LiteralTable is used to store/retrive
 * literals that have been defined in the
 * source code.
 ******************************************/
#include <map>
#include <iostream>
#include <vector>
#include "Literal.h"
#include "LiteralTable.h"
#include "DataConverter.h"
#include "SourceCodeInstruction.h"

using namespace std;

literal_map LiteralTable::_literalTable;

LiteralTable::LiteralTable()
{

}

vector<Literal> LiteralTable::GetUnpooled()
{
	vector<Literal> literals;

	for(literal_map::iterator it = _literalTable.begin(); it != _literalTable.end(); ++it) {
	 	 Literal literal = it->second;

	 	 if( false == literal.HasBeenPooled() )
	 	 {
			 literals.push_back(literal);
		 }
	}

	return literals;
}

Literal LiteralTable::Get(string literalString)
{
	literal_map::iterator i = _literalTable.find(literalString);

	return i->second;
}

Literal* LiteralTable::GetPointer(string literalString)
{
	literal_map::iterator i = _literalTable.find(literalString);

	return &i->second;
}

string LiteralTable::ToString()
{
	string returnValue;

	returnValue += "Literal\t\tValue\t\tLocation\n";

	for(literal_map::iterator it = _literalTable.begin(); it != _literalTable.end(); ++it) {
	 	 Literal literal = it->second;

		returnValue += literal.GetLiteralString();
		returnValue += "\t\t";
		returnValue += literal.GetObjectCode();
		returnValue += "\t\t";
		returnValue +=
			DataConverter::ConvertIntToHex(literal.GetLocation());
		returnValue += "\n";
	}

	return returnValue;
}

/**
 * Checks if the symbol is in the table.
 */
bool LiteralTable::IsLiteralInTable(string literalString)
{
	literal_map::iterator i = _literalTable.find(literalString);

	return i != _literalTable.end();
}

int LiteralTable::Size(){return _literalTable.size();}

void LiteralTable::Insert(Literal literal)
{
	if(true == IsLiteralInTable(literal.GetLiteralString()))
	{
		return;
	}

	_literalTable.insert(literal_pair(literal.GetLiteralString(), literal));
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
