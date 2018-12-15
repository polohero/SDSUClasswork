
using namespace std;

#include <vector>
#include <sstream>
#include <iostream>
#include "SecondChanceFifo.h"
#include "PageReplacementAlgorithm.h"

SecondChanceFifo::SecondChanceFifo(vector<int> pages, int numberOfFrames)
	: PageReplacementAlgorithm(pages, numberOfFrames)
{

}

string SecondChanceFifo::Name()
{
	return "SecondChanceFifo";
}


void SecondChanceFifo::DoIt(int pageID)
{
	if( true == _table.Exists(pageID) )
	{
		Page page = _table.Get(pageID);
		page.SetRBit( true );
		_table.Remove( pageID );
		_table.Add( page );
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
		_table.Remove(remove());
	}

	// Then add it back.
	pushBack(pageID);
	_table.Add(Page(pageID));
}


void SecondChanceFifo::pushBack(int pageID)
{
	_pageQueue.push_back(pageID);
}

int SecondChanceFifo::remove()
{
	int removedPage = -1;

	for(int i = 0; i < _pageQueue.size(); i++ )
	{
		Page page = _table.Get( _pageQueue[ i ] );
		if( false == page.GetRBit() )
		{
			removedPage = _pageQueue[ i ];
			_pageQueue.erase(_pageQueue.begin() + i);
			return removedPage;
		}
		else
		{
			page.SetRBit( false );
			_table.Remove(_pageQueue[ i ] );
			_table.Add( page );
		}
	}

	for(int i = 0; i < _pageQueue.size(); i++ )
	{
		Page page = _table.Get( _pageQueue[ i ] );
		if( false == page.GetRBit() )
		{
			removedPage = _pageQueue[ i ];
			_pageQueue.erase(_pageQueue.begin() + i);
			return removedPage;
		}
	}

	throw "This will never hit.";
}
