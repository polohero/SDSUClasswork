using namespace std;

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "DataConverter.h"
#include "FileHelper.h"
#include "Page.h"
#include "PageTable.h"

#include "PageReplacementAlgorithm.h"
#include "Fifo.h"
#include "LRU.h"
#include "Clock.h"
#include "Optimal.h"
#include "SecondChanceFifo.h"


#define PAGE_FILE "pages.txt"
#define SPACE ' '

/********************** Main ***********************/
/**
 * The main program. This will excute the
 * entire Assignment 2 application.
 */
int main()
{
	// Read in the number of frames.
	cout << "Enter the number of frames: " << endl;
	int numberOfFrames;
	cin >> numberOfFrames;

	// Read in the first line from the pages.txt file
	// and split it so we have an array of integers.
	string pagesString = FileHelper::PeakLine(PAGE_FILE);
	vector<int> pages = DataConverter::SplitStringToInts(pagesString, SPACE);

	// Create an array of each of the page replacement
	// algorithms that we want to run.
	vector<PageReplacementAlgorithm*> algorithms;
	algorithms.push_back(new Fifo(pages, numberOfFrames));
	algorithms.push_back(new SecondChanceFifo(pages, numberOfFrames));
	algorithms.push_back(new LRU(pages, numberOfFrames));
	algorithms.push_back(new Clock(pages, numberOfFrames));
	algorithms.push_back(new Optimal(pages, numberOfFrames));


	// Loop through each algorithm and simulate
	// the page lookups for each algorithm.
	// As an enhancement the inner loop can have
	// a thread that is kicked off and run each
	// algorithm in parallel.
	for(int i = 0; i < algorithms.size(); i++)
	{
		PageReplacementAlgorithm* algorithm = algorithms[i];

		for(int j = 0; j < pages.size(); j++)
		{
			int page = pages[j];

			algorithm->DoIt(page);
			cout << page << " " ;
		}

		cout << endl << algorithm->Name() << ": Number of Page Faults: " << algorithm->NumberOfFaults() << endl << endl;

	}


	return 0;
}


/********************** Method Implmentations ***********************/



