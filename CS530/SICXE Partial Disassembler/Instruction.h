#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include "AssemblyOperation.h"

/**
 * An Instruction is the base class for all
 * instructions. Each type of instruction will
 * inherit from this class, and must implement
 * the ToString() method.
 */
class Instruction
{
	public:
		/**
		 * The constructor for an Instruction;
		 * @param operation The AssemblyOperation.
		 */
		Instruction (AssemblyOperation operation);

		/**
		 * Formats the Instruction.
		 * @return A formatted string of the instruction.
		 */
		virtual std::string ToString();

		/**
		 * Gets the AssemblyOperation.
		 * @return The AssemblyOperation.
		 */
		AssemblyOperation GetAssemblyOperation();

	protected:
		/**
		 * The AssemblyOperation data.
		 */
		AssemblyOperation _operation;
};

#endif
