#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <string>
#include "Delegate.h"

/**
 * The Thread class is a class that will
 * handle multi threading operations.
 */
class Thread
{
	public:
		/**
		 * Constructors. This will initialize the thread
		 * but will not start the thread running yet.
		 */
		Thread();
		Thread(Delegate starter);
		Thread(Delegate starter, std::string name);

		/**
		 * Start running the thread.
		 */
		void Start();

		/**
		 * Returns the name of the thread.
		 */
		std::string Name();
		/**
		 * Returns the thread id of the thread.
		 */
		std::string ID();
		/**
		 * Exits the calling thread.
		 */
		static void Exit();

		/**
		 * Joins the calling thread with the POSIX thread
		 * passed in.
		 */
		static void Join(Thread thread);
		/**
		 * Returns the thread id of the currently running thread.
		 */
		static std::string GetCurrentThreadID();

	private:
		/**
		 * The function being threaded.
		 */
		Delegate _function;
		/**
		 * The POSIX thread.
		 */
		pthread_t _thread;
		/**
		 * The name of the thread.
		 */
		std::string _name;
		/**
		 * Joins the calling thread with the POSIX thread
		 * passed in.
		 */
		static void Join(pthread_t thread);
		/**
		 * Returns the current POSIX thread for the
		 * thread class.
		 */
		pthread_t id();
		/**
		 * Converts the pthread_t into a string for the ID.
		 */
		static std::string getID(pthread_t thread);

};

#endif
