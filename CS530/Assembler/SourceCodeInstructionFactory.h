/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SourceCodeInstructionFactory is
 * in charge of determining what type of
 * instruction this line of source code
 * is, and return a specific source code
 * instruction class.
 ******************************************/
#ifndef SOURCECODEINSTRUCTIONFACTORY_H
#define SOURCECODEINSTRUCTIONFACTORY_H

#include <string>
#include "Literal.h"
#include "SourceCodeLine.h"
#include "SourceCodeFile.h"
#include "SourceCodeInstruction.h"
#include "AssemblyOperation.h"
#include "AssemblyOperationTable.h"

class SourceCodeInstructionFactory
{
	public:
		/**
		 * Determines the machine type for a
		 * specific line from source code.
		 * @param line A line of source code.
		 * @return An integer of the machine type.
		 */
		int DetermineMachineType(std::string line);

		/**
		 * Creates a specifc instruction type
		 * based on a single source code line.
		 * @param line A line of source code.
		 * @param machineType The machine type.
		 * @param symbols A pointer to the symbol table.
		 * @param literals A pointer to the literal table.
		 * @param literals A pointer to the literal table.
		 * @return An integer of the machine type.
		 */
		SourceCodeInstruction* GetSourceCodeInstruction(
			std::string line,
			int machineType,
			SourceCodeFile* file);

		SourceCodeInstruction* GetLiteral(Literal literal, SourceCodeLine line);

	private:
		SourceCodeInstruction* handleSingleOperation(
			std::string line,
			AssemblyOperation* operation);

		AssemblyOperationTable _opTable;
};

#endif
