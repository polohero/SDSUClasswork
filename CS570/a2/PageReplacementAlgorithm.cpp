#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "PageTable.h"
#include "PageReplacementAlgorithm.h"

using namespace std;

PageReplacementAlgorithm::PageReplacementAlgorithm (std::vector<int> pages, int numberOfFrames)
{
	_pages = pages;
	_numberOfFaults = 0;
	_numberOfFrames = numberOfFrames;
}

int PageReplacementAlgorithm::NumberOfFaults()
{
	return _numberOfFaults;
}

int PageReplacementAlgorithm::NumberOfFrames()
{
	return _numberOfFrames;
}

void PageReplacementAlgorithm::DoIt(int pageID)
{

}

string PageReplacementAlgorithm::Name()
{
	return "PageReplacementAlgorithm";
}

void PageReplacementAlgorithm::pageFault()
{
	_numberOfFaults++;
}
