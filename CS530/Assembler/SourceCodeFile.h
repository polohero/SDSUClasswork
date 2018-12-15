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
#ifndef SOURCECODEFILE_H
#define SOURCECODEFILE_H

#include <string>
#include <vector>

#include "Literal.h"
#include "SourceCodeLine.h"
#include "LiteralTable.h"
#include "SymbolTable.h"
#include "SourceCodeInstruction.h"
#include "AssemblyOperation.h"
#include "AssemblyOperationTable.h"

class SourceCodeFile
{
	public:

		SourceCodeFile();
		/**
		 * Inserts a new instruction into the container.
		 */
		void Insert(SourceCodeInstruction* line);
		/**
		 * Gets an instruction based on the index.
		 */
		SourceCodeInstruction* Get(int index);
		/**
		 * Returns the size of the file.
		 */
		int Size();
		/**
		 * Returns a string representation
		 * of the symbol table.
		 */
		std::string DumpSymbolTable();
		/**
		 * Returns a string representation
		 * of the literal table.
		 */
		std::string DumpLiteralTable();
		/**
		 * Returns a string representation
		 * of the entire file.
		 */
		std::string Dump();
		/**
		 * Returns the total size of the
		 * entire file. Starting location -
		 * ending location.
		 */
		int GetMemorySize();
		/**
		 * Returns the starting location.
		 */
		int GetStartingLocation();

		int GetLocationCounter();

	private:

		std::vector<SourceCodeInstruction*> _lines;
		int _locationCounter;
		int _startingLocation;
		int _previousCounter;
};

#endif
