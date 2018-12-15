/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 ******************************************/
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <typeinfo>

#include "Symbol.h"
#include "SymbolTable.h"
#include "DataConverter.h"
#include "SourceCodeFile.h"
#include "SourceCodeInstruction.h"
#include "SourceCodeInstructionFactory.h"
#include "ObjectCodeFormatter.h"

#define MIN_ARGUMENTS 1
#define TAB '\t'
#define NEWLINE '\n'
#define CARRIAGE_RETURN '\r'
#define SPACE ' '
#define EXE "scl.o"
#define SYMBOL_TABLE_FILE "scl.symtab"
#define LITERAL_TABLE_FILE "scl.littab"
#define INTERMIDIATE_FILE "scl.imf"

#define COMMAND_LINE_CHAR '-'
#define COMMAND_FILE_NAME 'f'
#define COMMAND_DEBUG_MODE 'd'
#define COMMAND_LITERAL 'l'
#define COMMAND_SYMBOL 's'
#define COMMAND_INTERMEDIATE 'i'

using namespace std;

bool _debugMode = false;
bool _literalMode = false;
bool _symbolMode = false;
bool _intermediateMode = false;

/**
 * Finds out what machine type the source
 * file is targeting.
 * @param sourceFile. String of the
 * file to compile.
 * @return <0 if there is an error, otherwise
 *	the machine type for the source file.
 */
int getMachineType(string sourceFile);
/**
 * Gets the source file to compile.
 * If it was passed as an argument then
 * that's the file. Otherwise, prompt
 * the user to enter the file. This
 * will also process all of the other command
 * line arguments.
 * @param argc The number of parameters.
 * @param argv The arguments.
 * @return The source file to try to compile
 */
string getCommandLineArguments(int argc, char* argv[]);
/**
 * Performs the pass one assembly of the
 * source file.
 * @param sourceFile The file to assemble.
 * @param machineType The machine type to assemble the source for..
 * @return An object representing all the
 * source code for the file.
 */
SourceCodeFile* passOne(string sourceFile, int machineType);

void loadRegisterSymbols();

/**
 * Performs the pass two assembly of
 * the source file.
 * @param file The "pre-compiled" IE pass one source file.
 * @return A string of the compiled object code.
 */
string passTwo(SourceCodeFile* file);
/**
 * Checks if the line is a line to try to assemble.
 * @param line The line to assemble.
 * @return True if it should be assembled, false if not.
 */
bool shouldTryToAssembleLine(string line);


/**
 * The main program. This will execute the
 * entire Assignment 2 application.
 */
int main(int argc, char* argv[])
{
	// First get the file that we're going to
	// try to compile.
	string sourceFile = getCommandLineArguments(argc, argv);

	if( sourceFile.length() == 0 )
	{
		return 1;
	}

	// Next determine what machine is being
	// targeted.
	int machineType = getMachineType(sourceFile);

	ofstream objectFile;
	ofstream symbolTableFile;
	ofstream literalTableFile;
	ofstream intermediateFile;

	// If the machineType is 0, then
	// that means some error has occured.
	// Exit out of the program.
	if( machineType == 0 )
	{
		return 1;
	}

	// Pre-load the symbol table with
	// the registers.
	loadRegisterSymbols();

	// Now that we know what machine type
	// to use, we need to perform pass one
	// and inspect each of the instruction lines.
	SourceCodeFile* file =
		passOne(sourceFile, machineType);

	// If there was an error, exit.
	if( file == 0 )
	{
		return 1;
	}

	// All right... Pass two now!
	string objectCode =
		passTwo(file);

	// Check if the second pass failed for
	// some reason.
	if( objectCode.compare(string("")) == 0 )
	{
		cerr << "Unable to create object file." << endl;
		return 1;
	}

	// Delete the file if it already exists.
	remove(EXE);
	// All right. Create the file. We're done!
	objectFile.open(EXE);
	objectFile << objectCode;
	objectFile.close();


	if( true == _debugMode ||
	    true == _intermediateMode)
	{
		remove(INTERMIDIATE_FILE);
		intermediateFile.open(INTERMIDIATE_FILE);
		intermediateFile << file->Dump(); ;
		intermediateFile.close();
	}

	if( true == _debugMode ||
	    true == _symbolMode)
	{
		// And dump the symbol table.
		remove(SYMBOL_TABLE_FILE);
		symbolTableFile.open(SYMBOL_TABLE_FILE);
		symbolTableFile << file->DumpSymbolTable(); ;
		symbolTableFile.close();
	}

	if( true == _debugMode ||
	    true == _literalMode)
	{
		// And dump the literal table.
		remove(LITERAL_TABLE_FILE);
		literalTableFile.open(LITERAL_TABLE_FILE);
		literalTableFile << file->DumpLiteralTable(); ;
		literalTableFile.close();
	}

	return 0;
}

