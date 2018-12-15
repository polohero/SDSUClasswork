#ifndef FORMATFOURINSTRUCTION_H
#define FORMATFOURINSTRUCTION_H

#include <string>
#include "Memory.h"
#include "Registers.h"
#include "Instruction.h"
#include "DataConverter.h"
#include "AssemblyOperation.h"

/**
 * [ [op(6)] [nixbpe] [address (20) ]
 */
class FormatFourInstruction : public Instruction
{
	public:
		FormatFourInstruction(
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
		 * The address pased by the instruction.
		 */
		int _address;
		/**
		 * The target address of this instruction.
		 */
		int _targetAddress;
		/**
		 * The value..
		 */
		int _value;
		/**
		 * The addressing mode...
		 */
		std::string _addressingMode;
};

#endif
