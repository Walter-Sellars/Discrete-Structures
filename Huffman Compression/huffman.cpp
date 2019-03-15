// CSCI 2530
// Assignment: 8
// Author:     Walter Sellars
// File:       huffman.cpp
// Tab stops:  4

/*
 * This program uses the huffman algorithm to create a huffman tree
 * from a given text file that's named and entered in the command line. 
 * if the file is not found, the program will terminate.
 * 
 * At the terminal, the program can be set to trace with -t. Provide the 
 * program with the input file and the output file.
 * 
 * sample input:
 * 
 * ./huffman -t test1.txt test1.cmp
 * 
 * will start the program with tracing on, converting the text file 'test1.txt'
 *  to the compressed binary file 'test1.cmp' using the huffman algorithm.
 */


#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "trace.h"
#include "tree.h"
#include "binary.h"
#include "pqueue.h"

using namespace std;

const int MAXCHARS = 256;

// Prototypes

bool freqCounts(int *arr, int argc, char **argv);
void readFile(FILE* inFile, int* arr);
Tree huffmanTree(int *arr);
void insertQueue(PriorityQueue& q, int* charArray);
Tree huffTreeQueue(PriorityQueue &q);
void buildCode(Tree t, char** code, const char* pref);
void setNull(char** code);
void writeIOTree(BFILE* f, Tree t);
void encodeChar(char** code, BFILE* bF, const char* inputFile);
void encodeCharHelper(BFILE* write, char** code, int x);

int main(int argc, char* argv[])
{
    traceOn(argc, argv);

    int* charArr = new int[MAXCHARS];
    bool result = freqCounts(charArr, argc, argv);

    if(result)
    {
        Tree test = huffmanTree(charArr);

        char** code = new char*[MAXCHARS];
        const char* prefix = "";
        setNull(code);
        buildCode(test, code, prefix);

        BFILE* openWriteFile = openBinaryFileWrite(argv[argc-1]);
        writeIOTree(openWriteFile, test);

        encodeChar(code, openWriteFile, argv[argc-2]);

        if (tracelevel)
        {
            showFreq(charArr);
            printf("\nThe huffman tree is as follows:");
            showTree(test);
            showArray(code);
            printf("\nInput File: %s ", argv[argc-2]);
            printf("\nOutput File: %s \n", argv[argc - 1]);
            
        }

        closeBinaryFileWrite(openWriteFile);
    }
    else
    {
        printf("Unable to open file.");
    }

    putchar('\n');

    return 0;
}

/**
 * readFile reads in characters from the file 'inFile'
 * and stores their frequency counts in array 'arr'.
 */

void readFile(FILE* inFile, int* arr) {
    int ch;
    while((ch = getc(inFile)) != EOF)
    {
        arr[ch]++;
    }
}

/*
 * freqCounts finds the character counts from the first
 * file via 'argc' and 'argv' to find the position in the commandline and the
 * name. freqCounts stores the counts in the array 'arr', and returns true if 
 * it opened the file, and returns false otherwise false otherwise.
 */

bool freqCounts(int *arr, int argc, char **argv)
{
    for (int i = 0; i < MAXCHARS; i++)
    {
        arr[i] = 0;
    }
    FILE* inFile = fopen(argv[argc-2], "r");

    if(inFile != NULL)
    {
        readFile(inFile, arr);
        fclose(inFile);
        return true;
    }
    fclose(inFile);

    return false;
}

/*
 * huffmanTree reads the frequencies of each character in array "arr" and
 * returns the huffman tree of all present characters in 'arr'.
 */

Tree huffmanTree(int *arr)
{
    PriorityQueue queue = PriorityQueue();
    insertQueue(queue, arr);

    Tree huffmanTree = huffTreeQueue(queue);
    return huffmanTree;
}

/*
 * insertQueue inserts any characters in 'charArray' 
 * into priority queue 'q'.
 */
void insertQueue(PriorityQueue& q, int* charArray)
{
    for(int i = 0; i < MAXCHARS; i++)
    {
        if(charArray[i] > 0)
        {
            Tree pop = new Node((unsigned char)i);
            insert(q, pop, i);
        }
    }
}

/*
 * huffTreeQueue returns the huffman tree inside of priority
 * queue variable 'q'.
 */

Tree huffTreeQueue(PriorityQueue &q)
{
    Tree alpha = NULL;
    int epsil = 0;
    while(!isEmpty(q))
    {
        remove(q, alpha, epsil);
        if(!isEmpty(q))
        {
            Tree beta;
            int add;
            remove(q, beta, add);
            Tree t = new Node(alpha, beta);
            insert(q, t, epsil + add);
        }
    }
    return alpha;
}

/*
 * buildCode builds the char codes for tree 't'and stores it in the 
 * array of strings 'code' and prefixes them with 'pref'.
 */

void buildCode(Tree t, char** code, const char* pref)
{
    int pre;
    if (pref != NULL)
    {
        pre = sizeof(pref) + 1;
    }
    else
    {
        pre = 1;
    }
    if (t->kind == leaf)
    {
        code[(int)(unsigned char)t->ch] = strncpy(new char[pre], pref, pre);
    }
    else
    {
        char *prefL = strncpy(new char[pre], pref, pre);
        char *prefR = strncpy(new char[pre], pref, pre);
        strcat(prefL, "0");
        strcat(prefR, "1");
        buildCode(t->left, code, prefL);
        delete[] prefL;
        buildCode(t->right, code, prefR);
        delete[] prefR;
    }
}

/*
 * setNull sets array 'arr' to null.
 */

void setNull(char** arr)
{
    for(int i = 0; i < MAXCHARS; i++)
    {
        arr[i] = NULL;
    }
}

/*
 * writeIOTree writes a binary tree from 't' into
 * open binary file 'f'.
 */

void writeIOTree(BFILE* f, Tree t)
{
    if(t->kind == leaf)
    {
        writeBit(f, 1);
        writeByte(f, t->ch);
    }
    else
    {
        writeBit(f, 0);
        writeIOTree(f, t->left);
        writeIOTree(f, t->right);
    }
}

/*
 * encodeChar reads the file'inputFile' and writes
 * the character code from array 'code' 
 * for the characters. It then reads the binary file 'bF', and then closes 
 * the 'inputFile'.
 */

void encodeChar(char** code, BFILE* bF, const char* inputFile)
{
    FILE* reRead = fopen(inputFile, "r");

    if(reRead != NULL) {
        int ch;
        while ((ch = getc(reRead)) != EOF) {
            encodeCharHelper(bF, code, ch);
        }
    }
    fclose(reRead);
}

/*
 * This helper function writes the character 'x' in
 * the binary file 'file'.
 */

void encodeCharHelper(BFILE* file, char** code, int x)
{
    for(int i = 0; code[x][i] != '\0'; i++)
    {
        int bit = (code[x][i] == '1');
        writeBit(file, bit);
    }
}