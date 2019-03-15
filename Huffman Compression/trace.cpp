// CSCI 2530
// Assignment: 8
// Author:     Walter Sellars
// File:       trace.cpp
// Tab stops:  4

/*
  This module enables tracing for other modules that include "trace.h".
  Whenever '-t' is entered in the command line as a flag,tracing is enabled.
 */

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <iomanip>
#include <cctype>
#include "trace.h"

using namespace std;

int tracelevel = 0;

/*
 * traceOn sets variable to 1 if '-t' is entered in
 * the command line.
 */

void traceOn(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0) {
            tracelevel = 1;
        }
    }
}

/*
 * showFreq prints the frequencies of the characters 
 * in array 'arr'.
 */

void showFreq(int* arr)
{
    if(arr != NULL)
    {
        printf("\nThe character frequencies are: \n");
        for (int i = 0; i < 256; i++)
        {
            if (arr[i] > 0)
            {
                cout << setw(5);
                showChar(i);
                cout << setw(5) << arr[i] << endl;
            }
        }
    }
}

/*
 * showChar prints the name of 'b'
 * to the standard output.
 */

void showChar(char b)
{
    int hdf = (int) b;
    if (isspace(hdf))
    {
        spaceChar(hdf);
    }
    else if (isprint(hdf))
    {
        cout << (unsigned char) b;
    }
    else
    {
        cout << b << "\\n";
    }
}

/*
 * spaceChar checks if 'n' is a space character, and if 'n'
 * is, spaceChar prints the type of space character to the standard output.
 */

void spaceChar(int x)
{
    switch (x)
    {
        case '\n':
            cout << "newline";
            break;
        case ' ':
            cout << "space";
            break;
        case '\t':
            cout << "tab";
            break;
        default:
            cout << "spaceChar";
            break;
    }
}

/*
 * showTree prints a character tree contained in 'b' to the standard
 * output.
 */

void showTree(Tree b)
{
    if(b->kind == leaf)
    {
        showChar(b->ch);
    }
    else
    {
        printf("(");
        showTree(b->left);
        printf(" , ");
        showTree(b->right);
        printf(")");
    }
}

/*
 * showArray prints the huffman code for every character
 * inside the array of strings 'code'.
 */

void showArray(char** code)
{
    if(code != NULL) {
        cout << "\n\nThe huffman code is as follows:" << endl;
        for (int i = 0; i < 256; i++) {
            if (code[i] != NULL) {
                cout << setw(5);
                showChar(i);
                cout << setw(7) << code[i] << endl;
            }
        }
    }
}
