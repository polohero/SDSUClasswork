#ifndef LRU_H
#define LRU_H

#include <vector>
#include <string>
#include "PageReplacementAlgorithm.h"

/**
 * The LRU PageReplacementAlgorithm handles
 * the logic of running a LRU page replacement
 * on the pages passed in.
 */
class LRU : public PageReplacementAlgorithm
{
	public:
		/**
		 * The constructor for an LRU;
		 */
		LRU (std::vector<int> pages, int numberOfFrames);

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
		void moveToBack(int pageID);
};

#endif
