/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
	T stackTop = s.top(); //stackTop holds the top of the stack.
	s.pop(); //pop the top of the stack.
	if (!s.empty()) //If stack is not empty...
	{
		T sumVal = sum(s); //Call the sum of the popped stack.
		s.push(stackTop); //Push it back.
		return stackTop+sumVal; //Return the sum of the two.
	}
	else
	{
		s.push(stackTop);
		return stackTop;
	}
    return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets. 
 * A string will consist of 
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * You are allowed only the use of one stack in this function, and no other local variables.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
	stack<char> balancingStack;
	while(!input.empty())	
	{
		if (input.front() == '[') //If input has [ put it onto the stack and pop it from queue.
		{
			balancingStack.push(input.front()); //[ put onto stack.
		}
		else if((input.front() == ']') && (!balancingStack.empty())) //if queue has ] and stack has a [ in it
		{
			balancingStack.pop(); //Remove an element from the stack.
		}
		else if ((input.front() == ']') && (balancingStack.empty())) //If starting with ], already failed.
			return false;
		input.pop();
	}
	if (balancingStack.empty())
		return true;
	else
		return false;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
	stack<T> s;
	queue<T> q2 = q; //Holding the original queue.
	int set = 1, scrambled, queueSize = q.size();
	while (queueSize != 0)
	{
		if (queueSize < set)
			scrambled = queueSize;
		else
			scrambled = set;
		if (set % 2 == 0)
		{
			for (int i = 0; i < scrambled; i++)
			{
				s.push(q.front());
				q.pop();
			}
			for (int i = 0; i < scrambled; i++)
			{
				q.push(s.top());
				s.pop();
			}
		} 
		
		else
		{
			for (int i = 0; i < scrambled; i++)
			{
				q.push(q.front());
				q.pop();
			}
		}

		queueSize = queueSize - scrambled;
		set++;
	}
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    T sTop; // rename me
	if (!s.empty()) //If the stack has data in it.
	{
	sTop = s.top(); //Hold the top value.
	s.pop(); //Pop off the top value.
	retval = verifySame(s, q); //compare the smaller stack with the queue.
	retval &= (sTop == q.front()); //check if the top value is the same as the top of the queue.
//If it is AND retval = true (which it hsould be, by default), keep it true.
	q.push(q.front()); //Push the front of the queue to the back. Gets the next value.
	q.pop(); //Pop the top value off the queue.
	s.push(sTop); //push the stack back.
	}
	return retval;
}

}
