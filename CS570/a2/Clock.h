#ifndef CLOCK_H
#define CLOCK_H

#include <vector>
#include <string>
#include "ClockNode.h"
#include "PageReplacementAlgorithm.h"

/**
 * The Clock PageReplacementAlgorithm handles
 * the logic of running a clock page replacement
 * on the pages passed in.
 */
class Clock : public PageReplacementAlgorithm
{
	public:
		/**
		 * The constructor for an Clock;
		 */
		Clock (std::vector<int> pages, int numberOfFrames);

		/**
		 * Performs a memory get on the page table.
		 */
		virtual void DoIt(int pageID);
		/**
		 * The name of the algorithm for printing.
		 */
		virtual std::string Name();

	private:
		std::vector<ClockNode> _clock;
		int _clockPointer;
		void setFlag(int pageID);
		void replaceWith(int pageID);
		void incrementPointer();
};

#endif
