#include <map>
#include "Memory.h"

using namespace std;

int Memory::Get(int targetAddress)
{
	memory_map::iterator i = _memory.find(targetAddress);

	return i->second;
}

void Memory::Insert(int targetAddress, int data)
{
	_memory.insert(memory_pair(targetAddress, data));
}
