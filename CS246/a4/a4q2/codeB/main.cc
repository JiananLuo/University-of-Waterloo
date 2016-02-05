#include "controller.h"
#include <iostream>
using namespace std;

//main function
int main (int argc, char *argv[])
{
	Controller c;
	string arg = argv[1];
	if((argc == 2) && (arg == "-graphics"))
	{
		c.play('g');
	}
	else
	{
		c.play();
	}
}
