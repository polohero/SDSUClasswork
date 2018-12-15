
using namespace std;

#include <vector>
#include <sstream>
#include <iostream>
#include "Fifo.h"
#include "PageReplacementAlgorithm.h"

Fifo::Fifo(vector<int> pages, int numberOfFrames)
	: PageReplacementAlgorithm(pages, numberOfFrames)
{

}

string Fifo::Name()
{
	return "Fifo";
}


void Fifo::DoIt(int pageID)
{
	if( true == _table.Exists(pageID) )
	{
		return;
	}

	// We know for sure that we're going to need
	// a page fault here.
	pageFault();

	// If we're maxed out on size, then we
	// need to remove the first one, as well
	// as remove it from the page table.
	if( _table.Size() == NumberOfFrames() )
	{
		_table.Remove(removeFront());
	}

	// Then add it back.
	pushBack(pageID);
	_table.Add(Page(pageID));
}


void Fifo::pushBack(int pageID)
{
	_pageQueue.push_back(pageID);
}

int Fifo::removeFront()
{
	int front = _pageQueue.front();

	_pageQueue.erase(_pageQueue.begin());

	return front;
}
