/** CSCI 2530
 Assignment: 1
 Author:     Walter Sellars
 File:       closest.cpp
 Tab stops:  4
	
This program reads 3 input coordinate in the form of (x1,y1), (x2,y2) and (x3,y3), 
then calculates the distance between the points and displays (x1, y1) and (x2,y2) 
if they are the closest two points.

The program should show, on the standard output,
the three points that were read,
the two of the three points that are closest together, and
the distance between those two closest points.

For example, if the input is

  1.0 3.0 1.5 7.2 4.0 2.0

then the output should be

The three points are:
     1.000      3.000
     1.500      7.200
     4.000      2.000

The closest two points are:
     1.000      3.000
     4.000      2.000

The distance between those two points is:      3.162
**/

#include <cstdio>
#include <math.h>
using namespace std;

//******************************************************
//                    EchoInput
//******************************************************
// The fucntion EchoInput(x1,y1,x2,y2, x3, y3) displays 
// the given input coordinates (x1,y1), (x2,y2), 
// and (x3,y3) on the standard output.
//******************************************************

void echoInput(double x1, double y1, double x2, double y2, double x3, double y3)
{
  printf("The three points are:\n");
  printf("%10.3lf %10.3lf\n", x1, y1);
  printf("%10.3lf %10.3lf\n", x2, y2);
  printf("%10.3lf %10.3lf\n\n", x3, y3);
}

//******************************************************
//                    Distance
//******************************************************
// The function distance(x1,y1,x2,y2) returns 
// the distance between (x1,y1) and (x2,y2). 
//******************************************************

double distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2-x1,2) + pow(y2-y1, 2));
}

//******************************************************
//						showOutput
//******************************************************
// Function take vars 'x1 y1 x2 y2' and 'dist' and prints 
// them to output with proper spacing of 10 front 3 behind
//******************************************************

void showOutput( double x1, double y1, double x2, double y2,double dist)
{
	printf("The closest two points are:\n%10.3lf%10.3lf\n%10.3lf%10.3lf\n",x1,y1,x2,y2);
	printf("The distance between those two points is:%10.3lf\n", dist);
}

//******************************************************
//                    consider
//******************************************************
// This function determines if the distance between (x1,y1) and (x2,y2) is shorter than the distances 
// of the other possible combinations ((x1,y1) to (x3,y3)) and ((x2,y2) to (x3,y3)).
// If the distance between the first two coordinates is equal or less thas that of the other possible combinations
// it calls the showOutput function and prints that coordinate set and the distance between them.
//******************************************************

void consider(double x1,double y1,double x2,double y2,double x3,double y3)
{
	double distSet1 = distance(x1,y1,x2,y2);
	double distSet2 = distance(x1,y1,x3,y3);
	double distSet3 = distance(x2,y2,x3,y3);

	if((distSet1 <= distSet2) && (distSet1 <= distSet3))
	{
		showOutput(x1,y1,x2,y2,distSet1);
	}
}

//***********
//	  Main
//***********

int main(){
	double x1, y1, x2, y2, x3, y3;

	printf ("Please input three sets of coordinates in the form of x1, y1, x2, y2, x3, y3 \n");
	int input = scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3);
	if(input != 6)
	{
		printf("Incorrect number of coordinates. Please input 6 numbers in the form of x1, y1, x2, y2, x3, y3");
		return 1;
	}
	else
	{
		echoInput(x1,y1,x2,y2,x3,y3);
		consider(x1,y1,x2,y2,x3,y3);
		consider(x1,y1,x3,y3,x2,y2);
		consider(x2,y2,x3,y3,x1,y1);
	}
  return 0;
}
