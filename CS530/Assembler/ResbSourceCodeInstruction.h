/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ResbSourceCodeInstruction is a
 * specific instruction that will handle
 * when a RESB instruction is used. There is
 * no object code that gets created, just to
 * reserve a specific number of bytes.
 ******************************************/
#ifndef RESBSOURCECODEINSTRUCTION_H
#define RESBSOURCECODEINSTRUCTION_H

#include <string>
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"

class ResbSourceCodeInstruction : public SourceCodeInstruction
{
	public:
		ResbSourceCodeInstruction(
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
		int _length;
};

#endif
