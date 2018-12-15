#ifndef FORMATTHREEINSTRUCTION_H
#define FORMATTHREEINSTRUCTION_H

#include <string>
#include "Memory.h"
#include "Registers.h"
#include "Instruction.h"
#include "DataConverter.h"
#include "AssemblyOperation.h"

/**
 * A FormatThreeInstruction is a specific
 * instruction. The format three instruction
 * is of the format:
 * [ [op(6)] [nixbpe] [disp(12)] ]
 */
class FormatThreeInstruction : public Instruction
{
	public:
		/**
		 * The constructor for a FormatThreeInstruction.
		 * @param operation The operation info.
		 * @param instructionString The raw instruction.
		 * @param memory The current state of the memory.
		 * @param registers The current state of the registers.
		 */
		FormatThreeInstruction(
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

	private:
		/**
		 * Determines the addressing mode.
		 */
		std::string determineAddressingMode();

		/**
		 * Calculates the target address.
		 */
		int getTargetAddress(
				Registers registers,
				Memory memory);

		/**
		 * The raw instruction.
		 */
		std::string _instructionString;
		/**
		 * The n flag.
		 */
		bool _n;
		/**
		 * The i flag.
		 */
		bool _i;
		/**
		 * The x flag.
		 */
		bool _x;
		/**
		 * The b flag.
		 */
		bool _b;
		/**
		 * The p flag.
		 */
		bool _p;
		/**
		 * The e flag.
		 */
		bool _e;
		/**
		 * The displaceent.
		 */
		int _displacement;
		/**
		 * The target address..
		 */
		int _targetAddress;
		/**
		 * The target address..
		 */
		std::string _addressingMode;
};

#endif

