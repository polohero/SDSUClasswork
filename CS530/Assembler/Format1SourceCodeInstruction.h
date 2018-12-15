/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Format1SourceCodeInstruction is
 * a single byte instruction. It only
 * contains the OP code, and does not have
 * any operands.
 ******************************************/
#ifndef FORMATONESOURCECODEINSTRUCTION_H
#define FORMATONESOURCECODEINSTRUCTION_H

#include <string>
#include "AssemblyOperation.h"
#include "SourceCodeLine.h"
#include "SourceCodeInstruction.h"
#include "ModificationRecords.h"

class Format1SourceCodeInstruction : public SourceCodeInstruction
{
	public:
		Format1SourceCodeInstruction(
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
