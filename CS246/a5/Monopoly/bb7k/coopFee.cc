#include "coopFee.h"

using namespace std;

//see header file
CoopFee::CoopFee(Game * game, int buildingNum)
{
	this->game = game;
	this->name = "COOPFEE";
	this->buildingNum = buildingNum;
}

//see header file
void CoopFee::effect(Player * player)
{
	player->changeMoney(coopFee * -1);
}
