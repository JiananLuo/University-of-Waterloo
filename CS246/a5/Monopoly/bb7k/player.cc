#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "player.h"

using namespace std;

const int coopFee = 150;//the amount of coop fee
const int totalBuilding = 40;//total number of building

//see header file
Player::Player(Game * game, string name, char symbol, int money, int location, int cupOwn, bool atTimsLine, int atTimsTurn, map <string, OwnableBuilding *> **properties)
{
	this->game = game;
	this->name = name;
	this->symbol = symbol;

	this->money = money;
	this->location = location;
	this->cupOwn = cupOwn;
	this->atTimsLine = atTimsLine;
	this->atTimsTurn = atTimsTurn;

	this->rollTime = 0;
	//this->properties = properties;
}

//see header file
string Player::getName()
{
	return this->name;
}

//see header file
char Player::getSymbol()
{
	return this->symbol;
}

//see header file
int Player::getCup()
{
	return this->cupOwn;
}

//see header file
int Player::getMoney()
{
	return this->money;
}

//see header file
int Player::getLocation()
{
	return this->location;
}

//see header file
int Player::getRollTime()
{
	return this->rollTime;
}

//see header file
int Player::getTimsState()
{
	if(atTimsLine)
		return 1;
	else
		return 0;
}

//see header file
int Player::getTimsTurn()
{
	return atTimsTurn;
}

//see header file
void Player::changeCup(int amount)
{
	this->cupOwn += amount;
}

//see header file
void Player::changeMoney(int amount, Player * to)
{
	if(amount >= 0)
	{
		this->money += amount;
		cout << "You got $" <<  amount << "!" << endl;
		return;
	}
	while(true)
	{
		if(this->money >= amount * -1)
		{
			this->money += amount;
			if(to != NULL)
			{
				cout  << this->name << " paid $" << amount * -1 << " to " << to->getName() << "!" << endl;
				to->changeMoney(amount * -1);
				return;
			}
			else
			{
				cout << this->name << " paid $" << amount * -1 << " to the BANK!" << endl;
				return;
			}
		}
		else
		{
			cout << "You need to pay: " << amount * -1 << ", but since you don't have enough money, you must choose: " << endl;
			cout << "1. Drop out! (bankrupt)" << endl;
			cout << "2. Trade! (trade)" << endl;
			cout << "3. Mortgage buildings! (mortgage)" << endl;
			cout << "4. Sell improvements! (improve)" << endl;
			string command;
			cin >> command;
			if(command == "bankrupt")
			{
				this->bankrupt(to);
				return;
			}
			else if(command == "trade")
			{
				this->game->trade();
			}
			else if(command == "mortgage")
			{
				this->game->mortgage();
			}
			else if(command == "improve")
			{
				this->game->improve();
			}
			else
			{
				cout << "Wrong command, please try again!" << endl;
				continue;
			}
		}	
	}
}

//see header file
void Player::rollTimeAdd()
{
	this->rollTime++;
}

//see header file
void Player::rollTimeClear()
{
	this->rollTime = 0;
}

//see header file
void Player::goToTimsLine()
{
	this->game->notifyPlayer(this->symbol, location, '-');
	this->location = 10;
	this->game->notifyPlayer(this->symbol, location, '+', "play");
	this->atTimsLine = true;
	this->atTimsTurn = 0;
}

//see header file
void Player::goToCollectOsap()
{
	this->game->notifyPlayer(this->symbol, location, '-');
	this->location = 0;
	this->game->notifyPlayer(this->symbol, location, '+', "play");
	this->money += coopFee;
}

//see header file
void Player::timsLineTurn(char mode)
{
	srand (time(NULL));

	while(true)
	{
		cout << "1. Pay $50 (1)" << endl;
		cout << "2. Use a Roll Up the Rim cup (2)" << endl;
		if(this->atTimsTurn != 3)
		{
			cout << "3. Roll (roll)" << endl;
		}
		string action;
		cin >> action;
		if(cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Wrong command, please try again!" << endl;
			continue;
		}
		else if(action == "1")
		{
			this->changeMoney(-50);
			this->atTimsLine = false;
			this->atTimsTurn = 0;
			cout << "You have paid $50 to get out dc tims line, now you can move by rolling the dice!" << endl;
			break;
		}
		else if(action == "2")
		{
			if(this->cupOwn > 0)
			{
				this->cupOwn--;
				this->game->changeCup(1);
				this->atTimsLine = false;
				this->atTimsTurn = 0;
				cout << "You used cup to get out dc tims line, now you can move by rolling the dice!" << endl;
				break;
			}
			else
			{
				cout << "You don't have enough cup, please try again!" << endl;
				continue;
			}
		}
		else if((action == "roll") && (this->atTimsTurn != 3))
		{
			int a;
			int b;

			if(mode == 't')
			{
				cin >> a;
				if(cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Dice need to be a number between 1-6!" << endl;
					return;
				}
				cin >> b;
				if(cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Dice need to be a number between 1-6!" << endl;
					return;
				}
				if(max(a,b) > 6 || min(a,b) < 1)
				{
					cout << "Choose number between 1-6!" << endl;
					return;
				}
			}
			else
			{
				a = rand() % 6 + 1;
				b = rand() % 6 + 1;
			}


			if(a != b)
			{
				this->atTimsTurn++;
				cout << "You didn't roll double! Still stay tims line!" << endl;
				this->game->rolledDice();
				break;
			}
			else
			{
				this->atTimsLine = false;
				this->atTimsTurn = 0;
				cout << "You rolled double! Get out from tims line, now you can move by rolling the dice!" << endl;
				break;
			}
		}
		else
		{
			cout << "Wrong command, please try again!" << endl;
			continue;
		}
	}
	
}

