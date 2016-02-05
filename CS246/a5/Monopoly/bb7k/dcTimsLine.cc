#include "dcTimsLine.h"

using namespace std;

//see header file
DcTimsLine::DcTimsLine(Game * game, int buildingNum)
{
	this->game = game;
	this->name = "COLLECTOSAP";
	this->buildingNum = buildingNum;
}

//see header file
void DcTimsLine::effect(Player * player){ }
