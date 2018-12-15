
using namespace std;

#include <vector>
#include <sstream>
#include <iostream>
#include "LRU.h"
#include "PageReplacementAlgorithm.h"

LRU::LRU(vector<int> pages, int numberOfFrames)
	: PageReplacementAlgorithm(pages, numberOfFrames)
{

}

string LRU::Name()
{
	return "LRU";
}

void LRU::DoIt(int pageID)
{
	// If we do a GET on this page ID
	// and it exists, it needs to move to the
	// back of the queue.
	if( true == _table.Exists(pageID) )
	{
		moveToBack(pageID);

		return;
	}

	pageFault();

	// If we're maxed out on size, then we
	// need to remove the first one, as well
	// as remove it from the page table.
	if( _table.Size() == NumberOfFrames() )
	{
		int evicted = removeFront();
		_table.Remove(evicted);
	}

	// Then add it back.
	pushBack(pageID);
	_table.Add(Page(pageID));
}

void LRU::moveToBack(int pageID)
{
	int index = 0;

	for(int i = 0; i < _pageQueue.size(); i++)
	{
		if( _pageQueue[i] == pageID )
		{
			index = i;
		}
	}

	// Remove it from whereever it currently is
	// and push it to the back of the queue
	// so it's safe from being removed for
	// awhile.
	_pageQueue.erase(_pageQueue.begin() + index);
	pushBack(pageID);
}

void LRU::pushBack(int pageID)
{
	_pageQueue.push_back(pageID);
}

int LRU::removeFront()
{
	int front = _pageQueue.front();

	_pageQueue.erase(_pageQueue.begin());

	return front;
}
