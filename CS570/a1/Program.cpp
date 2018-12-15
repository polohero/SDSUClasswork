using namespace std;

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <process.h>
#include "Thread.h"
#include "Delegate.h"
#include "DataConverter.h"
#include "SemaphoreSlim.h"
#include "FileHelper.h"

#define THREAD_COUNT 6
#define EVEN_THREAD_SLEEP 2000
#define ODD_THREAD_SLEEP 3000
#define SHARED "SHARED.txt"

/********************** Data Types ***********************/
/**
 * A structure to pass data to the thread.
 */
struct thread_data
{
	string name;
	int sleepTime;
};

/********************** Member Variables ***********************/
/**
 * Global semaphore variable that is used to sync up the
 * threads and prevent file collisions.
 */
SemaphoreSlim SEM;

/********************** Method Declarations ***********************/
/**
 * Writes the data to the SHARED file and
 * the console.
 */
void writeThreadData(thread_data data);
/**
 * Handles the logic required for
 * running the threads.
 */
void* run(void* x);
/**
 * Logs the pid information in the
 * SHARED file.
 */
void logPid();

/**
 * Creates the delegate that is passed
 * to the thread to run.
 */
Delegate createDelegate(int i, string id);

/**
 * Starts all of the threads.
 */
void startThreads(Thread threads[], int length);
/**
 * Joins all of the threads to the main thread.
 */
void joinThreads(Thread threads[], int length);


/********************** Main ***********************/
/**
 * The main program. This will excute the
 * entire Assignment 1 application.
 */
int main()
{
	// First check if the file already exists.
	// If it does, delete it.
	if( true == FileHelper::Exists(SHARED))
	{
		FileHelper::Delete(SHARED);
	}

	logPid();

	Thread threads[ THREAD_COUNT ];

	
tartThreads(threads, THREAD_COUNT);

	joinThreads(threads, THREAD_COUNT);

	return 0;
}


/********************** Method Implmentations ***********************/
/**
 * Logs the pid information into the SHARED
 * file.
 */
void logPid()
{
	// Format a message to ouput
	string pidMessage =
		string("Process ID: ") +
		DataConverter::GetIntToString(_getpid());

	FileHelper::WriteLine(SHARED, pidMessage);
}

/**
 * Loops through all of the threads and
 * starts them up.
 */
void startThreads(Thread threads[], int length)
{
	for(int i = 0; i < length; i++)
	{
		string threadName =
			string(
				DataConverter::GetIntToString(i).c_str());
		Delegate delegate = createDelegate(i, threadName);

		Thread thread = Thread(delegate, threadName);
		thread.Start();

		threads[ i ] = thread;
	}
}

/**
 * Creates the delegate that is used to
 * start the threads.
 */
Delegate createDelegate(int i, string name)
{
	Delegate delegate;

	thread_data *data = new thread_data();
	data->name = name;

	if( i % 2 == 0 )
	{
		data->sleepTime = EVEN_THREAD_SLEEP;
	}
	else
	{
		data->sleepTime = ODD_THREAD_SLEEP;
	}

	delegate = Delegate(run, data);

	return delegate;
}

/**
 * Orchestration method for each thread.
 */
void* run(void* x)
{
	thread_data data = *(thread_data *)x;

	for(int i = 0; i < 10; i++)
	{
		writeThreadData(data);
		Sleep(data.sleepTime);
	}

    return 0;
}

/**
 * Prints out the thread data to the console
 * and the file.
 */
void writeThreadData(thread_data data)
{
	SEM.Wait();

	FileHelper::WriteLine(SHARED, data.name);
	cout << "Thread " << data.name << " is running " << endl;

	SEM.Release();
}

/**
 * Loops through all of the threads and
 * joins them to the currentl thread.
 */
void joinThreads(Thread threads[], int length)
{
	for(int i = 0; i < length; i++)
	{
		Thread::Join(threads[i]);
	}
}


