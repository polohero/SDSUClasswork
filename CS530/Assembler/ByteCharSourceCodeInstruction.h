/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ByteCharSourceCodeInstruction is a
 * specific instruction that will handle
 * when a BYTE instruction is used, and
 * the user is specifying to use a
 * character representation in the source
 * code.
 ******************************************/
#ifndef BYTECHARSOURCECODEINSTRUCTION_H
#define BYTECHARSOURCECODEINSTRUCTION_H

#include <string>
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"

class ByteCharSourceCodeInstruction : public SourceCodeInstruction
{
	public:
		ByteCharSourceCodeInstruction(
			SourceCodeLine line);

		/**
		 * Returns a string representation of
		 * the instruction.
		 **/
		virtual std::string ToString();
		/**
		 * Returns the length the instruction
		 * will take up in the object file.
		 **/
		virtual int GetLength();
		/**
		 * Returns the type of the instruction.
		 **/
		virtual std::string GetInstructionType();
		/**
		 * Returns the object code for
		 * the instruction.
		 **/
		virtual std::string GetObjectCode();
		/**
		 * Returns the modification records needed
		 * for this instruction.
		 **/
		virtual ModificationRecords GetModificationRecords();

	private:
		std::string _characters;
};

#endif
