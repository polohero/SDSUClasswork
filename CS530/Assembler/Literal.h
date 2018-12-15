/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The Literal is an
 * instruction to tell the assembler
 * about a specific literal.
 ******************************************/
#ifndef LITERAL_H
#define LITERAL_H

#include <string>
#include "SourceCodeLine.h"

class Literal
{
	public:
		Literal(
			SourceCodeLine firstLine);

		Literal(){}

		static const int CHAR;
		static const int INT;
		static const int HEX;

		/**
		 * Returns a string representation of
		 * the instruction.
		 **/
		std::string ToString();
		/**
		 * Returns the length the instruction
		 * will take up in the object file.
		 **/
		int GetLength();
		/**
		 * Returns the type of the instruction.
		 **/
		std::string GetInstructionType();
		/**
		 * Returns the object code for
		 * the instruction.
		 **/
		std::string GetObjectCode();

		int GetLocation();
		void SetLocation(int location);

		bool HasBeenPooled();
		void SetHasBeenPooled(bool hasBeenPooled);

		int GetLiteralType();
		std::string GetLiteralString();

		SourceCodeLine GetSourceCodeLine();


	private:
		bool _hasBeenPooled;
		std::string _literalString;
		int _literalType;

		SourceCodeLine _line;

		std::string _hexCharacters;
		std::string _characters;
		int _integer;
		int _location;
};

#endif
