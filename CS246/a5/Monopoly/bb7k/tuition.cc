#include "tuition.h"

using namespace std;

//see header file
Tuition::Tuition(Game * game, int buildingNum)
{
	this->game = game;
	this->name = "TUITION";
	this->buildingNum = buildingNum;
}

//see header file
void Tuition::effect(Player * player)
{
	cout << "Choose a way to pay your tuition: " << endl;
	cout << "1. paying $300 tuition" << endl;
	cout << "2. 10%% of your total worth (including your savings, printed prices of all buildings you own, and costs of each improvement)" << endl;
	int command;
	while(true)
	{
		cin >> command;
		if(cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Error command please try again!" << endl;
		}
		else
		{
			if(command == 1)
			{
				player->changeMoney(tuitionAmout * -1);
				break;
			}
			else if(command == 2)
			{
				player->changeMoney(player->getTotalValue() * tuitionPresent * -1);
				break;
			}
			else
			{
				cout << "Error command please try again!" << endl;
			}
		}
	}
}
