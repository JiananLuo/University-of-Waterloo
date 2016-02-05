#include <iostream>
#include <cstdlib>
#include <ctime>

#include "needlesHall.h"

using namespace std;

//see header file
NeedlesHall::NeedlesHall(Game * game, int buildingNum)
{
	this->game = game;
	this->name = "NEEDLESHALL";
	this->buildingNum = buildingNum;//either7, 22, 36
}

//see header file
void NeedlesHall::effect(Player * player)
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
	
	int normalRan = rand() % 18 + 1;

	int amount;
	if(normalRan <= probabilityOSAP_N200)
	{
		player->changeMoney(AmountOSAP_N200);
		amount = AmountOSAP_N200;
	}
	else if(normalRan <= probabilityOSAP_N100)
	{
		player->changeMoney(AmountOSAP_N100);
		amount = AmountOSAP_N100;
	}
	else if(normalRan <= probabilityOSAP_N50)
	{
		player->changeMoney(AmountOSAP_N50);
		amount = AmountOSAP_N50;
	}
	else if(normalRan <= probabilityOSAP_P25)
	{
		player->changeMoney(AmountOSAP_P25);
		amount = AmountOSAP_P25;
	}
	else if(normalRan <= probabilityOSAP_P50)
	{
		player->changeMoney(AmountOSAP_P50);
		amount = AmountOSAP_P50;
	}
	else if(normalRan <= probabilityOSAP_P100)
	{
		player->changeMoney(AmountOSAP_P100);
		amount = AmountOSAP_P100;
	}
	else if(normalRan <= probabilityOSAP_P200)
	{
		player->changeMoney(AmountOSAP_P200);
		amount = AmountOSAP_P200;
	}
	else
	{
		cout << "Not possiable (NEEDLESHALL)!" << endl;
		return;
	}
}
