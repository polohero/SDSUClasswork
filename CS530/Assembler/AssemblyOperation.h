/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The AssemblyOperation class contains all the
 * information for a specific assembly command.
 ******************************************/
#ifndef ASSEMBLYOPERATION_H
#define ASSEMBLYOPERATION_H

#include <string>

class AssemblyOperation
{
	public:
		/**
		 * The constructor for an assembly operation.
		 * @param opcode The op code the symbolizes this operation.
		 * @param mnemonic The text version of the command
		 *        (example LDA).
		 * @param format The format of the operation (meta data).
		 * @param effect The effect of the operation (meta data).
		 * @param notes The notes of the operation (meta data).
		 * @param example The example of the operation (meta data).
		 */
		AssemblyOperation(
			std::string opcode,
			std::string mnemonic,
			std::string format,
			std::string effect,
			std::string notes,
			std::string example);

		static const std::string FORMAT_0;
		static const std::string FORMAT_1;
		static const std::string FORMAT_2;
		static const std::string FORMAT_3;
		static const std::string FORMAT_4;

		/**
		 * The deafult constructor for an assembly operation.
		 */
		AssemblyOperation(){}

		/**
		 * Compares if the Assembly operations are
		 * the same.
		 */
		bool Compare(AssemblyOperation other);

		/**
		 * == operator. Compares the OpCode.
		 * @param other The other AssemblyOperation to compare.
		 * @return true or false.
		 */
		bool operator ==(AssemblyOperation other);

		/**
		 * Returns the ops code for this operation.
		 * @return The ops code.
		 */
		std::string GetOpCode();
		/**
		 * Returns the Mnemonic for this operation.
		 * @return The Mnemonic.
		 */
		std::string GetMnemonic();
		/**
		 * Returns the Format for this operation.
		 * @return The Format.
		 */
		std::string GetFormat();
		/**
		 * Returns the Effect for this operation.
		 * @return The Effect.
		 */
		std::string GetEffect();
		/**
		 * Returns the Notes for this operation.
		 * @return The Notes.
		 */
		std::string GetNotes();
		/**
		 * Returns the Example for this operation.
		 * @return The Example.
		 */
		std::string GetExample();

		/**
		 * Returns the number of formats that are available for
		 * this operation.
		 * @return The number of formats.
		 */
		int NumberOfFormatsPossible();



	private:
		std::string _opcode;
		std::string _example;
		std::string _mnemonic;
		std::string _format;
		std::string _effect;
		std::string _notes;
};

#endif
