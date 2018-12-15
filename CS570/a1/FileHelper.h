#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <string>


/**
 * A single lock is a locking object that will only allow
 * a single thread to go through a section of code.
 */
class FileHelper
{
	public:
		/**
		 * Writes a single line in a file.
	 	 */
		static bool WriteLine(std::string fileName, std::string text);
		/**
		 * Checks to see if a file exists.
	 	 */
		static bool Exists(std::string fileName);
		/**
		 * Deletes a file from disk.
	 	 */
		static void Delete(std::string fileName);

};

#endif
