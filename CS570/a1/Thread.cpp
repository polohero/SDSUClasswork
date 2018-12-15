using namespace std;
#include "Thread.h"
#include "Delegate.h"
#include <pthread.h>
#include <string>
#include <sstream>

#define EMPTY ""
#define SUCCESS 0

Thread::Thread()
{

}

Thread::Thread(Delegate function)
{
	_function = function;
	_name = string(EMPTY);
}

Thread::Thread(Delegate function, string name)
{
	_function = function;
	_name = name;
}

void Thread::Start()
{
	int result =
		pthread_create(
			&_thread,
			NULL,
			_function.GetFunction(),
			_function.GetArgument());

	if( SUCCESS != result )
	{
		throw "Thread creation failed at pthread_create.";
	}
}

void Thread::Join(pthread_t thread)
{
	pthread_join(thread, NULL);

}

void Thread::Join(Thread thread)
{
	Thread::Join(thread.id());
}

void Thread::Exit()
{
	pthread_exit(NULL);
}
string Thread::GetCurrentThreadID()
{
	pthread_t thread = pthread_self();
	return Thread::getID(thread);
}


string Thread::Name()
{
	return _name;
}

pthread_t Thread::id()
{
	return _thread;
}


string Thread::ID()
{
	return Thread::getID(_thread);
}


string Thread::getID(pthread_t thread)
{
	stringstream ss;
	ss <<  thread;
	return ss.str();
}

/* Windows
string Thread::getID(pthread_t thread)
{
	// NOTE: This is currently not the thread ID
	// I am unsure how to get the actual TID
	// or if it's needed for the project.
	stringstream ss;
	ss <<  &thread;
	return ss.str();
}
*/


