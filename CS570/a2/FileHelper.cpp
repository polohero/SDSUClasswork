using namespace std;
#include <string>
#include <iostream>
#include <fstream>

#include "FileHelper.h"

bool FileHelper::WriteLine(
	string fileName,
	string text)
{
	bool result = true;

	try
	{
		ofstream myfile (fileName.c_str(), ios_base::app);
		if (myfile.is_open())
		{
			myfile << text << endl;
			myfile.close();
		}
		else
		{
			result = false;
		}
	}
	catch( ... )
	{
		result = false;
	}

	return result;
}

string FileHelper::PeakLine(
	string fileName)
{
	bool result = true;

	string returnString;

	ifstream myfile (fileName.c_str());
	getline(myfile, returnString);
	myfile.close();

	return returnString;
}



bool FileHelper::Exists(
	string fileName)
{
 	ifstream ifile(fileName.c_str());
  	return ifile;
}

void FileHelper::Delete(
	string fileName)
{
	remove(fileName.c_str());
}
