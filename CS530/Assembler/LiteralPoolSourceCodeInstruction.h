/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The LiteralPoolSourceCodeInstruction is a
 * specific instruction that tells the
 * assembler where to build literal pools.
 ******************************************/
#ifndef LITERALPOOLSOURCECODEINSTRUCTION_H
#define LITERALPOOLSOURCECODEINSTRUCTION_H

#include <string>
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"

class LiteralPoolSourceCodeInstruction : public SourceCodeInstruction
{
	public:
		/**
		 * Constructor. All it takes is
		 * a line of source code.
		 */
		LiteralPoolSourceCodeInstruction(
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
};

#endif
