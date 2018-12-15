#ifndef CLOCKNODE_H
#define CLOCKNODE_H

/**
 * A clock node is a node in a clock
 * paging algorithm.
 */
class ClockNode
{
	public:
		/**
		 * The constructor for an ClockNode;
		 */
		ClockNode (int pageID);

		int PageID();
		void SetPageID( int pageID);
		bool Flag();
		void SetFlag(bool flag);

	private:
		int _pageID;
		bool _flag;
};

#endif
