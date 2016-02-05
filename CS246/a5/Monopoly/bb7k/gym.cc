#include <iostream>
#include <string>
#include "gym.h"

using namespace std;

//see header file
Gym::Gym(Game * game, string name, int buildingNum, int improvementLevel, Player * owner, int purchaseCost)
{
	this->monopolyBlock = "Gym";

	this->game = game;
	this->name = name;
	this->buildingNum = buildingNum;
	this->purchaseCost = purchaseCost;
	this->improvementLevel = improvementLevel;

	this->owner = owner;

	gymFeeMultiple[0] = 4;
	gymFeeMultiple[1] = 10;
}

//see header file
void Gym::buyImprovement()
{
	cout << "You can't buy improvement for gym!" << endl;
	return;
}

//see header file
void Gym::sellImprovement()
{
	cout << "You can't sell improvement for gym!" << endl;
	return;
}

//see header file
int Gym::getBuildingValue()
{
	return this->purchaseCost;
}

//see header file
int Gym::payAmount()
{
	char piece = this->owner->getSymbol();
	int numGymMonopoly = -1;
	if(this->game->getOwnerSymbol(12) == piece)
		numGymMonopoly++;
	if(this->game->getOwnerSymbol(28) == piece)
		numGymMonopoly++;
	int mult = this->game->rollInt() + this->game->rollInt();
	return gymFeeMultiple[numGymMonopoly] * mult;
}

//see header file
void Gym::ownerBankrupt()
{
	this->owner = NULL;
}
