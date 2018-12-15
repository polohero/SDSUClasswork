#ifndef OPTIMAL_H
#define OPTIMAL_H

#include <vector>
#include <string>
#include "PageReplacementAlgorithm.h"

/**
 * The optimal algorithm is a PageReplacementAlgorithm
 * that is theoretical and cannot be created in
 * a real environment.
 */
class Optimal : public PageReplacementAlgorithm
{
	public:
		/**
		 * The constructor for an Optimal;
		 */
		Optimal (std::vector<int> pages, int numberOfFrames);

		/**
		 * Performs a memory get on the page table.
		 */
		virtual void DoIt(int pageID);
		/**
		 * The name of the algorithm for printing.
		 */
		virtual std::string Name();

	private:
		void replace(int pageID);
		int _currentPage;
};

#endif
