/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ModificationRecord represents a
 * single modification record.
 ******************************************/
#include "ModificationRecord.h"

ModificationRecord::ModificationRecord(int location, int length)
{
	_location = location;
	_length = length;
}

int ModificationRecord::GetLocation(){return _location;}
int ModificationRecord::GetLength(){return _length;}
