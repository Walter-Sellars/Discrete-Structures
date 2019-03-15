// CSCI 2530
// Assignment: 3
// Author:     Walter Sellars
// File:       hailstone.cpp
// Tab stops:  4

// Given the input integer 'num', "Hailstone" prints the full sequence,
// the length of the sequence, the largest number in the sequence,
// the longest hailstone sequence for all numbers between 1 and 'num',
// and the number that the longest sequence begins with.
//
// Example - input of 7
// What number shall I start with? 7
// The hailstone sequence starting at 7 is :
// 7 22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1
// The length of the sequence is 17.
// The largest number in the sequence is 52.
// The longest hailstone sequence starting with a number up to 7 has length 17.
// The longest hailstone sequence starting with a number up to 7 begins with 7.
#include <algorithm>
#include <cstdio>
using namespace std;

// Function "next" returns the number in the hailstone
// sequence that follows 'num'

int next(int num)
{
    if (num % 2 == 0)
    {
        return num / 2;
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

// Function "sequence" writes the hailstone sequence 
// for 'num' starting at 'num'.

void sequence(int num)
{
    if (num == 1)
    {
        printf("%d \n", num);
        return;
    }
    else
    {
        printf("%d ", num);
        sequence(next(num));
    }
}

// Function "length" returns the length of the hailstone sequence for 'num'.

int length(int num)
{
    int count = 1;
    if (num == 1)
    {
        return 1;
    }
    else
    {
        return count + length(next(num));
    }
}

// Function "largeNum" returns the largest number in the hailstone
// sequence for 'num'.

int largeNum(int num)
{
    
    if (num > 1)
    {
        int largest = largeNum(next(num));
        if (largest > num)
        {
            return largest;
        }
        else
        {
            return num;
        }
    }
    else
    {
        return 1;
    }
}


// Function "longestHailstoneLength" returns the length of longest
// hailstone sequence for all numbers between 1 and 'num'.

int longestHailstoneLength(int num)
{
    if(num>1)
    {
        int longest = longestHailstoneLength(num - 1);
        if(longest > length(num))
        {
            return longest;
        }
        else
        {
            return length(num);
        }
    }
    else
    {
        return 1;
    }
}

// Function "longestHailstoneNum" returns the starting number of the longest 
// hailstone sequence for all numbers between 1 and 'num'.

int longestHailstoneNum(int num)
{
    if (num > 1)
    {
        int check = longestHailstoneNum(num - 1);
        if (length(num) > length(check))
        {
            return num;
        }
        else
        {
            return check;
        }
    }
    else
    {
        return 1;
    }
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