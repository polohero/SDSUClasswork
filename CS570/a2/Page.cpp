using namespace std;
#include <string>

#include "Page.h"
#include "DataConverter.h"


Page::Page(int id)
{
	_id = id;
	_rBit = false;
}

int Page::GetID()
{
	return _id;
}

void Page::SetID(int id)
{
	_id = id;
}

bool Page::GetRBit()
{
	return _rBit;
}

void Page::SetRBit(bool rBit)
{
	_rBit = rBit;
}


std::string Page::ToString()
{
	return DataConverter::GetIntToString(GetID());
}
