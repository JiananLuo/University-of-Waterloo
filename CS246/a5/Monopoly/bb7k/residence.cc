#include <iostream>
#include <string>
#include "residence.h"

using namespace std;

//see header file
Residence::Residence(Game * game, string name, int buildingNum, int improvementLevel, Player * owner, int purchaseCost)
{
	this->monopolyBlock = "Residence";

	this->game = game;
	this->name = name;
	this->buildingNum = buildingNum;
	this->purchaseCost = purchaseCost;
	this->improvementLevel = improvementLevel;

	this->owner = owner;

	residenceRentAmount[0] = 25;
	residenceRentAmount[1] = 50;
	residenceRentAmount[2] = 100;
	residenceRentAmount[3] = 200;
}

//see header file
void Residence::buyImprovement()
{
	cout << "You can't buy improvement for residence!" << endl;
	return;
}
//see header file
void Residence::sellImprovement()
{
	cout << "You can't sell improvement for residence!" << endl;
	return;
}

//see header file
int Residence::getBuildingValue()
{
	return this->purchaseCost;
}

//see header file
int Residence::payAmount()
{
	char piece = this->owner->getSymbol();
	int numResidenceMonopoly = -1;
	if(this->game->getOwnerSymbol(5) == piece)
		numResidenceMonopoly++;
	if(this->game->getOwnerSymbol(15) == piece)
		numResidenceMonopoly++;
	if(this->game->getOwnerSymbol(25) == piece)
		numResidenceMonopoly++;
	if(this->game->getOwnerSymbol(35) == piece)
		numResidenceMonopoly++;
	return residenceRentAmount[numResidenceMonopoly];
}

//see header file
void Residence::ownerBankrupt()
{
	this->owner = NULL;
}
