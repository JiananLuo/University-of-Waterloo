#include <iostream>
#include <string>

#include "ownableBuilding.h"

using namespace std;

//see header file
void OwnableBuilding::setOwner(Player * to, string mode)
{
	if(this->owner != NULL)
	{
		this->owner->changeBuilding(this->getName(), '-');
		this->owner = NULL;
	}

	if(to != NULL)
	{
		to->changeBuilding(this->getName(), '+');
		this->owner = to;

		if(mode == "play" && this->improvementLevel == -1)
		{
			int immediatelyFee = this->purchaseCost * immdeiatelyFeeRatio;
			to->changeMoney(immediatelyFee * -1);
		}
	}
}

//see header file
void OwnableBuilding::mortgage()
{
	if(this->improvementLevel > 0)
		cout << "Improvements must be sold before a building can be mortgaged!" << endl;
	else if(this->game->checkMonopolyNoImprovement(this->name))
		cout << "All the improvements in this monopoly must be sold before the building can be mortgaged!" << endl;
	else if(this->improvementLevel == 0)
	{
		this->improvementLevel = -1;
		this->owner->changeMoney(this->purchaseCost * mortgageRatio);
	}
	else
		cout << "This building is currently mortgaged!" << endl;
}

//see header file
void OwnableBuilding::unmortgage()
{
	if(this->improvementLevel == -1)
	{
		int unmortgageCost = this->purchaseCost * unmortgageRatio;
		if(owner->getMoney() >= unmortgageCost)
		{
			this->improvementLevel = 0;
			this->owner->changeMoney(unmortgageCost * -1);
		}
		else
			cout << "You don't have enough money to unmortgaged this building!" << endl;
	}
	else
		cout << "This building is not mortgaged!" << endl;
}

//see header file
bool OwnableBuilding::checkMonopoly()
{
	char piece = this->owner->getSymbol();
	if(monopolyBlock == "Arts1")
		return (this->game->getOwnerSymbol(1) == piece && this->game->getOwnerSymbol(3) == piece);
	else if(monopolyBlock == "Arts2")
		return (this->game->getOwnerSymbol(6) == piece && this->game->getOwnerSymbol(8) == piece && this->game->getOwnerSymbol(9) == piece);
	else if(monopolyBlock == "Eng")
		return (this->game->getOwnerSymbol(11) == piece && this->game->getOwnerSymbol(13) == piece && this->game->getOwnerSymbol(14) == piece);
	else if(monopolyBlock == "Health")
		return (this->game->getOwnerSymbol(16) == piece && this->game->getOwnerSymbol(18) == piece && this->game->getOwnerSymbol(19) == piece);
	else if(monopolyBlock == "Env")
		return (this->game->getOwnerSymbol(21) == piece && this->game->getOwnerSymbol(23) == piece && this->game->getOwnerSymbol(24) == piece);
	else if(monopolyBlock == "Sci1")
		return (this->game->getOwnerSymbol(26) == piece && this->game->getOwnerSymbol(27) == piece && this->game->getOwnerSymbol(29) == piece);
	else if(monopolyBlock == "Sci2")
		return (this->game->getOwnerSymbol(31) == piece && this->game->getOwnerSymbol(33) == piece && this->game->getOwnerSymbol(34) == piece);
	else if(monopolyBlock == "Math")
		return (this->game->getOwnerSymbol(37) == piece && this->game->getOwnerSymbol(39) == piece);
	else if(monopolyBlock == "Residence")
		return (this->game->getOwnerSymbol(5) == piece && this->game->getOwnerSymbol(15) == piece && this->game->getOwnerSymbol(25) == piece && this->game->getOwnerSymbol(35) == piece);
	else if(monopolyBlock == "Gym")
		return (this->game->getOwnerSymbol(12) == piece && this->game->getOwnerSymbol(28) == piece);
	else
	{
		cout << "Error! Not possiable!" << endl;
		return false;
	}
}

//see header file
void OwnableBuilding::auction()
{
	if(this->improvementLevel != 0)
	{
		this->improvementLevel = 0;
		this->game->notifyBuilding(this->improvementLevel, this->buildingNum, "play");
		cout << "Building improvements destroyed!" << endl;
	}
	this->game->auction(this, this->purchaseCost);
}

//see header file
int OwnableBuilding::getBuildingLevel()
{
	return improvementLevel;
}

//see header file
string OwnableBuilding::getBuildingMono()
{
	return monopolyBlock;
}

string bank = "BANK";
//see header file
string OwnableBuilding::getOwnerName()
{
	if (this->owner == NULL)
	{
		return bank;
	}
	return this->owner->getName();
}

char nullOwner = ' ';
//see header file
char OwnableBuilding::getOwnerSymbol()
{
	if(this->owner == NULL)
	{
		return nullOwner;
	}
	else
	{
		return this->owner->getSymbol();
	}
}

//see header file
void OwnableBuilding::effect(Player * player)
{
	if(this->owner == NULL)
	{
		if(player->getMoney() < this->purchaseCost)
		{
			cout << "Don't have enough money to buy!" << endl;
			cout << "Auction:" << endl;
			this->auction();
		}
		else
		{
			while(true)
			{
				cout << this->getName() << " Purchase Cost: " << this->purchaseCost << " yes/no (y/n)?" << endl;
				string command;
				cin >> command;
				
				if(command == "y")
				{
					player->changeMoney(this->purchaseCost * -1);
					this->setOwner(player);
					cout << "You have bought this building!" << endl;
					break;
				}
				else if(command == "n")
				{
					cout << "You didn't buy this building, auction!" << endl;
					this->auction();
					break;
				}
				else
				{
					cout << "wrong command, please check again!" << endl;
				}
			}
		}
	}
	else if(this->improvementLevel == -1)
	{
		cout << "This building is currently mortgaged, don't need to pay money!" << endl;
		return;
	}
	else if(player->getName() != owner->getName())
	{
		if(monopolyBlock == "Residence" || monopolyBlock == "Gym")
			player->changeMoney(this->payAmount() * -1, this->owner);
		else
			player->changeMoney(this->payAmount() * -1);
	}
	else
	{
		cout << "Hello owner!" << endl;
		return;
	}
}
