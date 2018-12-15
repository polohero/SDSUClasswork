#ifndef PAGEREPLACEMENTALGORITHM_H
#define PAGEREPLACEMENTALGORITHM_H

#include <vector>
#include <string>
#include "PageTable.h"

/**
 * A PageReplacementAlgorithm is the base class
 * for each algorithm.
 */
class PageReplacementAlgorithm
{
	public:
		/**
		 * The constructor for an PageReplacementAlgorithm;
		 */
		PageReplacementAlgorithm (std::vector<int> pages, int numberOfFrames);
		/**
		 * Performs a memory get on the page table.
		 */
		virtual void DoIt(int pageID);
		/**
		 * The name of the algorithm for printing.
		 */
		virtual std::string Name();
		/**
		 * The current number of page faults.
		 */
		int NumberOfFaults();
		/**
		 * The current number of frames used.
		 */
		int NumberOfFrames();

	protected:

		void pageFault();
		int _numberOfFaults;
		std::vector<int> _pages;
		PageTable _table;
		int _numberOfFrames;

};

#endif
