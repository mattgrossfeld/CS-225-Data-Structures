#include "heap.h"
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    //return 0;

	return 1; //Root stored at index 1.
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.

    return 2*currentIdx; //Left = 2i, for index i.
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return (2*currentIdx) + 1; //Right = 2i+1 for index i.
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
	
	//The current index can't be greater than or equal to the size of vector.	
	bool childExists = true;
	if (leftChild(currentIdx) < _elems.size())
		childExists = true;
	else
		childExists = false;
	return childExists;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
	if (_elems.size() <= rightChild(currentIdx))
		return leftChild(currentIdx);
	if (!higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]))
		return rightChild(currentIdx);
	else
		return leftChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
	if (hasAChild(currentIdx))
        {
		size_t minChildIndex = maxPriorityChild(currentIdx);
		if (higherPriority(_elems[minChildIndex], _elems[currentIdx]))
		{
			std::swap(_elems[minChildIndex], _elems[currentIdx]);
			heapifyDown(minChildIndex);
		}
	}
 
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
	T smallestVal = std::numeric_limits<T>::min();
	_elems.push_back(smallestVal);

}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm

	size_t x = 0;
	T smallestVal = std::numeric_limits<T>::min();
	_elems.push_back(smallestVal);
	_elems.insert(_elems.end(), elems.begin(), elems.end());
	for (x = parent(_elems.size()); x > 0; x--) 
		heapifyDown(x);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
	size_t currentIdx = 1;
	if (_elems.empty())
		return T();
	else
	{
		T highestPriority = _elems[currentIdx];
    		_elems[currentIdx] = _elems[_elems.size() - currentIdx];
   		_elems.pop_back();
   	 	heapifyDown(currentIdx);
    		return highestPriority;
	}
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
	//size_t root = root();
	return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
	_elems.push_back(elem);
	heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
	if (_elems.size() <= 1)
		return true;
    	else
		return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
