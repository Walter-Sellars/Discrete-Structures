// CSCI 2530
// Assignment: 2
// Author:     Walter Sellars
// File:       hailstone.cpp
// Tab stops:  4

// Given the input interger 'num', "Hailstone" proceeds through the 
// hailstone sequence and stops when the sequence finishes at 1.  
// "Hailstone" prints the entire sequence, the sequence's largest number, 
// the length of the sequence that starts with a number from 1 to 'num', 
// and the starting number of the longest sequence that starts with a 
// number 1 to 'num'.
//
// Example - input of 7
// What number shall I start with? 7
// The hailstone sequence starting at 7 is :
// 7 22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1 
// The length of the sequence is 17. 
// The largest number in the sequence is 52. 
// The longest hailstone sequence starting with a number up to 7 has length 17.
// The longest hailstone sequence starting with a number up to 7 begins with 7.

#include <cstdio>
using namespace std;

// Function "next" determines if the current number in the hailstone 
// sequence, 'num' is even, odd, or 1, and then returns the next number
// in the hailstone sequence depending on if 'num' is even or odd

int next(int num)
{
    if (num%2 == 0)
    {
        return num/2;
    }
    else if (num == 1)
    {
        return num;
    }
    else
    {
        return ((num * 3) + 1);
    }
}

// Function "sequence" finds the next number in the hailstone sequence for
// 'num' until it reaches the final number in the sequence, 1.

void sequence (int num)
{
    int funcNum = num;
    while (!(funcNum == 1))
    {
        printf("%d ", funcNum);
        funcNum = next(funcNum);
    }
    printf("%d \n", funcNum);
}

// Function "length" counts how many numbers there are in 
// the hailstone sequence for 'num' and returns the length 
// of the hailstone sequence for 'num'.

int length(int num)
{
    int funcNum = num;
    int seqLength = 1;
    while (!(funcNum == 1))
    {
        funcNum = next(funcNum);
        seqLength++;
    }
    return seqLength;
}

// Function "largeNum" returns the largest number in the hailstone 
// sequence for 'num'.

int largeNum(int num)
{
    int hailstoneLarge, funcNum = num;
    while (!(funcNum == 1))
    {
        if (funcNum > hailstoneLarge)
        {
            hailstoneLarge = funcNum;
        }
        funcNum = next(funcNum);   
    }
    return hailstoneLarge;
}

// Function "longestHailstoneLength" determines the longest hailstone 
// sequence for all numbers between 1 and 'num', and then returns 
// the length of the longest hailstone sequence between 1 and 'num'.

int longestHailstoneLength (int num)
{
    int longestSequence = 0;
    for (int n = 1; n <= num; n++)
    {
        int nLength = length(n);
        if (nLength > longestSequence)
        {
            longestSequence = nLength;
        }
    }
    return longestSequence;
}

// Function "longestHailstoneNum" determines the longest hailstone sequence
// for all numbers between 1 and 'num' and then returns the 
// starting number of the longest sequence.

int longestHailstoneNum(int num)
{
    int longestSequence = 0;
    int biggestStart = 0;
    for (int n = 1; n <= num; n++)
    {
        int nLength = length(n);
        if (nLength > longestSequence)
        {
            biggestStart = n;
            longestSequence = nLength;
        }
    }
    return biggestStart;
}

int main()
{
    int num = 0;
    printf("What number shall I start with? ");
    scanf("%d", &num);
    printf("The hailstone sequence starting at %d is: \n", num);
    sequence(num);
    printf("The length of the sequence is %d.\n", length(num));
    printf("The largest number in the sequence is %d. \n", largeNum(num));

    printf("The longest hailstone sequence starting with a number up to");
    printf(" %d has length %d. \n", num, longestHailstoneLength(num));

    printf("The longest hailstone sequence starting with a number up to");
    printf(" %d begins with %d. \n", num, longestHailstoneNum(num));
    return 0;
}