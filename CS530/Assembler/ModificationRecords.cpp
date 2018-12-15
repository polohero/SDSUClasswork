/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ModificationRecords represents a
 * list of modification records.
 ******************************************/
#include <vector>
#include "ModificationRecord.h"
#include "ModificationRecords.h"

ModificationRecord ModificationRecords::Get(int index)
{
	return _records[index];
}

int ModificationRecords::Size()
{
	return _records.size();
}

void ModificationRecords::Add(ModificationRecord record)
{
	_records.push_back(record);
}
