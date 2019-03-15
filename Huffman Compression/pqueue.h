// CSCI 2530
// Assignment: 6
// Author:     Walter Sellars
// File:       pqueue.h
// Tab stops:  4

#include <iostream>
using namespace std;

#include "tree.h"
typedef Tree ItemType;
typedef int PriorityType;
typedef void (*ItemPrinter)(ItemType);
typedef void (*PriorityPrinter)(PriorityType);

struct PQCell;

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