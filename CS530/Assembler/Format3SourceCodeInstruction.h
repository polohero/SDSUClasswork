/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Format3SourceCodeInstruction is
 * used for 3 byte instructions.
 ******************************************/
#ifndef FORMATTHREESOURCECODEINSTRUCTION_H
#define FORMATTHREESOURCECODEINSTRUCTION_H

#include <string>
#include "AssemblyOperation.h"
#include "SymbolTable.h"
#include "LiteralTable.h"
#include "SourceCodeLine.h"
#include "SourceCodeInstruction.h"
#include "ModificationRecords.h"

class Format3SourceCodeInstruction : public SourceCodeInstruction
{
	public:
		Format3SourceCodeInstruction(
			SourceCodeLine line,
			AssemblyOperation* assemblyOperation);

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

		int _addressingMode;
		bool _hasLiterals;

		/**
		 * The data for the operations.
		 * NOTE: no need to explicitly call the
		 * delete operation on this because
		 * it can still live outside this object.
		 * When the AssemblyOperationTable is
		 * destroyed is when this should be deleted
		 * not before.
		 */
		AssemblyOperation* _assemblyOperation;

};

#endif
