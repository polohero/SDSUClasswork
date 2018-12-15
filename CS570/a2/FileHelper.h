#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <string>


/**
 * A static class that helps with file manipulations.
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
		/**
		 * Reads the first line of the file.
	 	 */
		static std::string PeakLine(std::string fileName);

};

#endif
