#include <map>
#include <vector>
#include "Page.h"
#include "PageTable.h"

using namespace std;


PageTable::PageTable()
{

}

vector<int> PageTable::GetPages()
{
	vector<int> pages;

	for(std::map<int,Page>::iterator iter = _hash.begin(); iter != _hash.end(); ++iter)
	{
		pages.push_back(iter->first);
	}
	return pages;
}

/**
 * Checks if the page exists in the table already.
 */
bool PageTable::Exists(int pageID)
{
	assembly_map::iterator i = _hash.find(pageID);

	return i != _hash.end();
}

/**
 * Currently this method will not allow an invalid
 * PageID to be passed. You will need to call exists
 * first.
 */
Page PageTable::Get(int pageID)
{
	assembly_map::iterator i = _hash.find(pageID);

	return i->second;
}

/**
 * Inserts a page into the table.
 */
void PageTable::Add(Page page)
{
	_hash.insert(assembly_pair(page.GetID(), page));
}

/**
 * Removes a page from the table.
 */
void PageTable::Remove(int pageID)
{
	_hash.erase(pageID);
}

int PageTable::Size()
{
	_hash.size();
}
