#ifndef DELEGATE_H
#define DELEGATE_H


typedef void* (*functionPointer) (void*);

/**
 * The Delegate class that holds a
 * pointer to a function so it can be
 * used by some other construct.
 */
class Delegate
{
	public:
		/**
		 * The Delegate constructor with the pointer to
		 * a function.
		 */
		Delegate(functionPointer function);
		Delegate(functionPointer function, void* argument);
		Delegate();

		/**
		 * Gets the function being pointed to.
		 */
		 functionPointer GetFunction();

		/**
		 * Gets the argument used with this
		 * delegate..
		 */
		 void* GetArgument();

	private:
		functionPointer _function;
		void* _argument;

};

#endif
