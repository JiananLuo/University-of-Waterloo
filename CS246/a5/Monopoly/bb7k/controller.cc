#include <cstdlib>
#include <ctime>
#include <cctype>
#include <iostream>

#include "controller.h"

using namespace std;

int exitState = 0;
int zeroPlayerLeft = 0;
int onePlayerLeft = 1;

//see header file
Controller::Controller()
{	
	this->td = new TextDisplay();
	this->game = new Game(this);

	this->rolled = false;
}

//see header file
void Controller::init()
{
	
	this->td->init();
	this->game->init();
	td->print();//print the game board after game start
}

//see header file
void Controller::load(string file)
{
	this->td->init();
	this->game->load(file);
	td->print();
}

//see header file
void Controller::notifyPlayer(char piece, int buildingNum, char active, std::string mode)
{
	td->notifyPlayer(piece, buildingNum, active, mode);
}

//see header file
void Controller::notifyBuilding(int level, int buildingNum, std::string mode)
{
	td->notifyBuilding(level, buildingNum, mode);
}

//see header file
void Controller::rolledDice()
{
	this->rolled = true;
}
void Controller::rolledClear()
{
	this->rolled = false;
}
//see header file
void Controller::play(char mode)
{
	srand(time(NULL));
	
	if(this->game->getNumPlayer() <= zeroPlayerLeft)
	{
		cout << "0 player, game finished!" << endl;
		return;
	}
	
	checkWin();
	
	string command;

	while(cin >> command)
	{
		if(command == "roll")
		{
			if(rolled == true)
			{
				cout << "You can't roll again!" << endl;
				continue;
			}
			game->roll(mode);
		}
		else if(command == "next")
		{
			if(rolled == false)
			{
				cout << "You have not roll yet!" << endl;
				continue;
			}
			rolled = false;
			game->next();
		}
		else if(command == "trade")
		{
			game->trade();
		}
		else if(command == "improve")
		{
			game->improve();
		}
		else if(command == "mortgage")
		{
			game->mortgage();
		}
		else if(command == "unmortgage")
		{
			game->unmortgage();
		}
		else if(command == "bankrupt")
		{
			cout << "You can use this command right now!" << endl;
		}
		else if(command == "assets")
		{
			game->assets();
		}
		else if(command == "save")
		{
			game->save();
		}
		else if(command == "quit")
		{
			return;
		}
		else
		{
			cout << "Wrong command, please try again!" << endl;
		}
	}

	delete td;
	delete game;
}

//see header file
void Controller::checkWin()
{
	if(game->getNumPlayer() == onePlayerLeft)
	{
		cout << "Congratualtions you win!" << endl;
		delete td;
		delete game;
		exit(exitState);
	}
}
