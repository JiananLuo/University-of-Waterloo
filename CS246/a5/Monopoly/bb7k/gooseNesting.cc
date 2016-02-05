#include <iostream>

#include "gooseNesting.h"

using namespace std;

//see header file
GooseNesting::GooseNesting(Game * game, int buildingNum)
{
	this->game = game;
	this->name = "GOOSENESTING";
	this->buildingNum = buildingNum;
}

//see header file
void GooseNesting::effect(Player * player)
{
	cout << "You are attacking by goose, but nothing happend!" << endl;
}
