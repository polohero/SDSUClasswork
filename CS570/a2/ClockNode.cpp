
using namespace std;

#include "ClockNode.h"

ClockNode::ClockNode(int pageID)
{
	_pageID  = pageID;
	_flag = false;
}

int ClockNode::PageID()
{
	return _pageID;
}

void ClockNode::SetPageID( int pageID )
{
	_pageID = pageID;
}

bool ClockNode::Flag()
{
	return _flag;
}

void ClockNode::SetFlag(bool flag)
{
	_flag = flag;
}
