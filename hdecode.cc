/*############################################################################
#                                                                            #
#  hdecode.cc                                                                #
#                                                                            #
#  Complete by: Oliver Keh                                                   #
#                                                                            #
#  May 8th, 2016                                                             #
#                                                                            #
#  This program reads an input file and creates a huffman tree. It reads the #
#  input header file and finds the length of the file as well as takes the   #
#  unsigned characters and turns them into a binary string to find the       #
#  intended position of each character in the file.                          #
#                                                                            #
############################################################################*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include "priqueue.h"

using namespace std;

string byte_to_bitstring(unsigned char byte)
{
    size_t power;
    string bitstring = "";
    for (power = 128; power > 0; power /= 2) {

        // if byte is greater than power, 1 must exist in bitstring
        if (byte >= power) {
            // adds 1 to bitstring corresponding to right movement along tree
            bitstring += '1';

            // subtracts size of power from byte
            byte -= power;
        }
        else {
            // adds 0 to bitstring corresponding to left movement along tree
            bitstring += '0';
        }
    }
    return bitstring;
}

hnode * build_tree(ifstream & in)
{
    // goes to next character in .huf file every time function is called
    int ch;
    ch = in.get();

    // if leaf, adds new hnode with following char in input file as letter
    if (ch == 'I')
        return new hnode(0, build_tree(in),
                         build_tree(in));

    // if internal hnode, recursively calls function with input file
    else {
        return new hnode(ch = in.get(), 0);
    }
}

void output_char(hnode * tree, string & bits, ofstream & ostr)
{
    // if node is a leaf, outputs the data
    if (!tree -> left)
        ostr << tree -> data;

    /* if bit is equal to 0, moves leftwards on tree and removes first
       character from bits */ 
    else if (bits[0] == '0') {
        output_char(tree -> left, bits = bits.substr(1), ostr);
    }

    /* if bits is equal to 1, moves rightwards on tree and removes first 
       character from bits */
    else {
        output_char(tree -> right, bits = bits.substr(1), ostr);
    }
}

int main(int argc, char** argv) {

    // exits program if input file is not included
    if (argc < 2)
        return 0;

    string filename = argv[1];
    ifstream in(filename.c_str());

    string out_filename = filename.substr(0, filename.length() - 4);
    ofstream ostr(out_filename.c_str());

    // checks is file can be opened
    if (!in.is_open())
        return 0;

    // finds length of file
    size_t length;
    in >> length;

    // buids tree from header file
    hnode * tree;
    tree = build_tree(in);

    // creates empty string for binary code
    string bits = "";
    int ch;

    // creates a string of binary from unsigned chars in header file
    while ((ch = in.get()) != EOF) {
        bits += byte_to_bitstring((unsigned char) ch);
    }

    /* outputs the converted binary string into characters and output while
       the counter is less than the length of the file */
    size_t counter = 0;
    while (counter < length) {
        output_char(tree, bits, ostr);
	counter++;
    }

    // removes the file
    remove(filename.c_str());
}