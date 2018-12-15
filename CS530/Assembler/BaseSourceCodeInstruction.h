/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The BaseSourceCodeInstruction is a
 * compiler instruction that helps it keep
 * track of the current value of the base
 * register.
 ******************************************/
#ifndef BASESOURCECODEINSTRUCTION_H
#define BASESOURCECODEINSTRUCTION_H

#include <string>
#include "SymbolTable.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"

class BaseSourceCodeInstruction : public SourceCodeInstruction
{
	public:
		BaseSourceCodeInstruction(
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
