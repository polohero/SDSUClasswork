/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SourceCodeInstruction is a base class.
 * All other instructions inherit from this
 * class. Each specific class contains
 * the logic to create the object code.
 * Methods have been stubbed out, but will not
 * be used.
 ******************************************/
#ifndef SOURCECODEINSTRUCTION_H
#define SOURCECODEINSTRUCTION_H

#include <string>

#include "SourceCodeLine.h"
#include "ModificationRecords.h"

class SourceCodeInstruction
{
	public:
		/**
		 * Enums do not seem to be as useful
		 * in C++ as they are in other OOP languages
		 * so we chose to use a const int instead.
		 * Below are the enumerations for the type
		 * of instructions that can be created.
		 */
		static const std::string NONE;
		static const std::string BYTE;
		static const std::string BASE;
		static const std::string NOBASE;
		static const std::string WORD;
		static const std::string EQU;
		static const std::string START;
		static const std::string END;
		static const std::string RESB;
		static const std::string RESW;
		static const std::string FORMAT_0;
		static const std::string FORMAT_1;
		static const std::string FORMAT_2;
		static const std::string FORMAT_3;
		static const std::string FORMAT_4;
		static const std::string COMMENT;
		static const std::string LITERAL;
		static const std::string LTORG;

		static int BASE_VALUE;

		static const int SIC_BASIC;
		static const int SIC_XE;

		SourceCodeInstruction(
			std::string line);
		SourceCodeInstruction(
			SourceCodeLine line);

		/**
		 * Returns the location of the instruction.
		 */
		int GetLocation();
		/**
		 * Sets the location of the instruction.
		 */
		void SetLocation(int location);
		/**
		 * Returns the location of the instruction.
		 */
		int GetNextLocation();
		/**
		 * Sets the location of the instruction.
		 */
		void SetNextLocation(int location);
		/**
		 * Gets the parsed source code line.
		 */
		SourceCodeLine GetSourceCodeLine();
		/**
		 * Checks if this instruction has a label.
		 */
		bool HasLabel();
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

	protected:
		SourceCodeLine _line;
		int _location;
		int _nextLocation;
};

#endif
