#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
    /* YOUR CODE HERE */
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
    /* YOUR CODE HERE */
    Node * newNode = new Node(ndata);       // Create new node with ndata
    newNode->next = tail_->next;            // newNode's next val is tail_->next (aka head_)
    tail_->next = newNode;                  // point the former tail's next to newNode
    tail_ = newNode;                        // set tail_ pointer to newNode
}

/**
 * Mirrors the given chain across its center on the x-axis.
 */
void Chain::mirror()
{
    /* YOUR CODE HERE */
    
}

/*
* Modifies the current chain by "rotating" every k nodes.
* Starting with the 0th node, swap with with the kth next node.
* Starting at the position you just swapped into, continue to
* swap nodes until you swap a node with the final node of the chain.
* Some examples with the chain a b c d e:
*   k = 0: a b c d e
*   k = 1: b c d e a
*   k = 2: c b e d a
*   k = 3: d e c b a
* You may assume that the rotation will not loop forever
* (i.e. you **will** swap the final node in the list at some point)
*/
void Chain::rotate(int k)
{
    /* YOUR CODE HERE */

    // Note: this solution assumes k >= 0
    if (k % length_ == 0) return;

    int pos = 0;

    while (pos != length_ - 1) {                // termination argument: pos = length_ - 1
        swap(pos, (pos + k) % length_);         // swaps the nodes at pos and pos + k
        pos = (pos + k) % length_;              // sets pos = pos + k
    }
}

/**
 * 
 */
void Chain::swap(int a, int b) 
{   
    Node *tempNext, *tempPrev;
    Node *A = head_, *B = head_;

    for (int i = 0; i < a; i++) A = A->next;
    for (int i = 0; i < b; i++) B = B->next;

    if (a == 0 || b == 0)                       // helper: checks if we're swapping the head node
    head_ = (A == head_) ? B : A;               // if yes, reassign the head node pointer to node at other index

    tempNext = B->next;
    tempPrev = B->prev;

    B->next = A->next;
    B->prev = A->prev;
    A->next = tempNext;
    A->prev = tempPrev;
    
    B->next->prev = B;
    B->prev->next = B;
    A->next->prev = A;
    A->prev->next = A;

    tail_ = head_->prev;                        // reassigns tail pointer
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */

void Chain::clear()
{
    /* YOUR CODE HERE */
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */

void Chain::copy(Chain const &other)
{
    /* YOUR CODE HERE */
}
