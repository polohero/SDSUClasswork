#ifndef FORMATZEROINSTRUCTION_H
#define FORMATZEROINSTRUCTION_H

#include <string>
#include "Memory.h"
#include "Registers.h"
#include "Instruction.h"
#include "DataConverter.h"
#include "AssemblyOperation.h"

/**
 * The FormatZeroInstruction is a specialized
 * Instruction that has 1 operand that is the
 * displacement.
 *
 * The format for a FormatZeroInstruction is
 * [ [op(8)] [x] [disp(15)] ].
 */
class FormatZeroInstruction : public Instruction
{
	public:
		/**
		 * The constructor for the FormatZeroInstruction.
		 * @param operation The AssemblyOperation data.
		 * @param instructionString The raw instruction.
		 * @param memory The current state of the memory.
		 * @param registers The current state of the registers.
		 */
		FormatZeroInstruction(
			AssemblyOperation operation,
			std::string instructionString,
			Memory memory,
			Registers registers);

		/**
		 * Returns the string representation of
		 * the instruction.
		 * @return a formatted string of the instruction.
		 */
		virtual std::string ToString();

		/**
		 * Gets if X should be indexed.
		 * @returns X flag.
		 */
		bool GetX();
		/**
		 * Gets the displacement.
		 * @returns the displacement.
		 */
		int GetDisplacement();
		/**
		 * Gets the target address.
		 * @returns the target address.
		 */
		int GetTargetAddress();

	private:
		std::string _instructionString;
		bool _x;
		int _displacement;
		int _targetAddress;
};

#endif
