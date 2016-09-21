/*############################################################################
#                                                                            #
#  priqueue.h                                                                #
#                                                                            #
#  Complete by: Oliver Keh                                                   #
#                                                                            #
#  April 24, 2016                                                            #
#                                                                            #
#  This program defines the class Priqueue and also contains the definition  #
#  for hnode, which must be done outside of the class definition. File       #
#  contains constructor, destructor, and all additional functions for        #
#  PriQueue. Also contains separate definitions of hnode depending on        #
#  whether or not the node is internal or a leaf.                            #
#                                                                            #
############################################################################*/

#include <cstdlib>

struct hnode {
    unsigned char data;
    size_t count;
    hnode *left, *right;
    hnode(int letter, size_t count) : data(letter), count(count),
          left(NULL), right(NULL) {} 
    hnode(size_t count, hnode * left, hnode * right) : 
          count(count), left(left), right(right) {}
};

class PriQueue {

    struct listnode {
    hnode * data;
    listnode * next;
    listnode(hnode * data, listnode * next) : data(data), next(next) {}
    };

    public:

    // constructor
    PriQueue();

    // destructor
    ~PriQueue();

    // helps destructor, deletes first listnode in Priqueue
    void remove_at_0();

    // removes listnode from Priqueue and returns its hnode data 
    hnode * remove();

    // returns size of Priqueue
    size_t size();

    // adds a new hnode where appropriate, ordered by smallest to largest
    void add(hnode * item);

    /* add helper function, recursively goes through Priqueue to find right
       position for item */
    void rc_add(listnode * & front, hnode * item);

    private:

    size_t _size;
    listnode * _front;

};