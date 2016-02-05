#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "controller.h"

using namespace std;

int badReturnState = -1;

void newOrLoadGame()
{
	std::cout << "";
}
int main (int argc,char *argv[])
{
	bool testingMode = false;

	Controller c;
	if(argc == 1)
	{
		c.init();
	}
	else if(argc == 2)
	{
		string mode = argv[1];
		if(mode == "-testing")
		{
			c.init();
			testingMode = true;
		}
		else
		{
			cout << "Wrong argument, game exit!" << endl;
			return badReturnState;
		}
	}
	else if(argc == 3)
	{
		string mode = argv[1];
		if(mode == "-load")
		{
			string arg2 = argv[2];
			ifstream file(arg2.c_str());
			if (file)
			{
				c.load(arg2);
			}
			else
			{
				cout << "File doesn't exists!" << endl;
				return badReturnState;
			}
		}
		else
		{
			cout << "Wrong argument, game exit!" << endl;
			return badReturnState;
		}

	}
	else if(argc == 4)
	{
		testingMode = true;

		string arg1 = argv[1];
		string arg2 = argv[2];
		string arg3 = argv[3];
		if(arg1 == "-load")
		{
			if(arg3 == "-testing")
			{
				ifstream file(arg2.c_str());
				if (file)
				{
					c.load(arg2);
				}
				else
				{
					cout << "File doesn't exists!" << endl;
					return badReturnState;
				}
			}
		}
		else if(arg1 == "-testing")
		{
			if(arg2 == "-load")
			{
				ifstream file(arg3.c_str());
				if (file)
				{
					c.load(arg3);
				}
				else
				{
					cout << "File doesn't exists!" << endl;
					return badReturnState;
				}
			}
		}
		else
		{
			cout << "Wrong argument, game exit!" << endl;
			return badReturnState;
		}
	}
	else
	{
		cout << "Wrong argument, game exit!" << endl;
		return badReturnState;
	}
	if(testingMode == true)
		c.play('t');
	else
		c.play();
}
