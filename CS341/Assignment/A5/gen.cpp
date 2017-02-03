/*Steven Billington
January 17, 2003
Ranexample.cpp
Program displays three random integers.
*/
/*
Header: iostream
Reason: Input/Output stream
Header: cstdlib
Reason: For functions rand and srand
Header: time.h
Reason: For function time, and for data type time_t
*/
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
/*
Declare variable to hold seconds on clock.
*/
time_t seconds;
/*
Get value from system clock and
place in seconds variable.
*/
time(&seconds);
int high=10;
/*
Convert seconds to a unsigned
integer.
*/
srand((unsigned int) seconds);
/*
Output random values.
*/
ofstream myfile;
myfile.open ("game.txt");
int length;
cin>>length;
myfile<<length<<"\n";
for(int i=0;i<length;++i){
myfile<< rand()%high+1 << " " <<rand()%high+1<<"\n";
}
return 0;
}

