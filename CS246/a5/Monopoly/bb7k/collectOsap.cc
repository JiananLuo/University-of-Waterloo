#include "collectOsap.h"

using namespace std;

//see header file
CollectOsap::CollectOsap(Game * game, int buildingNum)
{
	this->game = game;
	this->name = "COLLECTOSAP";
	this->buildingNum = buildingNum;
}

//see header file
void CollectOsap::effect(Player * player)
{
	player->changeMoney(moneyCollect);
}
