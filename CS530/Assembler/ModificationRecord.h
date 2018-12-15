/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ModificationRecord represents a
 * single modification record.
 ******************************************/
#ifndef MODIFICATIONRECORD_H
#define MODIFICATIONRECORD_H

class ModificationRecord
{
	public:
		ModificationRecord(int location, int length);
		/**
		 * Returns the location of the mod records.
		 */
		int GetLocation();
		/**
		 * Returns the length of the mod records.
		 */
		int GetLength();

	private:
		int _location;
		int _length;
};

#endif
