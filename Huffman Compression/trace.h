// CSCI 2530
// Assignment: 8
// Author:     Walter Sellars
// File:       trace.h
// Tab stops:  4

#ifndef trace_h
#define trace_h

#include "tree.h"

extern int tracelevel;

// Function prototypes

void showChar(char b);
void spaceChar(int n);
void showTree(Tree b);
void showFreq(int* arr);
void showArray(char** code);
void traceOn(int argc, char* argv[]);

#endif
