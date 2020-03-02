/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { //constructor was not working because I had created a new ListNode* for head_ and tail_
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_); //changed to head
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL); //this is fine
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() { //destroy was not working initially, getting valgrind error - important function
  /// @todo Graded in MP3.1

  /* Going through the doubly linked list from head to end. Keeping a variable current
  to represent current position in list. Assigning it to temp as we go through the list,
  and deleting the temp, but moving current to next position. Finally setting all the
  variables and pointers to NULL to prevent memory leaks. */

  while(head_ != NULL) {
    ListNode* temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  head_ = NULL;
  length_ = 0;

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1

  /* First condition - if there is nothing in the list, or length = 0, the newNode
  entered has to be the head & the tail and length of list is incremented.

  Second condition - (else) there is already a head_ and you are adding to the
  front of a linked list. newNode->next points to the head_, newNode->prev points
  to NULL, and head_->prev points to newNode. The new head_ becomes head_->prev.
  */
  ListNode * newNode = new ListNode(ndata);

  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
    length_ = 1;
    return; //initally forgot return statement
  }
  head_->prev = newNode;
  newNode->next = head_;
  newNode->prev = NULL;


  head_ = head_->prev; //basically saying that the new head is newNode (since newNode is now head_ -> prev)
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1

  /* First condition - if there is nothing in the list, or length = 0, the newNode
  entered has to be the head & the tail and length of list is incremented.

  Second condition - (else) there is already a tail_ and you are adding to the
  back of a linked list. newNode->next points to the NULL, newNode->prev points
  to tail_, and tail_->next points to newNode. The new tail_ becomes tail_->prev.
  */
  ListNode * newNode = new ListNode(ndata);

  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
    length_ = 1;
    return;
  }
  tail_->next = newNode;
  newNode->prev = tail_;
  newNode->next = NULL;


  tail_ = tail_->next;
  length_++;
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
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  if (start == NULL) {
    return NULL;
  }

  if (splitPoint >= length_ || splitPoint == 0) {
    return start;
  }

  for (int i = 0; i < splitPoint || curr == NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
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
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

  if (head_ == NULL) {
    return;
  }

  ListNode* current = head_;
  ListNode* temp;
  int pos = 1;

  while (current != tail_) {
    temp = current->next;

    if (pos % 2 == 0) {
      current->prev->next = current->next; //we are skipping whatever is in the middle and setting the thing before to whats after.
      current->next->prev = current->prev;

      tail_->next = current;
      current->prev = tail_;
      current->next = NULL;
      tail_ = current;

    }
    pos++;
    current = temp;

  }

}

/**
 * Reverses the current List.
 */
template <typename T>
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
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2

  if (startPoint == endPoint) {
    return;
  }

  ListNode* current = startPoint;
  ListNode* prevNode = current->prev;
  ListNode* tempNode = current->next;

  current->next = endPoint->next;
  current->prev = tempNode;
  current = tempNode;


  while (current != endPoint) {

    tempNode = current->next;   //storing the next node before you change current->next pointer
    current->next = current->prev;  //changing direction of current->next pointer to previous node
    current->prev = tempNode;   //changing direction of current->prev to point to next node

    current = tempNode;
  }

  endPoint->next = endPoint->prev;
  endPoint->prev = prevNode;

  if (head_ != startPoint) {
    prevNode->next = current;

  }

  if (tail_ != endPoint) {
    startPoint->next->prev = startPoint;
  }

  if (head_ == startPoint) {
    head_ = endPoint;
  }

  if (tail_ == endPoint) {
    tail_ = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  /* Go through the list using normal while loop with a current node, have a
  counter that increments when you reach the n value then reverse it.
  */

  ListNode* newStart = head_;
  ListNode* newEnd = newStart;
  int pos = 0;

  while(newStart != NULL) {
    pos = 1;

    while (pos < n) {
      if (newEnd != tail_) {
        newEnd = newEnd->next;
      }
      pos++;
    }
    reverse(newStart, newEnd);
    newStart = newStart->next;
    newEnd = newStart;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
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
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {

  /// @todo Graded in MP3.2

  ListNode* current = first;
  ListNode* secondCurrent = second;
  ListNode* secondNextNode = second;

  while(secondCurrent != NULL) {
    while(current != NULL) {

      if (secondCurrent->data < first->data) {
        secondNextNode = secondNextNode->next;
        secondCurrent->prev = NULL;
        secondCurrent->next = first;
        first->prev = secondCurrent;
        first = secondCurrent;
        second = second->next;
        break;
      }

      if (secondCurrent->data < current->data) {
        secondNextNode = secondNextNode->next;
        secondCurrent->next = current;
        secondCurrent->prev = current->prev;
        current->prev->next = secondCurrent;
        current->prev = secondCurrent;
        break;
      }

      if (current->next == NULL) {
        current->next = secondCurrent;
        secondCurrent->prev = current;
        secondNextNode = NULL;
        break;
      }
      current = current->next;
    }
    secondCurrent = secondNextNode;
  }
  return first;
}




  /*ListNode* currHead = NULL;
  if (first == NULL) {
    return second;
  }

  if (second == NULL) {
    return first;
  }

  if (first->data < second->data) {
    currHead = first;
    first = first->next;
  } else {
    currHead = second;
    second = second->next;
  }

  ListNode* current = currHead;

  while (first != NULL && second != NULL) {

    if (first->data < second->data) {
      current->next = first;
      first->prev = current;
      first = first->next;

    } else {
      current->next = second;
      second->prev = current;
      second = second->next;
    }
    current = current->next;
  }

  if (second == NULL && first != NULL) {
    current->next = first;
    first->prev = current;
  }

  if (first == NULL && second != NULL) {
    current->next = second;
    second->prev = current;
  }

  return currHead;
}
*/




/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start->next == NULL || start == NULL) {
    return start;  //returning first node of the new list called in the last line of tihs function
  }

  ListNode* second = split(start, chainLength/2);  //second node holds head of the other half
  int newLength = (chainLength % 2) + (chainLength / 2); //splitting in half plus taking the remainder after half split
  return merge(mergesort(start,chainLength/2), mergesort(second, newLength));
}
