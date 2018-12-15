#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <map>
#include <vector>
#include "Page.h"

typedef std::map<int, Page> assembly_map;
typedef std::pair<int, Page> assembly_pair;

/**
 * A page table represents a list of pages currently
 * loaded into memory. It uses a dictionary lookup
 * based on a integer pageid.
 */
class PageTable
{
	public:
		PageTable();
		Page Get(int pageID);
		void Add(Page page);
		void Remove(int pageID);
		bool Exists(int pageID);
		int Size();
		std::vector<int> GetPages();

	private:
		assembly_map _hash;

};

#endif

