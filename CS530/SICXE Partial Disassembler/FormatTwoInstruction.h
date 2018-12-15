#ifndef FORMATTWOINSTRUCTION_H
#define FORMATTWOINSTRUCTION_H

#include <string>
#include "Registers.h"
#include "Instruction.h"
#include "DataConverter.h"
#include "AssemblyOperation.h"

/**
 * A FormatTwoInstruction is a specialized
 * instruction that accepts 1 or 2 operands and
 * performs an operation based on those 2 operands.
 *
 * [ [op(8)] [r1(4) r2(4)] ]: It would appear r2 is optional,
 * based on a couple of the operations (example: SVC).
 */
class FormatTwoInstruction : public Instruction
{
	public:
		/**
		 * Constructor for the FormatTwoInstruction.
		 */
		FormatTwoInstruction(
			AssemblyOperation operation,
			std::string instructionString);

		/**
		 * Returns the string representation of
		 * the instruction.
		 * @return a formatted string of the instruction.
		 */
		virtual std::string ToString();

		/**
		 * Returns the R1 value.
		 * @return The R1 data.
		 */
		std::string GetR1();

		/**
		 * Returns the R2 value.
		 * @return The R2 data.
		 */
		std::string GetR2();

	private:
		/**
		 * The raw instruction string.
		 */
		std::string _instructionString;
		/**
		 * The R1 operand.
		 */
		std::string _r1;
		/**
		 * The R2 operand.
		 */
		std::string _r2;
};

#endif
