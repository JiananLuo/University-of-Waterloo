#include "goToTims.h"

using namespace std;

//see header file
GoToTims::GoToTims(Game * game, int buildingNum)
{
	this->game = game;
	this->name = "GOTOTIMS";
	this->buildingNum = buildingNum;
}

//see header file
void GoToTims::effect(Player * player)
{
	player->goToTimsLine();
}
