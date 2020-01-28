/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
	while(head_ != NULL)
	{
		ListNode * clearNode = head_;
		head_ = head_->next;
		delete clearNode;
	}
	tail_ = NULL;
	length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
	ListNode * newNode  = new ListNode(ndata); //New list node.
	if  (head_ == NULL)
	{
		head_ = newNode;
		tail_ = newNode;
		length_++;
	}
	else
	{
		newNode->next = head_;
		head_->prev = newNode;
		head_ = newNode;
		length_++;
	}
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
	ListNode * newNode  = new ListNode(ndata); //New list node.
	if  (tail_ == NULL)
	{
		head_ = newNode;
		tail_ = newNode;
		length_++;
	}
	else
	{
		tail_->next = newNode;
		newNode->prev = tail_;
		tail_ = newNode;
		length_++;
	}

}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  		reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
	if (startPoint == NULL || endPoint == NULL || startPoint == endPoint)
		return; //If the list has at most one node, done.
	//Holding the original nodes.
	ListNode * startNode = startPoint;
	ListNode * startPrev = startPoint->prev;
	ListNode * endNext = endPoint->next;
	ListNode * tempNode = startPoint->prev;

	while (startPoint != endPoint) //While they're not the same.
	{
		tempNode = startPoint->prev; //Temp holds previous node.
		startPoint->prev = startPoint->next; //previous holds the next one.
		startPoint->next = tempNode; 
		startPoint = startPoint->prev;
	}
	
	if (startPoint == endPoint)
	{
	tempNode = startPoint->prev;
	startPoint->prev = startPrev;
	startPoint->next = tempNode;
	endPoint = startNode;
	endPoint->next = endNext;
	}
	if (startPrev == NULL)
		head_ = startPoint;
	if (startPrev != NULL)
		startPrev->next = startPoint;
	if (endNext == NULL)
		tail_ = endPoint;
	if (endNext != NULL)
		endNext->prev = endPoint;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
	if (head_ == NULL || tail_ == NULL || head_ == tail_ || n == 1) //If list has <= 1 nodes
		return; //Or if we're reversing blocks of one, we don't reverse.
	if ( (n >= length_) && (length_ > 1)) //if blocks to reverse are bigger than length, just reverse the list.
		reverse(head_, tail_);
	int counter; //Counter for changing the blocks.
	ListNode * startPoint = head_; //Head = startPoint
	ListNode * endPoint = head_; //endpoint starts at head
	while ( (endPoint->next != NULL) && (startPoint->next != NULL) )//As long as neither nexts are empty
	{
		endPoint = startPoint; //the endpoint is now at the beginning
		for(counter = n-1; counter > 0; counter--) //Sets up the blocks to be reversed.
		{
			if( endPoint->next != NULL) //if the next node after the end is not empty, move.
			{
				endPoint = endPoint->next; //new endpoint.
			
			}
		}
		reverse(startPoint, endPoint); //reverse it.
		startPoint = endPoint->next; //move the startpoint to the next block
		
	}
  /// @todo Graded in MP3.1
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
	if (head_ == NULL || tail_ == NULL || head_ == tail_) //If the list is smaller than one, done.
		return;
	ListNode * currNode = head_; //Node we are moving.
	ListNode * tempNode = head_;
	
	while (currNode->next != tail_ && currNode != NULL && currNode != tail_)//Remove and append until we hit NULL or tail.
	{

		tempNode = currNode; //current node we're on is the one we're keeping.
		currNode = currNode->next; //Get the second node.
		
		tempNode->next = currNode->next; //Changing next pointers. A -> B -> C
		currNode->next->prev = tempNode;		//Changes to A->C
		
		currNode->next = NULL; //Appending it to the end, so its next pointer is NULL
		currNode->prev = tail_; //Previous pointer is the tail.
		tail_->next = currNode;
		tail_ = currNode; //New tail defined.

		currNode = tempNode->next;
	}
	
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
	if (start == NULL || splitPoint <= 0)
	  return start;
	ListNode * currNode = start;
	for(int i = 0; i < splitPoint; i++)
	{
		currNode = currNode->next;
	}
	currNode->prev->next = NULL;
	return currNode;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
	ListNode * firstList = first;
	ListNode * secondList = second;

	if (firstList == NULL || secondList == NULL || firstList == secondList)
		return firstList; //If either list is null or if they're the same, return.

	ListNode * newList = first; //the new, merged list
	ListNode * temp = newList; //temporarily hold it.
	if (firstList->data < secondList->data) //If the firstList's 1st element is less than the second's 1st element
		firstList = firstList->next; //its fine, so move on.
	else
	{
		newList = secondList; //otherwise, it'll start with secondList.
		temp = newList; //hold the new one.
		secondList = secondList->next; //Move on.
	}

	
	while (firstList != NULL && secondList != NULL) //While they're both not NULL
	{

		if (firstList->data < secondList->data)
		{
			temp->next = firstList;
			firstList->prev = temp;
			temp = firstList;
			firstList = firstList->next;

		}

		else
		{
			temp->next = secondList;
			secondList->prev = temp;
			temp = secondList;
			secondList = secondList->next;
		}
	}
	if (firstList != NULL)
	{
		temp->next = firstList;
		firstList->prev = temp;
	}
	else
	{
		temp->next = secondList;
		secondList->prev = temp;
	}

	return newList;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
	ListNode* sortedList = start; //starting point
	if (chainLength == 1) //Base case
	{
		start->next = NULL;
		start->prev = NULL;
		return start;
	}
	if (start != NULL && chainLength > 1) //if the list isn't null, and we need to sort a size > 1
	{
	ListNode* temp = start;
	for (int i = 0; i < chainLength/2; i++) //Go to the middle.
		temp = temp->next;
	start = mergesort(start, chainLength/2); //Start sorting the beginning.
	temp = mergesort(temp, chainLength - chainLength/2); //Start sorting the second half
	ListNode* sortedList = merge(start, temp); //merge it all
	return sortedList;
	}
	return start;

}
