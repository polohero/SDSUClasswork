#ifndef FORMATONEINSTRUCTION_H
#define FORMATONEINSTRUCTION_H

#include <string>
#include "Instruction.h"
#include "AssemblyOperation.h"

/**
 * A FormatOneInstruction is a specific instruction
 * Format one instructions only have an op code,
 * and have no operands.
 * [ op(8) ].
 */
class FormatOneInstruction : public Instruction
{
	public:
		/**
		 * The constructor for the FormatOneInstruction.
		 * @param operation The operation data.
		 * @param instructionString The raw instruction.
		 */
		FormatOneInstruction(
			AssemblyOperation operation,
			std::string instructionString);

		/**
		 * Returns the string representation of
		 * the instruction.
		 * @return a formatted string of the instruction.
		 */
		virtual std::string ToString();

	private:
		std:: string _instructionString;
};

#endif
