
using namespace std;

#include <vector>
#include <sstream>
#include <iostream>
#include "Optimal.h"
#include "PageReplacementAlgorithm.h"

#define NONE -1

Optimal::Optimal(vector<int> pages, int numberOfFrames)
	: PageReplacementAlgorithm(pages, numberOfFrames)
{
	_currentPage = 0;
}

string Optimal::Name()
{
	return "Optimal";
}

void Optimal::replace(int pageID)
{
	int replacePageID;
	int replacementPointer = NONE;

	vector<int> pages = _table.GetPages();

	for(int i = 0; i < pages.size(); i++)
	{
		int page = pages[i];
		bool found = false;

		// Optimizing the algorithm to loop from
		// the last element back to the first.
		for( int j = _currentPage; j < _pages.size(); j++)
		{
			int nextPage = _pages[j];

			if( page == nextPage )
			{
				found = true;

				if( replacementPointer < j )
				{
					replacementPointer = j;
					replacePageID = nextPage;
				}
				break;
			}
		}

		// If there is something in the
		// page table that is not going to be used
		// again. We should purge that.
		if( false == found )
		{
			replacePageID = page;
			break;
		}
	}

	// If for some reason we didn't find any of them.
	// we can just replace any of them.
	if( NONE == replacementPointer )
	{
		_table.Remove(pages[0]);

	}
	// Otherwise, we know who to replace.
	else
	{
		_table.Remove(replacePageID);
	}

	_table.Add(Page(pageID));
}


void Optimal::DoIt(int pageID)
{
	_currentPage++;

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
		replace( pageID );
	}
	else
	{
		_table.Add(Page(pageID));
	}

}
