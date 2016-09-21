/*############################################################################
#                                                                            #
#  priqueue.cc                                                               #
#                                                                            #
#  Complete by: Oliver Keh                                                   #
#                                                                            #
#  May 8th, 2016                                                             #
#                                                                            #
#  Creates a heap-based tree implementation, organizing the data from least  #
#  to highest.                                                               #
#  This program defines all of the member functions of the class PriQueue    #
#  that include the constructor. Also has functions to allow                 #
#  items to be removed and added to the PriQueue in condensed form.          #
#                                                                            #
############################################################################*/

#include <iostream>
#include "priqueue.h"

using namespace std;

template <typename T>
size_t PriQueue<T>::size()
{
    // returns the size of the tree
    return _size;
}

template <typename T>
size_t PriQueue<T>::left_child(size_t k)
{
    // returns the position of the left child of the node in the _data array
    return k * 2 + 1;
}

template <typename T>
size_t PriQueue<T>::right_child(size_t k)
{
    // returns the position of the right child of the node in the _data array
    return k * 2 + 2;
}

template <typename T>
size_t PriQueue<T>::parent(size_t k)
{
  // returns the parent position of the node in the _data array
    return (k - 1) / 2;
}

template <typename T>
PriQueue<T>::PriQueue(int (*C)(const T &, const T &))
{
    // initializes _compare as input function pointer and size to 0
    _compare = C;
    _size = 0;
}

template <typename T>
void PriQueue<T>::add(const T & item)
{
    // increments size by one while adding new item to new position in array
    _data[_size++] = item;

    // adjusts the order of the tree based on new added item
    _reheap_up(_size -  1);
}

template <typename T>
T PriQueue<T>::remove()
{
    // pointer of item at removed position
    T result = _data[0];

    // decrements the size of the array
    _data[0] = _data[--_size];

    // adjusts the order of the tree based on the removed item
    _reheap_down(0);

    // returns pointer to removed item
    return result;
}

template <typename T>
void PriQueue<T>::swap(T & node1, T & node2)
{
    // swaps the items at the two positions in array using variable temp
    T temp = node1;
    node1 = node2;
    node2 = temp;
}

template <typename T>
void PriQueue<T>::_reheap_up(size_t pos)
{
    size_t par;

    // ends function if the item is at the correct position
    if (pos==0 or _compare(_data[pos],_data[par=parent(pos)])>=0)
        return;

    // swaps the item with its parent node 
    swap(_data[pos], _data[par]);

    // recursive call to reheap up until base case is true
    _reheap_up(par);
}

template <typename T>
void PriQueue<T>::_reheap_down(size_t pos)
{
    size_t child;
    size_t right;

    // checks if the node is in the data
    if (pos < _size) {

        // sets child to left child node
        child = left_child(pos);

        // checks if the node is in the data
        if (child < _size){
	    
	    // sets right to the right child node
            right = right_child(pos);

	    /* if the data in right is smaller than data in left, child is set
	       to right */
            if (right < _size and _compare(_data[child], _data[right]) >= 0)
                child = right;

	    /* if data in child is greater than data in parent, swaps nodes and
	       reheaps down */
            if (_compare(_data[child], _data[pos]) < 0) {
                swap(_data[pos], _data[child]);
        	_reheap_down(child);
            }
        }
    }
}




