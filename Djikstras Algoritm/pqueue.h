// CSCI 2530
// Assignment: 7
// Author:     Walter Sellars
// File:       pqueue.h
// Tab stops:  4

// **Say what this program does here.  (replace this comment)**

#include <iostream>
#include "event.h"
using namespace std;

typedef Event* ItemType;

typedef double      PriorityType;

typedef void (*ItemPrinter)(ItemType);

typedef void (*PriorityPrinter)(PriorityType);

struct PQCell;

// Structure PriorityQueue holds a pointer to the PQCell linked list.
// By default it sets the pointer to null.

struct PriorityQueue
{
    PQCell* head;
    PriorityQueue()
    {
        head = NULL;
    }
};

bool isEmpty(const PriorityQueue& q);

void insert(PriorityQueue& q, ItemType x, PriorityType p);

void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter pp);

void remove(PriorityQueue& q, ItemType& x, PriorityType& p);