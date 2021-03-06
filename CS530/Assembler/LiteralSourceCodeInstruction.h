/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SourceCodeInstruction is an
 * instruction to tell the assembler
 * about a specific literal.
 ******************************************/
#ifndef LITERALSOURCECODEINSTRUCTION_H
#define LITERALSOURCECODEINSTRUCTION_H

#include <string>
#include "Literal.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"

class LiteralSourceCodeInstruction  : public SourceCodeInstruction
{
	public:
		LiteralSourceCodeInstruction(
			SourceCodeLine firstLine,
			Literal literal);

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
		int _literalType;

		std::string _hexCharacters;
		std::string _characters;
		int _integer;
		Literal _literal;
};

#endif
