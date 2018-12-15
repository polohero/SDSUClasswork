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

string DataConverter::GetHexStringFromBinaryString (string binaryString)
{
	string returnString = "";

	for(int i = 0; i< binaryString.length(); i+=4 )
	{
		string oneBinaryString = binaryString.substr(i, 4);

		if(oneBinaryString.compare(string("0000")) == 0){returnString += "0";}
		else if(oneBinaryString.compare(string("0001")) == 0){returnString += "1";}
		else if(oneBinaryString.compare(string("0010")) == 0){returnString += "2";}
		else if(oneBinaryString.compare(string("0011")) == 0){returnString += "3";}
		else if(oneBinaryString.compare(string("0100")) == 0){returnString += "4";}
		else if(oneBinaryString.compare(string("0101")) == 0){returnString += "5";}
		else if(oneBinaryString.compare(string("0110")) == 0){returnString += "6";}
		else if(oneBinaryString.compare(string("0111")) == 0){returnString += "7";}
		else if(oneBinaryString.compare(string("1000")) == 0){returnString += "8";}
		else if(oneBinaryString.compare(string("1001")) == 0){returnString += "9";}
		else if(oneBinaryString.compare(string("1010")) == 0){returnString += "A";}
		else if(oneBinaryString.compare(string("1011")) == 0){returnString += "B";}
		else if(oneBinaryString.compare(string("1100")) == 0){returnString += "C";}
		else if(oneBinaryString.compare(string("1101")) == 0){returnString += "D";}
		else if(oneBinaryString.compare(string("1110")) == 0){returnString += "E";}
		else if(oneBinaryString.compare(string("1111")) == 0){returnString += "F";}
	}

	return returnString;
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
	string hexString = sstream.str();

	for(int i = 0; i < hexString.length(); i++)
	{
		hexString[i] = toupper(hexString[i]);
	}

	return hexString;
}


string DataConverter::Trim(string strToTrim)
{
	string str = strToTrim;

  string::size_type pos = str.find_last_not_of(' ');
  if(pos != string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(' ');
    if(pos != string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());

  return str;
}

string DataConverter::PadRight(string str, int num, char paddingChar)
{
	if(str.length() >= num)
	{
		return str;
	}

	for(int i = str.length(); i < num; i++)
	{
		str += paddingChar;
	}

	return str;
}

string DataConverter::PadLeft(string str, int num, const char paddingChar)
{
	if(num > str.size())
		str.insert(0, num - str.size(), paddingChar);

	return str;
}

/**
 *UNIT TESTS
 * g++ DataConverter.cpp
 */
/*
int main()
{

	string trimer = "  trim  ";

	cout << trimer << endl;

	string trimmed = DataConverter::Trim(trimer);

	cout << trimmed << endl;

	cout << trimmed.length() << endl;

	string padder = string("123");

	string padded = DataConverter::PadLeft(padder, 10, '0');

	cout << padded << endl;

	cout << DataConverter::PadRight(padder, 10, 'A') << endl;
	cout << DataConverter::PadRight(padder, 2, 'A') << endl;
	cout << DataConverter::PadRight(padder, 3, 'A') << endl;
	cout << DataConverter::PadRight(padder, 4, 'A') << endl;

	cout << DataConverter::ConvertIntToHex(-10) << endl;
	cout << DataConverter::ConvertIntToHex(10) << endl;

	int r = 0;

	cin >> r;

	return 1;
}


*/
