/**CSCI 2530
* Assignment: 7
* Author:     Walter Sellars
* File:       pqueue.cpp
* Tab stops:  4
* 
* "pqueue.cpp" is a priority queue management module that implements
* and manipulates multiple priority queues.
* This program provides functions to add and remove items to and from the queue,
* and to check if the queue has any items with priorities in the queue.
*/

#include "pqueue.h"
#include <cstdio>
using namespace std;

/*PQCell represents a single cell in a priority queue. PQCell has three fields:
*
* next - a pointer to the next PQCell structure
* item - the string contents of the structure
* priority - the priority level given to the structure
*/

struct PQCell
{
    PQCell* next;
    ItemType item;
    PriorityType priority;
    
    PQCell(PQCell* n,ItemType it,PriorityType pr)
    {
        next = n;
        item = it;
        priority = pr;
    }
};

//"isEmpty" returns true if q is empty, and false if q is not empty.

bool isEmpty(const PriorityQueue& q)
{
    return(q.head==NULL);
}

//"InsertCell" inserts item x with priority p into linked list L.

void insertCell(PQCell*& L, ItemType x, PriorityType p)
{
    if(L == NULL)
    {
        L = new PQCell(NULL,x,p);
    }
    else if (p < L->priority)
    {
        L = new PQCell(L, x, p);
    }
    else
    {
        insertCell(L -> next, x, p);
    }
}

// "Insert" inserts itemType x with priority p into PriorityQueue object q

void insert(PriorityQueue& q, ItemType x, PriorityType p)
{
    insertCell(q.head,x,p); 
}

//printPriorityQueue writes the priority queue of parameter 'q' to
// the standard output by using the function pi to write the item, and function pp to write the 
// priority.

void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi, PriorityPrinter pp)
{
    PQCell* h = q.head;
    while(h != NULL)
    {
        pi(h->item);
        printf(" ");
        pp(h->priority);
        printf("\n\n");
        h = h->next;
    }
}

//"remove" removes an item from the priority queue 'q' that has the smallest 
//priority. The function stores the removed cell's information in 
//out-parameters 'x' for item and 'p' for priority.

void remove(PriorityQueue& q, ItemType& x, PriorityType& p)
{
    if(!isEmpty(q))
    {
        PriorityQueue temp;
        temp.head = q.head;
        x=q.head->item;
        p=q.head->priority;
        q.head = temp.head->next;
        delete temp.head;
    }
}