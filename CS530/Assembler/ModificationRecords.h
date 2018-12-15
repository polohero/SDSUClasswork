/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ModificationRecords represents a
 * list of modification records.
 ******************************************/
#ifndef MODIFICATIONRECORDS_H
#define MODIFICATIONRECORDS_H

#include <vector>
#include "ModificationRecord.h"

class ModificationRecords
{
	public:
		ModificationRecord Get(int index);
		/**
		 * Adds a modification record to
		 * the list.
		 */
		void Add(ModificationRecord record);
		/**
		 * Returns the size of the array.
		 */
		int Size();

	private:
		std::vector<ModificationRecord> _records;
};

#endif
