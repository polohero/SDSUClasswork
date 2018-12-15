#include <sstream>
#include <string>
#include <iostream>
#include <ctype.h>
#include <stdlib.h>


#include "DataConverter.h"

using namespace std;

#define FALSE_FLAG '0'
#define TRUE_FLAG '1'

bool DataConverter::ConvertToIntFromHexString(
		int& t,
		 const std::string& s,
		 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

string DataConverter::GetBinaryStringFromHexString (string hexString)
{
	string returnString = "";
	for (int i = 0; i < hexString.length (); ++i)
	{
		returnString.append (GetBinaryStringFromHexChar(hexString[i]));
	}
	return returnString;
}

string DataConverter::GetIntToString(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

string DataConverter::GetBinaryStringFromHexChar (char hexString)
{
	string returnString = "";
	switch (toupper(hexString))
			{
				case '0': returnString.append ("0000"); break;
				case '1': returnString.append ("0001"); break;
				case '2': returnString.append ("0010"); break;
				case '3': returnString.append ("0011"); break;
				case '4': returnString.append ("0100"); break;
				case '5': returnString.append ("0101"); break;
				case '6': returnString.append ("0110"); break;
				case '7': returnString.append ("0111"); break;
				case '8': returnString.append ("1000"); break;
				case '9': returnString.append ("1001"); break;
				case 'A': returnString.append ("1010"); break;
				case 'B': returnString.append ("1011"); break;
				case 'C': returnString.append ("1100"); break;
				case 'D': returnString.append ("1101"); break;
				case 'E': returnString.append ("1110"); break;
				case 'F': returnString.append ("1111"); break;
		}
	return returnString;
}

int DataConverter::GetIntFromBinaryString(string binaryString)
{
	return (int) strtol(binaryString.c_str() , 0, 2);

}

string DataConverter::GetNibble(int index, string instruction)
{
	if( index > (instruction.length() - 1) )
	{
		throw "Index is too large. Invalid operation.";
	}

	return GetBinaryStringFromHexChar(instruction[index]);
}

int DataConverter::GetStringToInt(std::string str)
{
	return atoi(str.c_str());
}

string DataConverter::GetNibbles(
	int startIndex,
	int endIndex,
	string instruction)
{
	if(startIndex< 0)
	{
		throw "startIndex cannot be negative.";
	}

	if(endIndex< 0)
	{
		throw "endIndex cannot be negative.";
	}

	if( endIndex > (instruction.length() - 1) )
	{
		throw "Index is too large.";
	}

	if(startIndex > endIndex)
	{
		throw "startIndex > endIndex.";
	}


	return GetBinaryStringFromHexString(instruction.substr(startIndex, endIndex) );
}

string DataConverter::GetStringFromBool(bool flag)
{
	if(true == flag)
	{
		return "1";
	}

	return "0";
}

bool DataConverter::GetBoolFromChar(char flag)
{
	if(flag == TRUE_FLAG)
	{
		return true;
	}

	return false;
}

string DataConverter::ConvertIntToHex(int i)
{
	std::stringstream sstream;
	sstream << std::hex << i;
	return sstream.str();
}


/**
 *UNIT TESTS
 */
/*int main()
{
	DataConverter c;

	string bin = "1A10050D";

	string val = c.GetNibbles(4, 6, bin);

	cout << bin << endl;
	cout << val << endl;

	int r = 0;

	cin >> r;
}*/


