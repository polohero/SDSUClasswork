/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The SourceCodeLine is in charge of
 * parsing a single line of code into
 * it's different parts.
 ******************************************/
#ifndef SOURCECODELINE_H
#define SOURCECODELINE_H

#include <string>

class SourceCodeLine
{
	public:
		static const char COMMENT_CHARACTER;

		SourceCodeLine(
			std::string rawLine);
		SourceCodeLine(){}

		/**
		 * Returns the raw instruction line.
		 */
		std::string GetRawLine();
		/**
		 * Returns the label from the instruction.
		 */
		std::string GetLabel();
		/**
		 * Sets the label from the instruction.
		 */
		void SetLabel(std::string label);
		/**
		 * Returns the operation prefix.
		 */
		std::string GetOperationPrefix();
		/**
		 * Returns the operation.
		 */
		std::string GetOperation();
		/**
		 * Returns the operand prefix.
		 */
		std::string GetOperandPrefix();
		/**
		 * Returns the operand.
		 */
		std::string GetOperand();
		/**
		 * Returns whether or not this is a
		 * full comment line.
		 */
		bool IsCommentLine();
		/**
		 * Returns the location of the line.
		 */
		int GetLocation();
		/**
		 * Returns the length of the line.
		 */
		int GetLength();
		/**
		 * Sets the length of the line.
		 */
		void SetLength(int length);
		/**
		 * Sets the location of the line.
		 */
		void SetLocation(int location);

		bool HasLiteral();

	private:
		void parse(std::string rawLine);
		void validate(std::string rawLine);
		bool isCommentLine(std::string rawLine);
		std::string getOperand(std::string rawLine);
		void hasInvalidCharacters(std::string data, std::string message);

		bool _isCommentLine;
		int _location;
		int _length;
		std::string _rawLine;
		std::string _label;
		std::string _operationPrefix;
		std::string _operation;
		std::string _operandPrefix;
		std::string _operand;
};

#endif
