#include "pqueue.h"
#include <cstdio>
using namespace std;
  
typedef const char* CSTRING;

void printString(CSTRING s)
  {
    printf("%s", s);
  }

void printDouble(double x)
  {
    printf("%lf", x);
  }
int main()
{
    PriorityQueue *p = new PriorityQueue ;
    insert(*p, "alpha", 1);
    insert(*p, "beta", 2);
    insert(*p, "delta", 3);
    insert(*p, "epsilon", 4);
    printPriorityQueue(*p, printString, printDouble);
   
    return 0;
}