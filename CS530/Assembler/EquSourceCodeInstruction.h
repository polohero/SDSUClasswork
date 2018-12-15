/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The EquSourceCodeInstruction is
 * used for equating variables.
 ******************************************/
#ifndef EQUSOURCECODEINSTRUCTION_H
#define EQUSOURCECODEINSTRUCTION_H

#include <string>
#include "SymbolTable.h"
#include "LiteralTable.h"
#include "SourceCodeLine.h"
#include "SourceCodeInstruction.h"
#include "ModificationRecords.h"

class EquSourceCodeInstruction : public SourceCodeInstruction
{
	public:
		EquSourceCodeInstruction(
			SourceCodeLine line,
			int currentLocation);

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

		int _address;

};

#endif
