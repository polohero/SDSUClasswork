/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ObjectCodeFormatter is in charge of
 * formatting the object code for a specific
 * source file. It will perform the Pass 2
 * logic where the parsed source code turns into
 * object code.
 ******************************************/
#ifndef OBJECTCODEFORMATTER_H
#define OBJECTCODEFORMATTER_H

#include <string>
#include "SourceCodeFile.h"
#include "SourceCodeInstruction.h"

class ObjectCodeFormatter
{
	public:
		/*
		 * Formats a source code file, and returns
		 * the object code.
		 */
		std::string FormatFile(SourceCodeFile* file);
		/*
		 * Returns any error messages that have occured
		 * as a result of formating the source file.
		 */
		std::string GetErrorMessages();

	private:
		void validate(SourceCodeFile* file);
		std::string formatFile(SourceCodeFile* file);
		std::string _errorMessages;
		void handleErrorMessages(char const* errorMessage, int line);

};

#endif

