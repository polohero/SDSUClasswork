#ifndef FIFO_H
#define FIFO_H

#include <vector>
#include <string>
#include "PageReplacementAlgorithm.h"

/**
 * The Fifo PageReplacementAlgorithm handles
 * the logic of running a Fifo page replacement
 * on the pages passed in.
 */
class Fifo : public PageReplacementAlgorithm
{
	public:
		/**
		 * The constructor for an Fifo;
		 */
		Fifo (std::vector<int> pages, int numberOfFrames);

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
		int removeFront();
		std::vector<int> _pageQueue;
};

#endif
