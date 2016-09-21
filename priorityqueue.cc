/*############################################################################
#                                                                            #
#  priqueue.cc                                                               #
#                                                                            #
#  Complete by: Oliver Keh                                                   #
#                                                                            #
#  April 24, 2016                                                            #
#                                                                            #
#  This program defines all of the member functions of the class PriQueue    #
#  that include the constructor and destructor. Also has functions to allow  #
#  items to be removed and added to the PriQueue in condensed form.          #
#                                                                            #
############################################################################*/

#include <iostream>
#include "priqueue.h"

using namespace std;

PriQueue::PriQueue() 
{
    // initializes size to 0 and front to NULL for empty Priqueue
    _size = 0;
    _front = NULL;
}

PriQueue::~PriQueue()
{
    // destructor removes all items from PriQueue until size is equal to 0
    while (_size != 0) {
        remove_at_0();
    }
}

void PriQueue::remove_at_0()
{
    // sets pointer p equal to front
    listnode * p = _front;

    // moves front pointer to next item in PriQueue
    _front = _front -> next;

    // deletes p and decrements size by 1
    delete p;
    _size--;
}

hnode * PriQueue::remove() 
{
    // returns NULL if Priqueue is empty
    if (_size == 0)
        return NULL;

    // sets pointer p equal to data of front listnode in PriQueue
    hnode * p = _front -> data;

    // sets pointer q equal to front listnode in PriQueue
    listnode * q = _front;

    // moves front pointer to next item in PriQueue
    _front = _front -> next;

    // deletes front listnode
    delete q;

    // decrements size and returns hnode pointer p
    _size--;
    return p;

}

size_t PriQueue::size() 
{
    // returns size of PriQueue
    return _size;
}

void PriQueue::rc_add(listnode * & front, hnode * item)
{
    /* if Priqueue is empty or item count is less than pointer count, creates
       a new listnode before pointer front */
    if (front == NULL or item -> count <= front -> data -> count)
        front = new listnode(item, front);
    else
        // recursively calls function until base case is true
        rc_add(front->next, item);
}

void PriQueue::add(hnode * item) 
{
    // calls recursive add function passing _front and hnode pointer item
    rc_add(_front, item);

    // increments size after item has been placed
    _size++;
}