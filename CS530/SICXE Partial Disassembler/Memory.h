#ifndef MEMORY_H
#define MEMORY_H

#include <map>

typedef std::map<int, int> memory_map;
typedef std::pair<int, int> memory_pair;

/**
 * The memory class represents all the data
 * stored in memory.
 */
class Memory
{
	public:
		/**
		 * Looks up the data in memory based on the TA.
		 * @param targetAddress The TA to lookup.
		 */
		int Get(int targetAddress);
		/**
		 * Inserts data into the memory location.
		 * @param targetAddress The address to insert the memory.
		 * @param data The data to insert.
		 */
		void Insert(int targetAddress, int data);

	private:
		memory_map _memory;
		int _loaded;

};


#endif
