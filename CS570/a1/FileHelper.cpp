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
