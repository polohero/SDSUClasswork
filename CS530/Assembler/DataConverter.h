/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The DataConverter is a helper utility
 * that will convert between hex, int, and
 * binary in order to help us process the
 * instructions.
 ******************************************/
#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <string>
#include <ctype.h>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

/* static */ class DataConverter
{

	public:
		/**
		 * Converts a HEX string into it's integer value.
		 * Example: "F" becomes 15.Pieces of the code
		 * have been taken from
		 * http://www.cplusplus.com/forum/beginner/42422/.
		 * @param t The address to put the converted int.
		 * @param s The string to convert.
		 * @param f The base to be converted to. (HEX).
		 * @return Whether the conversion was successful or not.
		 */
		static bool ConvertToIntFromHexString(
				int& t,
			    const std::string& s,
			    std::ios_base& (*f)(std::ios_base&));

		/**
		 * Converts to a hex string from a binary string.
		 * @param binaryString The string to convert.
		 * @return The converted string.
		 */
		static std::string GetHexStringFromBinaryString (std::string  binaryString);

		/**
		 * Converts a HEX string into it's binary representation.
		 * Example: "F0" becomes "11110000". Pieces of code have
		 * been taken from:
		 * http://www.cplusplus.com/forum/beginner/41657/.
		 * @param hexString The string to convert.
		 * @return The binary string.
		 */
		static std::string GetBinaryStringFromHexString (std::string hexString);

		/**
		 * Converts a HEX CHAR into it's binary representation.
		 * Example: "F" becomes "1111". Pieces of code have
		 * been taken from:
		 * http://www.cplusplus.com/forum/beginner/41657/.
		 * @param hexChar The char to convert.
		 * @return The binary string.
		 */
		static std::string GetBinaryStringFromHexChar (char hexChar);

		/**
		 * Converts a binary string to an integer.
		 * Example: "1111".becomes 15. Pieces of code have
		 * been taken from:
		 * http://www.cplusplus.com/forum/beginner/41657/.
		 * @param binaryString The binary string.
		 * @return The integer value of that string.
		 */
		static int GetIntFromBinaryString (std::string binaryString);

		/**
		 * Gets a single nibble from a string at the index.
		 * The string is passed in HEX notation.
		 * Example: index= 2, "ABCD" returns "1100", because C is
		 * at index of 2. and it converts it to binary.
		 * @param index The index to pull out of the hex string.
		 * @param instruction The full instruction.
		 * @return A binary string (nibble).
		 */
		static std::string GetNibble(int index, std::string instruction);

		/**
		 * Gets a series of nibbles from a string at the index.
		 * The string is passed in HEX notation.
		 * Example: startIndex= 1,endIndex=2 , "ABCD" returns "10111100",
		 * because B=1011 AND C= 1100.
		 * @param startIndex The starting index to pull out of the hex string.
		 * @param endIndex The ending index to pull out of the hex string.
		 * @param instruction The full instruction.
		 * @return A binary string (nibbles).
		 */
		static std::string GetNibbles(int startIndex, int endIndex, std::string instruction);

		/**
		 * Converts an int to a string.
		 * @param number The integer to convert.
		 * @return The string of the int.
		 */
		static std::string GetIntToString(int number);

		/**
		 * Converts a string to an int.
		 * @param str The string to convert.
		 * @return The int of the string.
		 */
		static int GetStringToInt(std::string str);

		/**
		 * Gets a string from a boolean value.
		 * Example: "true" becomes "1".
		 * @param flag The flag to convert.
		 * @return The string value.
		 */
		static std::string GetStringFromBool(bool flag);

		/**
		 * Gets a boolean from a char value.
		 * Example: "1" becomes "true".
		 * @param flag The flag to convert.
		 * @return The char value.
		 */
		static bool GetBoolFromChar(char flag);

		/**
		 * Converts to a hex string from an int.
		 * @param i The int to convert.
		 * @return The converted string.
		 */
		static std::string ConvertIntToHex(int i);


		/**
		 * Trims the left and right side of a string.
		 * Taken from:
		 * http://www.codeproject.com/Articles/10880/A-trim-implementation-for-std-string
		 * @param s The string to trim.
		 * @return The trimmed string.
		 */
		static std::string Trim(std::string strToTrim);


		/**
		 * Pads to the left of a string.
		 * Taken from:
		 * http://stackoverflow.com/questions/667183/padding-stl-strings-in-c
		 * @param str The string to pad.
		 * @param num The number of charcters to pad.
		 * @param paddingChar The actual charcter to pad.
		 * @return The padded string.
		 */
		static std::string PadLeft(std::string str, int num, const char paddingChar);

		/**
		 * Pads to the right of a string.
		 * @param str The string to pad.
		 * @param num The number of charcters to pad.
		 * @param paddingChar The actual charcter to pad.
		 * @return The padded string.
		 */
		static std::string PadRight(std::string str, int num, char paddingChar);


};

#endif
