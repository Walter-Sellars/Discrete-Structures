// CSCI 2530
// File:       equiv.h
// Tab stops:  4

// These #ifndef and #define lines make it so that, if this file is
// read more than once by the compiler, its body is skipped on all
// but the first time it is read.

#ifndef EQUIV_H
#define EQUIV_H

// An equivalence relation is an array of integers.
// So ER abbreviates int*.

typedef int *ER;

// Public functions

ER newER(const int n);
void destroyER(ER R);
bool equivalent(ER R, const int x, const int y);
void merge(ER R, const int x, const int y);

// The following is advertised here solely for debugging.  These must
// only be used for debugging.

void showER(const ER R, const int n);
int leader(ER R, const int x);

#endif