//see header file
void Player::changeBuilding(string buildingName, char action)
{
	if(action == '+')
	{
		properties[buildingName] = static_cast<OwnableBuilding *>(game->getBuilding(buildingName));
	}
	else if(action == '-')
	{
		properties.erase(buildingName);
	}
	else
	{
		cout << "Error: Not possiable! (changeMortgage)" << endl;
	}
}

//see header file
void Player::changeImprove(string buildingName, char action)
{
	if(properties.find(buildingName) == properties.end())
	{
		cout << "Building does not belong to you / doesn't exist!" << endl;
		return;
	}
	if(action == '+')
	{
		this->properties[buildingName]->buyImprovement();
	}
	else if(action == '-')
	{
		this->properties[buildingName]->sellImprovement();
	}
	else
	{
		cout << "Error: Not possiable! (changeMortgage)" << endl;
	}
}

//see header file
void Player::changeMortgage(char action)
{
	string buildingName;
	cin >> buildingName;
	if(properties.find(buildingName) == properties.end())
	{
		cout << "Building does not belong to you / doesn't exist!" << endl;
		return;
	}
	if(action == '+')
	{
		this->properties[buildingName]->mortgage();
	}
	else if(action == '-')
	{
		this->properties[buildingName]->unmortgage();
	}
	else
	{
		cout << "Error: Not possiable! (changeMortgage)" << endl;
	}
}

//see header file
bool Player::checkProperty(string buildingName)
{
	for (map<string, OwnableBuilding *>::iterator it = properties.begin(); it != properties.end(); ++it)
	{
		if(it->first == buildingName)
		{
			return true;
		}
	}
	return false;
}

//see header file
void Player::assets()
{
	cout << "Name: " << this->name << endl;
	cout << "Moeny: " << this->money << endl;
	cout << "Properties:";
	for (map<string, OwnableBuilding *>::iterator it = properties.begin(); it != properties.end(); ++it)
	{
		cout << " " << it->first;
	}
	cout << endl;
}

//see header file
int Player::getTotalValue()
{
	int totalValue = this->money;
	for (map<string, OwnableBuilding *>::iterator it = properties.begin(); it != properties.end(); ++it)
	{
		totalValue += it->second->getBuildingValue();
	}
	
	return totalValue;
}

//see header file
void Player::bankrupt(Player * to)
{
	this->game->bankrupt();

	int numProperty = 0;
	for (map<string, OwnableBuilding *>::iterator it = properties.begin(); it != properties.end(); ++it)
	{
		numProperty++;
	}

	string tempProperty[totalBuilding];

	int counter = 0;
	for (map<string, OwnableBuilding *>::iterator it = properties.begin(); it != properties.end(); ++it)
	{
		tempProperty[counter] = it->first;
		counter++;
	}

	if(to != NULL)
	{
		for(int i=0; i<counter; i++)
		{
			dynamic_cast<OwnableBuilding *>(this->game->getBuilding(tempProperty[i]))->setOwner(to);
		}
		to->changeMoney(this->money);
	}
	else
	{
		for(int i=0; i<counter; i++)
		{
			dynamic_cast<OwnableBuilding *>(this->game->getBuilding(tempProperty[i]))->auction();
		}
	}

	this->game->playerOut();
}

//see header file
void Player::move(int steps)
{
	this->game->notifyPlayer(this->symbol, location, '-');
	this->location += steps;
	
	if(this->location > 39)
	{
		if(this->location > totalBuilding)
		{
			this->game->buildingEffect(0);
		}
		this->location -= totalBuilding;
	}
	this->game->notifyPlayer(this->symbol, this->location, '+', "play");

	if(steps > 0)
		cout << "You moved " << steps << " steps forward!" << endl;
	else
		cout << "You moved " << steps * -1 << " steps backward!" << endl;

	this->game->buildingEffect(this->location);
}
