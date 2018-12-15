
using namespace std;

#include <vector>
#include <sstream>
#include <iostream>
#include "Clock.h"
#include "PageReplacementAlgorithm.h"

#define NOTHING -1

Clock::Clock(vector<int> pages, int numberOfFrames)
	: PageReplacementAlgorithm(pages, numberOfFrames)
{
	_clockPointer = 0;

	for(int i = 0; i < NumberOfFrames(); i++)
	{
		_clock.push_back( ClockNode( NOTHING ) );
	}
}

string Clock::Name()
{
	return "Clock";
}

void Clock::setFlag(int pageID)
{
	for(int i = 0; i < _clock.size(); i++)
	{
		ClockNode node = _clock[i];

		if( node.PageID() == pageID )
		{
			node.SetFlag( true );
			// Reset the pointer to the selected node.
			// and increment the pointer to the next
			// one.
			_clockPointer = i;
			incrementPointer();
			break;
		}
	}
}

void Clock::replaceWith(int pageID)
{
	while( true )
	{
		// If there is a node that can be
		// evicted, then remove it, and replace
		// it with the current one.
		if( _clock[ _clockPointer ].Flag() == false )
		{
			_table.Remove(_clock[ _clockPointer ].PageID());

			_table.Add(Page(pageID));
			_clock[ _clockPointer ].SetPageID(pageID);
			_clock[ _clockPointer ].SetFlag( true );
			incrementPointer();
			break;

		}
		// Otherwise, set the flag to false
		// and move on.
		else
		{
			_clock[ _clockPointer ].SetFlag( false );
			incrementPointer();
		}

	}
}

void Clock::incrementPointer()
{
	// If we reached the end of the frames.
	// start back over at 0.
	if( ( _clockPointer + 1 )  >= NumberOfFrames() )
	{
		_clockPointer = 0;
	}
	else
	{
		_clockPointer++;
	}
}

void Clock::DoIt(int pageID)
{
	// If the page already exists we need
	// to set the flag for this page and
	// move the pointer.
	if( true == _table.Exists(pageID) )
	{
		setFlag(pageID);
		return;
	}

	pageFault();

	// If we're maxed out on size, then we
	// need to remove the first one, as well
	// as remove it from the page table.
	if( _table.Size() >= NumberOfFrames() )
	{
		// Replace an item in the clock with
		// this page ID.
		replaceWith(pageID);
	}
	else
	{
		// Find an open spot in the clock.
		// We know that there must be an open
		// spot somewhere because of the size
		// check above.
		for(int i = 0; i < _clock.size(); i++)
		{
			if( NOTHING == _clock[ i ].PageID() )
			{
				// Set the clock pointer
				// to the open spot.
				_clockPointer = i;
				break;
			}
		}

		// Add the page to the clock and
		// increment the counter.
		_clock[ _clockPointer ].SetPageID( pageID );
		_clock[ _clockPointer ].SetFlag( true );
		_table.Add(Page(pageID));
		incrementPointer();
	}
}
