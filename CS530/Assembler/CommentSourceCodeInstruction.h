/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The CommentSourceCodeInstruction is a
 * specific instruction that is essentially
 * a skip instruction. There is nothing that
 * happens because of a comment. We chose
 * this route instead of just ignoring the
 * lines because we could then include
 * comments in a debugging intermidate file
 * if needed.
 ******************************************/
#ifndef COMMENTSOURCECODEINSTRUCTION_H
#define COMMENTSOURCECODEINSTRUCTION_H

#include <string>
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"

class CommentSourceCodeInstruction : public SourceCodeInstruction
{
	public:
		/**
		 * Constructior. All it takes is
		 * a line of source code.
		 */
		CommentSourceCodeInstruction(
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
