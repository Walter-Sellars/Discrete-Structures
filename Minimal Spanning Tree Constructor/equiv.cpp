// CSCI 2530
// File:       equiv.cpp
// Tab stops:  4

// Equiv.cpp is a tool that manages an equivalence relation that can be changed in a specific
// way 

#include <cstdio>
#include "equiv.h"
using namespace std;

// Function newER returns an equivalence relation of size 'n' over {1, ..., n} 
// where each value is initially the sole member of it's equivalence class.

ER newER(int n)
{
    ER R = new int[n + 1];
    for (int index = 1; index <= n; index++)
    {
        R[index] = index;
    }
    return R;
}

// Function "leader" returns the leader of n in equivalence relation R.

int leader(ER R, int n)
{
    
    if (R[n] == n)
    {
        return n;
    }
    else
    {
        R[n] = leader(R, R[n]);
        return R[n];
    }
}

// Function equivalent returns true if x and y are currently in
// the same equivalence class in equivalence relation R, and 
// returns false if they are not in the same class.

bool equivalent(ER R, int x, int y)
{
    if (leader(R, x) == leader(R, y))
    {
        return true;
    }
    return false;
}

// void merge(int* R, int x, int y)
// Merges the equivalence classes of x and y in R, making 
// the leader of y the new leader of x.

void merge(ER R, int x, int y)
{
    if (!equivalent(R, x, y))
    {
        R[leader(R, x)] = leader(R, y);
    }
}

//Function destroyER deletes the Equivalent Relation R and frees memory.

void destroyER(ER R)
{
    delete [] R;
}

// Function showER writes the contents of the Equivalent Relation 'R' 
// to the standard output.

void showER(ER R, int n)
{
    printf("\nx Boss\n");
    for (int index = 1; index <= n; index++)
    {
        printf("%i %i \n", index, R[index]);
    }
}

