#include "Memory.h"
#include "Registers.h"
#include "Instruction.h"
#include "DataConverter.h"
#include "InstructionFactory.h"
#include "FormatOneInstruction.h"
#include "AssemblyOperation.h"
#include "AssemblyOperationTable.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define SIC_FILE "a1.sic"
#define LINE_1 1
#define LINE_2 2
#define LINE_3 3
#define LINE_4 4
#define LINE_5 5
#define DEFAULT_MEMORY_LOCATION 1293

using namespace std;

/**
 * The main program. This will excute the
 * entire Assignment 1 application.
 */
int main()
{
	ifstream infile;
	infile.open (SIC_FILE);

	// First check if the file is valid.
	if(infile.fail())
	{
		cerr << "File was not found " << SIC_FILE << endl;
		return 1;
	}

	// Initiate some values.
	AssemblyOperationTable operations;
	Registers registers;
	Memory memory;
	InstructionFactory instructionFactory;

	string sLine = "";
	int lineIndex = 1;

	cout << "Mne\tFlags\tDisp/Op/Addr\tTA\tfmt\tEx/Notes" << endl;

	// Loop until we read the end of the file.
	while (!infile.eof())
	{
		try
		{
			int x;
			getline(infile, sLine);

			// The first line -- contains contents of X register
			if(LINE_1 == lineIndex)
			{
				DataConverter::ConvertToIntFromHexString(x, sLine, hex);
				registers.Insert(Registers::X, x);
			}
			// The second line -- contains contents of PC register
			else if(LINE_2 == lineIndex)
			{
				DataConverter::ConvertToIntFromHexString(x, sLine, hex);
				registers.Insert(Registers::PC, x);
			}
			// The third line -- contains contents of B register
			else if(LINE_3 == lineIndex)
			{
				DataConverter::ConvertToIntFromHexString(x, sLine, hex);
				registers.Insert(Registers::B, x);
			}
			// The fourth line -- contains contents of memory address location 050D
			else if(LINE_4 == lineIndex)
			{
				DataConverter::ConvertToIntFromHexString(x, sLine, hex);
				memory.Insert(DEFAULT_MEMORY_LOCATION, x);
			}
			// The fifth...nth line -- contains instructions (one per line)
			// to be disassembled
			else
			{
				// If it's not an empty string.
				if(sLine.compare("") != 0)
				{
					// Use the factory to create our instruction.
					Instruction* instruction =
						instructionFactory.Create(
							sLine,
							memory,
							registers,
							operations);

					// If we did not get a valid indstruction.
					// No bueno.
					if(0 == instruction)
					{
						delete instruction;
						throw "Instruction is not valid.";
					}

					// If we did get a value instruction. Output it.
					cout << instruction->ToString() << endl;

					// Ensure we don't leak any memory.
					delete instruction;

				}
				else
				{
					cerr << "Empty line. Line will be skipped." << endl;
				}

			}

		}
		catch(char const* exception)
		{
			cerr << "Exception: Line " << sLine << ". Error: " << exception << endl;
		}
		catch(...)
		{
			cerr << "Unknown exception. Line must be skipped." << endl;
		}

		lineIndex++;
	}


	// Cleanup the file.
	infile.close();

	return 0;
}
