#ifndef SECONDCHANCEFIFO_H
#define SECONDCHANCEFIFO_H

#include <vector>
#include <string>
#include "PageReplacementAlgorithm.h"

/**
 * The SecondChanceFifo PageReplacementAlgorithm handles
 * the logic of running a Fifo page replacement
 * on the pages passed in, but it also gives
 * each page a second chance before being
 * evicted.
 */
class SecondChanceFifo : public PageReplacementAlgorithm
{
	public:
		/**
		 * The constructor for an SecondChanceFifo;
		 */
		SecondChanceFifo (std::vector<int> pages, int numberOfFrames);

		/**
		 * Performs a memory get on the page table.
		 */
		virtual void DoIt(int pageID);
		/**
		 * The name of the algorithm for printing.
		 */
		virtual std::string Name();

	private:
		void pushBack(int pageID);
		int remove();
		std::vector<int> _pageQueue;
};

#endif
