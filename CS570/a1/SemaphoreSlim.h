#ifndef SEMAPHORESLIM_H
#define SEMAPHORESLIM_H

#include <sys/types.h>
#include <semaphore.h>

/**
 * A semaphore implimentation that uses the
 * POSIX implementation under the hood.
 */
class SemaphoreSlim
{
	public:
		/**
		 * Constructors
		 */
		SemaphoreSlim(int count);
		SemaphoreSlim();
		~SemaphoreSlim();
		/**
		 * Waits by 1 for the semaphore to become
		 * free.
		 */
		void Wait();
		/**
		 * Releases by 1 the current semaphore.
		 */
		void Release();
		/**
		 * Returns the current number of threads
		 * the semaphore will allow.
		 */
		int Count();

		void Destroy();

	private:
		void initialize();
		sem_t _semaphore;
		int _count;
		void destroy();

};

#endif
