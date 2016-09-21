/*############################################################################
#                                                                            #
#  hencode.cc                                                                #
#                                                                            #
#  Complete by: Oliver Keh                                                   #
#                                                                            #
#  May 8th, 2016                                                             #
#                                                                            #
#  This program reads an input file and creates a huffman tree and creates   #
#  a string of binary code based on the position of the characters from the  #
#  input file in the huffman tree and then assigns an unsigned integer       #
#  to each 8 bit sequence. The file length and tree are output to the        #
#  overhead file.                                                            #
#                                                                            #
############################################################################*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include "priqueue.h"

using namespace std;

typedef hnode* huff;

size_t COUNTS[256] = {0};  // initializes all cells to 0.
string CODES[256];         // default strings are empty

unsigned char bitstring_to_byte(string bits)
{
    size_t i;
    unsigned char total = 0;
    size_t power;

    /* total is incremented by the size of power every time bits[i] is not 0,
       then total is divided by 2 when the next bit is analyzed */
    for (i = 0, power = 128; i < 8; i++, power /= 2)
        total += power * (bits[i] - '0');
    return total;
}

void output_tree(hnode * tree, ostream & ostr)
{
    /*  a huffman tree is always full, so a node will always have a left if it
	    is not a leaf */
    if (!tree -> left) 

        // L is output every time a leaf is reached, along with its letter
        ostr << 'L' << tree -> data;
    else {
        // I is output every time an internal node is reached
        ostr << 'I';
        output_tree(tree -> left, ostr);
        output_tree(tree -> right, ostr);
    }
}

void string_from_codes(string infile, ostream & ostr)
{
    // initializes an empty string
    string total = "";
    int letter;

    // resets in to the beginning of the file
    ifstream in(infile.c_str());

    /* adds the binary string for each corresponding letter in the input file
       from the CODES list to the empty 'total' string */
    while ((letter = in.get()) != EOF)
        total += CODES[letter];

    // while total is not divisible by 8, it adds 0 to the end
    while (total.length() % 8 != 0) {
        total += '0';
    }

    unsigned char character;
    while (total.length() != 0) {
        character = bitstring_to_byte(total.substr(0, 8));
        total = total.substr(8);
        ostr << character;
    }
}

void binary_to_codes(hnode * tree, string curr_code){

    /* if tree is a leaf, it adds curr_code to the position in CODES that
       corresponds with the letter at the leaf */
    if (!tree -> left) {
        CODES[tree -> data] = curr_code + CODES[tree -> data];
        return;
    }
    binary_to_codes(tree -> left, curr_code);
    binary_to_codes(tree -> right, curr_code);
}

size_t combine_count(hnode * left, hnode * right)
{
    // combines the counts of the left and right hnode pointers
    return (left -> count + right -> count);
}

int _compare(const huff & p1, const huff & p2)
{
  return (p1 -> count - p2 -> count);
}

void condense(PriQueue<hnode*> & priqu) {

    // removes the first two items off of priqu and sets pointers equal to each
    hnode *left = priqu.remove();
    hnode *right = priqu.remove();

    // adds "0" or "1" to the front of the string curr_code and moves downwards
    binary_to_codes(left, "0");
    binary_to_codes(right, "1");

    // adds a new hnode to priqu with pointers to left and right set above
    priqu.add(new hnode(combine_count(left, right), left, right));
}

void create_hnode(PriQueue<hnode*> & priqu)
{
    // creates an hnode for each occurance in COUNTS that is not equal to 0
    for (size_t i=0;i<256;i++)
        if (COUNTS[i] != 0) {
            hnode * item = new hnode(i, COUNTS[i]);
            priqu.add(item);
        }
}

int main(int argc, char **argv)
{
    // exits the program if there are less than 2 arguments in command line
    if (argc < 2)
        return 0;

    string filename = argv[1];
    ifstream in(filename.c_str());

    // checks to see if the input file exists
    if (!in.is_open())
        return 0;

    // creates filename.huf
    string outfilename = filename + ".huf";
    ofstream ostr(outfilename.c_str());
    int letter;
    size_t counter = 0;

    int (*C)(const huff &, const huff &) = _compare;

    // creates an instance of the class PriQueue
    PriQueue<huff> priqu(C);

    /* adds 1 to position of value 'letter' every time that letter occurs in
       the input file */
    while ((letter = in.get()) != EOF) {
        // add this letter to the counts
        COUNTS[letter]++;
	    counter++;
    }

    // creates an hnode for every occurance in CODES not equal to 0
    create_hnode(priqu);

    // leaves the full tree on the priority queue
    while (priqu.size() > 1) {
        condense(priqu);
    }

    // removes final hnode off of priqu and returns the root of the tree
    hnode * root = priqu.remove();

    // outputs length of file to .huf file 
    ostr << counter;

    // outputs the tree to the header file
    output_tree(root, ostr);

    // outputs the input file in the form of binary code to .huf file
    string_from_codes(filename, ostr);

    // removes the file
    remove(filename.c_str()); 
}