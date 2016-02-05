#include <iostream>
#include <cstdlib>
#include <ctime>

#include "slc.h"

using namespace std;

//see header file
Slc::Slc(Game * game, int buildingNum)
{
	this->game = game;
	this->name = "SLC";
	this->buildingNum = buildingNum;//either 2, 17, 33
}

//see header file
void Slc::effect(Player * player)
{
	//check cup
	srand (time(NULL));
	
	if(this->game->cupLeft() > 0)
	{
		int rareRan = rand() % 100 + 1;
		if(rareRan == 1)
		{
			player->changeCup(1);
			this->game->changeCup(-1);
			return;
		}
	}

	int normalRan = rand() % 24 + 1;
	if(normalRan <= probabilityBack3)
	{
		player->move(-3);
	}
	else if(normalRan <= probabilityBack2)
	{
		player->move(-2);
	}
	else if(normalRan <= probabilityBack1)
	{
		player->move(-1);
	}
	else if(normalRan <= probabilityForward3)
	{
		player->move(3);
	}
	else if(normalRan <= probabilityForward2)
	{
		player->move(2);
	}
	else if(normalRan <= probabilityForward1)
	{
		player->move(1);
	}
	else if(normalRan <= probabilityGoToTims)
	{
		player->goToTimsLine();
		cout << "Go to DC Tims Line!" << endl;
	}
	else if(normalRan <= probabilityCollectOSAP)
	{
		player->goToCollectOsap();
		cout << "Advance to Collect OSAP!" << endl;
	}
	else
	{
		cout << "Not possiable (SLC)!" << endl;
		return;
	}
}
