#ifndef INSTRUCTIONFACTORY_H
#define INSTRUCTIONFACTORY_H

#include <string>
#include "Instruction.h"
#include "Registers.h"
#include "Memory.h"
#include "DataConverter.h"
#include "AssemblyOperationTable.h"
#include "AssemblyOperation.h"

/**
 * The InstructionFactory will pre-process the
 * instruction string and determine what
 * kind of instruction it is. Then create
 * the specific class needed for it.
 */
class InstructionFactory
{
	public:
		/**
		 * Creates the Instruction.
		 * @param instructionString The full instruction.
		 * @param memory The current state of memory.
		 * @param registers The current state of the registers.
		 * @param instructions The table of instruction data.
		 * @return The specific Instruction based on the pre-processing of
		 * the instruction string.
		 */
		Instruction* Create(
			std::string instructionString,
			Memory memory,
			Registers registers,
			AssemblyOperationTable instructions);
	private:
		/**
		 * Determines the op code for the instruction.
		 * @param instructionString The raw instruction.
		 */
		int getOpCode(std::string instructionString);

		/**
		 * Handles an operation that only has
		 * 1 format.
		 * @param instructionString The raw instruction.
		 * @param operation The operation information.
		 * @param memory The current state of memory.
		 * @param registers The current state of registers.
		 */
		Instruction* handleSingleOperation(
				std::string instructionString,
				AssemblyOperation operation,
				Memory memory,
				Registers registers);

		/**
		 * Handles an operation that has
		 * multiple formats.
		 * @param instructionString The raw instruction.
		 * @param operation The operation information.
		 * @param memory The current state of memory.
		 * @param registers The current state of registers.
		 */
		Instruction* handleMultiOperation(
				std::string instructionString,
				AssemblyOperation operation,
				Memory memory,
				Registers registers);
};

#endif
