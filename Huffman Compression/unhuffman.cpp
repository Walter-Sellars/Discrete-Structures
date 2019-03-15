// CSCI 2530
// Assignment: 8
// Author:     Walter Sellars
// File:       unhuffman.cpp
// Tab stops:  4

/*
 * This program 'unhuffmans' the huffman tree, which is read in as a binary file.
 * Unhuffman prints the decoded tree to the standard output.
 */

#include <cstdio>
#include <iostream>
#include "binary.h"
#include "trace.h"
#include "tree.h"


using namespace std;

// Prototypes

Tree returnBinaryTree(BFILE *data);
int charAsInt(Tree t, BFILE* file);
void uncompress(BFILE *file, char *out, Tree tree);


int main(int argc, char **argv)
{
    traceOn(argc, argv);
    BFILE* openRead = openBinaryFileRead(argv[argc-2]);
    Tree t = returnBinaryTree(openRead);
    uncompress(openRead, argv[argc-1], t);

    closeBinaryFileRead(openRead);

    if(tracelevel)
    {
        cout << "\nThe decoded huffman tree:" << endl;
        showTree(t);
        putchar('\n');
    }

    putchar('\n');

    return 0;
}

/**
 * returnBinaryTree reads the binary file 'data', makes a
 * binary tree, and then returns the tree.
 */

Tree returnBinaryTree(BFILE *data)
{
    int bit = readBit(data);
    if(bit != EOF && bit == 1) {
        int byte = readByte(data);
        if(byte != EOF) {
            return new Node(byte);
        }
    }
    return new Node(returnBinaryTree(data),
                    returnBinaryTree(data));
}

/*
 * charAsInt returns the character of the leaf at the end of the tree.
 */

int charAsInt(Tree t, BFILE* file)
{
    if(t->kind == leaf)
        return t->ch;
    else
    {
        int pop = readBit(file);
        if(pop == EOF)
            return EOF;
        else if(pop == 1)
            charAsInt(t->right, file);
        else
            charAsInt(t->left, file);
    }
}

/*
 * 'uncompress' converts the compressed binary output of the huffman program in
 * 'file' and writes the characters stored in the 'tree' to the output
 * file 'out'
 */
void uncompress(BFILE* file, char* out, Tree tree)
{
    FILE* writeF = fopen(out, "w");
    char it = charAsInt(tree, file);
    while(it != EOF)
    {
        putc(it, writeF);
        it = charAsInt(tree, file);
    }
    fclose(writeF);
}