string  passTwo(SourceCodeFile* file)
{
	string objectCode;

	try
	{
		ObjectCodeFormatter formatter;

		objectCode =
			formatter.FormatFile(file);

		if( objectCode.compare(string("")) == 0 )
		{
			cerr << formatter.GetErrorMessages() << endl;
			return string("");
		}
	}
	catch(char const* exception)
	{
		cerr << exception
			 << endl;
	}
	catch(...)
	{
		cerr << "Unknown Exception " << endl;
	}

	return objectCode;
}

bool shouldTryToAssembleLine(string line)
{
	if( line.length() == 0 )
	{
		return false;
	}

	if( ((int)line[0]) == 13 )
	{
		return false;
	}

	// Loop through each character.
	// If it's a character that is not
	// a "blank" character, then it must
	// be something we care about.
	for(int i = 0; i < line.length(); i++)
	{
		if(TAB != line[i] &&
		   SPACE != line[i] &&
		   CARRIAGE_RETURN != line[i] &&
		   NEWLINE != line[i])
		{
			return true;
		}
	}

	return false;
}

string getCommandLineArguments(int argc, char* argv[])
{
	string sourceFile;

	// If no arguments were provided then,
	// we need to ask the user what file
	// they want to be compiled.
	if( MIN_ARGUMENTS == argc)
	{
		cout << "Please enter the source filename: \n";
		getline(cin, sourceFile);
	}
	else
	{
		for(int i = 1; i < argc; i++)
		{
			string argument = string(argv[i]);

			if( argument.length() < 2 ||
			    argument[0] != COMMAND_LINE_CHAR)
			{
				cerr << "Argument #" << i << " is not valid." << endl;
				return string("");
			}
			// Check if the user specified to use
			// debugging mode.
			else if( argument[1] == COMMAND_DEBUG_MODE )
			{
				_debugMode = true;
			}
			else if( argument[1] == COMMAND_LITERAL )
			{
				_literalMode = true;
			}
			else if( argument[1] == COMMAND_INTERMEDIATE )
			{
				_intermediateMode = true;
			}
			else if( argument[1] == COMMAND_SYMBOL )
			{
				_symbolMode = true;
			}


			// Check if the user passed in a file
			// name.
			else if( argument[1] == COMMAND_FILE_NAME )
			{
				if( argument.length() < 3 )
				{
					cerr << "File is not valid." << endl;
					return string("");
				}
				sourceFile = argument.substr(2, string::npos);
			}
			// Otherwise barf. We don't know what
			// this argument is.
			else
			{
				cerr << "Unknown arugment #" << i << endl;
				return string("");
			}
		}

		if( sourceFile.length() == 0 )
		{
			cout << "Please enter the source filename: \n";
			getline(cin, sourceFile);
		}
	}

	return sourceFile;
}

