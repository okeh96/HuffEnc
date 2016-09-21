/*############################################################################
#                                                                            #
#  priqueue.h                                                                #
#                                                                            #
#  Complete by: Oliver Keh                                                   #
#                                                                            #
#  May 8th, 2016                                                             #
#                                                                            #
#  Program defines the class Priqueue as a heap-based tree implementation    #
#  and also contains the definition for hnode, which must be done outside of #
#  the class definition. File contains constructor and all additional        #
#  functions for PriQueue. Also contains separate definitions of hnode       #
#  depending on whether or not the node is internal or a leaf.               #
#                                                                            #
############################################################################*/

#include <cstdlib>
#ifndef PRIQUEUE
#define PRIQUEUE

using namespace std;

struct hnode {
    unsigned char data;
    size_t count;
    hnode *left, *right;
    hnode(int letter, size_t count) : data(letter), count(count),
          left(NULL), right(NULL) {} 
    hnode(size_t count, hnode * left, hnode * right) : 
          count(count), left(left), right(right) {}
};

template <typename T>
class PriQueue {

    public:

        // constructor
        PriQueue(int (*C) (const T &, const T &));

        // adds a new item to the heap
        void add(const T &);

        // removes first item from heap and returns pointer pointing to it
        T remove();

        // returns the size of the heap
        size_t size();

    private:

        // returns position of parent node in data array
        size_t parent(size_t k);

        // returns position of left child node in the data array
        size_t left_child(size_t k);

        // returns position of the right child node in the data array
        size_t right_child(size_t k);

        // swaps two nodes in tree
        void swap(T &, T &);

        // current number of elements in the heap
        size_t _size;

        // space to store the heap
        T _data[500];

        // comparison function
        int (*_compare)(const T &, const T &);

        // adjusts positions of nodes in tree after adding
        void _reheap_up(size_t);

        // adjusts positions of nodes in tree after removing
        void _reheap_down(size_t);

};

#include "priqueue.cc"

#endif