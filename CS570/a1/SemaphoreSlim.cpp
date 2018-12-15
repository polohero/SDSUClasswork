using namespace std;

#include <sys/types.h>
#include <semaphore.h>
#include "SemaphoreSlim.h"

#define DEFAULT_COUNT 1


SemaphoreSlim::SemaphoreSlim(int count)
{
	_count = count;
	initialize();
}

SemaphoreSlim::SemaphoreSlim()
{
	_count = DEFAULT_COUNT;
	initialize();
}

SemaphoreSlim::~SemaphoreSlim()
{
	destroy();
}

void SemaphoreSlim::initialize()
{
	sem_init(&_semaphore, 0, _count);
}

void SemaphoreSlim::destroy()
{
	sem_destroy(&_semaphore);
}

void SemaphoreSlim::Destroy()
{
	destroy();
}



void SemaphoreSlim::Wait()
{
	sem_wait(&_semaphore);
}

void SemaphoreSlim::Release()
{
	sem_post(&_semaphore);
}

int SemaphoreSlim::Count()
{
	return _count;
}





