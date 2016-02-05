#include <iostream>
#include <string>
#include "academic.h"
#include "game.h"

using namespace std;

//see header file
Academic::Academic(Game * game, string name, int buildingNum, string monopolyBlock, int purchaseCost, int improvementCost, int tuition0, int tuition1, int tuition2, int tuition3, int tuition4, int tuition5, Player * owner, int improvementLevel)
{
	this->game = game;
	this->name = name;
	this->buildingNum = buildingNum;
	this->monopolyBlock = monopolyBlock;
	this->purchaseCost = purchaseCost;
	this->improvementCost = improvementCost;
	this->tuitionAtImprovements[0] = tuition0;
	this->tuitionAtImprovements[1] = tuition1;
	this->tuitionAtImprovements[2] = tuition2;
	this->tuitionAtImprovements[3] = tuition3;
	this->tuitionAtImprovements[4] = tuition4;
	this->tuitionAtImprovements[5] = tuition5;

	this->owner = owner;
	this->improvementLevel = improvementLevel;
}

//see header file
void Academic::buyImprovement()
{
	if(this->checkMonopoly() == false)
	{
		cout << "You can't buy any improvements, since this block is not a monopoly yet!" << endl;
	}
	else if(this->improvementLevel == maxLevel)
	{
		cout << "Already at maximum level, no more improvement to buy!" << endl;
	}
	else if(this->owner->getMoney() < this->improvementCost)
	{
		cout << "You don't have enough money to buy any improvements!" << endl;
	}
	else
	{
		owner->changeMoney(this->improvementCost * buyImprovementRatio);
		this->improvementLevel++;
		this->game->notifyBuilding(this->improvementLevel, this->buildingNum, "play");
		cout << "You successfully upgrade: " <<  this->getName() << "!" << endl;
	}
}

//see header file
void Academic::sellImprovement()
{
	if(this->improvementLevel == minLevel)
	{
		cout << "Already at minimum level, no more improvement to sell!" << endl;
	}
	else
	{
		owner->changeMoney(this->improvementCost * sellImprovementRatio);
		this->improvementLevel--;
		this->game->notifyBuilding(this->improvementLevel, this->buildingNum, "play");
		cout << "You successfully sold improvement!" << endl;
	}
}

//see header file
int Academic::getBuildingValue()
{
	return this->purchaseCost + this->improvementLevel * this->improvementCost;
}

//see header file
int Academic::payAmount()
{
	if(checkMonopoly() && improvementLevel == minLevel)
	{
		return this->tuitionAtImprovements[improvementLevel] * monopolyNoImprovementRatio;
	}
	return this->tuitionAtImprovements[improvementLevel];
}

//see header file
void Academic::ownerBankrupt()
{
	this->owner = NULL;
	this->improvementLevel = minLevel;
}
