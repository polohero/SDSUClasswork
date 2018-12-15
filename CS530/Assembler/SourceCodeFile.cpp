/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SourceCodeFile has a list of
 * instructions that have been parsed,
 * assigned locations, and are ready for
 * pass 2. This could also be represented
 * in the intermediate file, but instead
 * we have used it in memory.
 ******************************************/
#include <string>
#include <iostream>

#include "Symbol.h"
#include "SymbolTable.h"
#include "Literal.h"
#include "LiteralTable.h"
#include "DataConverter.h"
#include "SourceCodeFile.h"
#include "SourceCodeInstruction.h"
#include "SourceCodeInstructionFactory.h"
#include "AssemblyOperation.h"
#include "AssemblyOperationTable.h"
#include "LiteralPoolSourceCodeInstruction.h"

using namespace std;

SourceCodeFile::SourceCodeFile()
{
	_locationCounter = 0;
}

string SourceCodeFile::DumpSymbolTable()
{
	return SymbolTable::ToString();
}
string SourceCodeFile::DumpLiteralTable()
{
	return LiteralTable::ToString();
}


int SourceCodeFile::GetMemorySize(){return _locationCounter - _startingLocation;}

int SourceCodeFile::GetLocationCounter(){return _locationCounter;}

int SourceCodeFile::GetStartingLocation(){return _startingLocation;}


void SourceCodeFile::Insert(SourceCodeInstruction* line)
{
	if( Size() == 0 &&
	    line->GetInstructionType().compare(SourceCodeInstruction::START) != 0)
	{
		throw "All source files must start with a START instruction.";
	}
	else if( Size() == 0 )
	{
		_locationCounter = line->GetLocation();
		_startingLocation = line->GetLocation();
		line->SetNextLocation(_startingLocation);
	}

	line->SetLocation(_locationCounter);


	if( true == line->HasLabel() &&
		line->GetInstructionType().compare(SourceCodeInstruction::EQU) != 0 )
	{
		Symbol symbol =
			Symbol(
				line->GetSourceCodeLine().GetLabel(),
				_locationCounter,
				Symbol::LABEL);
		SymbolTable::Insert(symbol);
	}

	_locationCounter += line->GetLength();
	_lines.push_back(line);

	if( Size() > 1 )
	{
		for(int i = Size() - 1; i >=0; i--)
		{
			SourceCodeInstruction* previousInstruction =
				Get(i);

			previousInstruction->SetNextLocation(_locationCounter);

			if( previousInstruction->GetLength() != 0 )
			{
				break;
			}
		}
	}

	// If this is a literal pool instruction
	// dump all the literals we've collected
	// into the file at this location.
	// Then everything will continue on.
	if( line->GetInstructionType().compare(SourceCodeInstruction::LTORG) == 0 ||
	    line->GetInstructionType().compare(SourceCodeInstruction::END) == 0)
	{
		vector<Literal> literals =
			LiteralTable::GetUnpooled();

		for(int i = 0; i < literals.size(); i++)
		{
			Literal literal =
				literals[i];

			Literal* literPtr =
				LiteralTable::GetPointer(literal.GetLiteralString());

			literPtr->SetLocation(_locationCounter);
			literPtr->SetHasBeenPooled(true);

			SourceCodeLine newSourceCodeLine =
				literal.GetSourceCodeLine();

			SourceCodeInstructionFactory factory;

			SourceCodeInstruction* instruction =
					factory.GetLiteral(literal, newSourceCodeLine);

			instruction->SetLocation(_locationCounter);
			instruction->SetNextLocation(_locationCounter);

			_locationCounter += literal.GetLength();

			_lines.push_back(instruction);

			for(int i = Size() - 1; i >=0; i--)
			{
				SourceCodeInstruction* previousInstruction =
					Get(i);

				previousInstruction->SetNextLocation(_locationCounter);

				if( previousInstruction->GetLength() != 0 )
				{
					break;
				}
			}

		}
	}
}

SourceCodeInstruction* SourceCodeFile::Get(int index)
{
	return _lines[index];
}

int SourceCodeFile::Size()
{
	return _lines.size();
}

string SourceCodeFile::Dump()
{
	string returnString;

	returnString += "Loc/Next\t\tCode\t\tObjectCode\n";

	for( int i = 0; i < Size(); i++)
	{
		string current;

		SourceCodeInstruction* instruction =
			Get(i);

		current +=
			DataConverter::PadRight(
				DataConverter::ConvertIntToHex(instruction->GetLocation()) +
				"/" +
				DataConverter::ConvertIntToHex(instruction->GetNextLocation()),
			12,
			' ');

		current += DataConverter::PadRight(instruction->ToString(), 20, ' ');
		current += "\t";
		current += instruction->GetObjectCode();
		current += "\n";

		returnString += current;
	}

	return returnString;
}

/******************************************************
UNIT TESTS
g++ SourceCodeLine.cpp AssemblyOperation.cpp AssemblyOperationTable.cpp SourceCodeFile.cpp DataConverter.cpp
******************************************************/
/*int main()
{

	try
	{
		SourceCodeFile file;

		file.Insert("COPY     +START  #0                                                            ");

		SourceCodeLine line = file.Get(0);

		cout << line.GetRawLine() << endl;
		cout << line.GetLocation() << endl;
	}
	catch(char const* exception)
	{
		cerr << "Exception: " << exception << endl;
		return 1;
	}

	return 0;


}
*/