SourceCodeFile* passOne(
	string sourceFile,
	int machineType)
{
	ifstream infile;
	SourceCodeInstructionFactory factory;
	SourceCodeFile* file = new SourceCodeFile();
	bool errorOccured = false;

	infile.open (sourceFile.c_str());

	if( true == infile.fail() )
	{
		cerr << "File was not found " << sourceFile << endl;
		return 0;
	}

	int lineNumber = 1;
	string sLine;

	// Loop through each line and
	// find the instruction for each one.
	while (!infile.eof())
	{
		try
		{
			getline(infile, sLine);

			// If the line is a "blank" line,
			// then ignore it.
			if( true == shouldTryToAssembleLine(sLine) )
			{
				SourceCodeInstruction* instruction =
					factory.GetSourceCodeInstruction(
						sLine,
						machineType,
						file);

				file->Insert(instruction);

			}
		}
		catch(char const* exception)
		{
			cerr << "Unable to parse line: "
				 << lineNumber
				 << " "
				 << exception
				 << endl;
			errorOccured = true;
		}
		catch(...)
		{
			cerr << "Unknown Exception on line "
				 << lineNumber << endl
				 << " Line: "
				 << sLine << endl;
			errorOccured = true;
		}

		lineNumber++;
	}

	infile.close();

	if( errorOccured == true )
	{
		cerr << "Unable to parse file successfully. Ending..."
		     << endl;
		return 0;
	}

	return file;
}

int getMachineType(string sourceFile)
{
	ifstream infile;
	int machineType;
	SourceCodeInstructionFactory factory;
	bool errorOccured = false;

	infile.open (sourceFile.c_str());

	if( true == infile.fail() )
	{
		cerr << "File was not found " << sourceFile << endl;
		return 0;
	}

	int lineNumber = 1;
	string sLine;

	// Loop until we read the end of the file.
	// and determine if we should be using an
	// XE or a SIC/Basic machine.
	while (!infile.eof())
	{
		try
		{
			getline(infile, sLine);

			if( true == shouldTryToAssembleLine(sLine) )
			{
				machineType =
					factory.DetermineMachineType(sLine);

				if( machineType == SourceCodeInstruction::SIC_XE )
				{
					break;
				}
			}
		}
		catch(char const* exception)
		{
			cerr << "Unable to parse line: "
				 << lineNumber
				 << " "
				 << exception
				 << endl;
			errorOccured = true;
		}
		catch(...)
		{
			cerr << "Unknown Exception on line "
				 << lineNumber << endl
				 << " Line: " << sLine
				 << endl;
			errorOccured = true;
		}

		lineNumber++;
	}

	infile.close();

	if( errorOccured == true )
	{
		cerr << "Unable to parse file successfully. Ending..."
		     << endl;
		return 0;
	}

	return machineType;
}

void loadRegisterSymbols()
{
		Symbol a =
			Symbol(
				Symbol::REGISTER_A ,
				Symbol::REGISTER_A_ADDRESS,
				Symbol::REGISTER);
		SymbolTable::Insert(a);

		Symbol x =
			Symbol(
				Symbol::REGISTER_X ,
				Symbol::REGISTER_X_ADDRESS,
				Symbol::REGISTER);
		SymbolTable::Insert(x);

		Symbol l =
			Symbol(
				Symbol::REGISTER_L ,
				Symbol::REGISTER_L_ADDRESS,
				Symbol::REGISTER);
		SymbolTable::Insert(l);

		Symbol b =
			Symbol(
				Symbol::REGISTER_B ,
				Symbol::REGISTER_B_ADDRESS,
				Symbol::REGISTER);
		SymbolTable::Insert(b);

		Symbol s =
			Symbol(
				Symbol::REGISTER_S ,
				Symbol::REGISTER_S_ADDRESS,
				Symbol::REGISTER);
		SymbolTable::Insert(s);

		Symbol t =
			Symbol(
				Symbol::REGISTER_T ,
				Symbol::REGISTER_T_ADDRESS,
				Symbol::REGISTER);
		SymbolTable::Insert(t);

		Symbol f =
			Symbol(
				Symbol::REGISTER_F ,
				Symbol::REGISTER_F_ADDRESS,
				Symbol::REGISTER);
		SymbolTable::Insert(f);

		Symbol pc =
			Symbol(
				Symbol::REGISTER_PC ,
				Symbol::REGISTER_PC_ADDRESS,
				Symbol::REGISTER);
		SymbolTable::Insert(pc);

		Symbol sw =
			Symbol(
				Symbol::REGISTER_SW ,
				Symbol::REGISTER_SW_ADDRESS,
				Symbol::REGISTER);
	SymbolTable::Insert(sw);
}

