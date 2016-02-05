#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "game.h"
#include "ownableBuilding.h"
#include "academic.h"
#include "residence.h"
#include "gym.h"
#include "collectOsap.h"
#include "dcTimsLine.h"
#include "goToTims.h"
#include "gooseNesting.h"
#include "tuition.h"
#include "coopFee.h"
#include "slc.h"
#include "needlesHall.h"

using namespace std;

//see header file
Game::Game(Controller *controller)
{
	this->controller = controller;
	this->numPlayer = 0;
	this->totalPlayer = numPlayer;
	this->currentPlayer = 0;
	this->cupAvailable = 4;

	this->pieceAvailable[0] = 'G';
	this->pieceAvailable[1] = 'B';
	this->pieceAvailable[2] = 'D';
	this->pieceAvailable[3] = 'P';
	this->pieceAvailable[4] = 'S';
	this->pieceAvailable[5] = '$';
	this->pieceAvailable[6] = 'L';
	this->pieceAvailable[7] = 'T';

	player = NULL;

	building = new Building * [40];
	for(int i=0; i<40; i++)
	{
		building[i] = NULL;
	}
	building[0] = new CollectOsap(this, 0);
	building[10] = new DcTimsLine(this, 10);
	building[30] = new GoToTims(this, 30);
	building[20] = new GooseNesting(this, 20);
	building[4] = new Tuition(this, 4);
	building[38] = new CoopFee(this, 38);
	building[2] = new Slc(this, 2);
	building[17] = new Slc(this, 17);
	building[33] = new Slc(this, 33);
	building[7] = new NeedlesHall(this, 7);
	building[22] = new NeedlesHall(this, 22);
	building[36] = new NeedlesHall(this, 36);
}

//see header file
Game::~Game()
{
	delete [] player;
	delete [] building;
}

//see header file
void Game::init()
{
	int num;
	cout << "How many player?" << endl;
	while(true)
	{
		cin >> num;
		if(cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Wrong command, please try again!" << endl;
			continue;
		}
		else
		{
			if(num > -1 || num < 9)
			{
				this->numPlayer = num;
				break;
			}
			else
			{
				cout << "Choose a number between 0 - 8!" << endl;
				continue;
			}
		}
	}

	player = new Player * [this->numPlayer];
	this->totalPlayer = this->numPlayer;
	for(int i=0; i< numPlayer; i++)
	{
		cout << "Please give name and piece!" << endl;
		string name;
		char piece;
		cin >> name >> piece;
		player[i] = new Player(this, name, piece);
		this->notifyPlayer(piece, 0, '+', "load");
	}



	building[1] = new Academic(this, "AL", 1, "Arts1", 40, 50, 2, 10, 30, 90, 160, 250);
	building[3] = new Academic(this, "ML", 3, "Arts1", 60, 50, 4, 20, 60, 180, 320, 450);
	building[6] = new Academic(this, "ECH", 6, "Arts2", 100, 50, 6, 30, 90, 270, 400, 550);
	building[8] = new Academic(this, "PAS", 8, "Arts2", 100, 50, 6, 30, 90, 270, 400, 550);
	building[9] = new Academic(this, "HH", 9, "Arts2", 120, 50, 8, 40, 100, 300, 450, 600);
	building[11] = new Academic(this, "RCH", 11, "Eng", 140, 100, 10, 50, 150, 450, 625, 750);
	building[13] = new Academic(this, "DWE", 13, "Eng", 140, 100, 10, 50, 150, 450, 625, 750);
	building[14] = new Academic(this, "CPH", 14, "Eng", 160, 100, 12, 60, 180, 500, 700, 900);
	building[16] = new Academic(this, "LHI", 16, "Health", 180, 100, 14, 70, 200, 550, 750, 950);
	building[18] = new Academic(this, "BMH", 18, "Health", 180, 100, 14, 70, 200, 550, 750, 950);
	building[19] = new Academic(this, "OPT", 19, "Health", 200, 100, 16, 80, 220, 600, 800, 1000);
	building[21] = new Academic(this, "EV1", 21, "Env", 220, 150, 18, 90, 250, 700, 875, 1050);
	building[23] = new Academic(this, "EV2", 23, "Env", 220, 150, 18, 90, 250, 700, 875, 1050);
	building[24] = new Academic(this, "EV3", 24, "Env", 240, 150, 20, 100, 300, 750, 925, 1100);
	building[26] = new Academic(this, "PHYS", 26, "Sci1", 260, 150, 22, 110, 330, 800, 975, 1150);
	building[27] = new Academic(this, "B1", 27, "Sci1", 260, 150, 22, 110, 330, 800, 975, 1150);
	building[29] = new Academic(this, "B2", 29, "Sci1", 280, 150, 24, 120, 360, 850, 1025, 1200);
	building[31] = new Academic(this, "EIT", 31, "Sci2", 300, 200, 26, 130, 390, 900, 1100, 1275);
	building[32] = new Academic(this, "ESC", 32, "Sci2", 300, 200, 26, 130, 390, 900, 1100, 1275);
	building[34] = new Academic(this, "C2", 34, "Sci2", 320, 200, 28, 150, 450, 1000, 1200, 1400);
	building[37] = new Academic(this, "MC", 37, "Math", 350, 200, 35, 175, 500, 1100, 1300, 1500);
	building[39] = new Academic(this, "DC", 39, "Math", 400, 200, 50, 200, 600, 1400, 1700, 2000);
	building[5] = new Residence(this, "MKV", 5);
	building[15] = new Residence(this, "UWP", 15);
	building[25] = new Residence(this, "V1", 25);
	building[35] = new Residence(this, "REV", 35);
	building[12] = new Gym(this, "PAC", 12);
	building[28] = new Gym(this, "CIF", 28);
}

//see header file
int lineLength(string line)
{
	int i = 0;
	stringstream sstream(line);
	string in;
	while (sstream>>in)
	{
		i++;
	}
	return i;
}

//see header file
void Game::load(string file)
{
	ifstream myfile(file.c_str());

	string line;
	getline(myfile, line);
	stringstream ss(line);
	ss >> this->numPlayer;
	this->totalPlayer = this->numPlayer;
	player = new Player * [this->numPlayer];
	
	for (int i = 0; i < numPlayer; i++)
	{

		getline(myfile, line);
		stringstream ss(line);
		int l = lineLength(line);

		string name;
		char piece;
		int cup;
		int money;
		int position;
			
		ss >> name;
		ss >> piece;
		ss >> cup;
		if(cup > 0)
		{
			this->cupAvailable -= cup;
			if(this->cupAvailable <= 0)
			{
				cout << "Error: file broken (cup)" << endl;
				return;
			}
		}
		ss >> money;
		ss >> position;

		int decide;
		int turn;
		
		
		if(l == 5)
		{
			player[i] = new Player(this, name, piece, money, position, cup);
			
		}
		else if(l == 6)
		{
			ss >> decide;
			player[i] = new Player(this, name, piece, money, position, cup);
		}
		else if(l == 7)
		{
			ss >> decide;
			ss >> turn;
			player[i] = new Player(this, name, piece, money, position, cup, true, turn);
		}
		else
		{
			cout << "Error: file broken (player)" << endl;
			return;
		}

		this->notifyPlayer(piece, position, '+', "load");
	}

	for(int i = 0; i < 28; i++)
	{
		getline(myfile, line);
		stringstream ss(line);

		string name;
		string owner;
		int level;
		ss >> name;
		ss >> owner;
		ss >> level;

		//Player BANK = NULL;
		Player * RealOwner = NULL;
		if(owner != "BANK")
			RealOwner = getPlayer(owner);
		if(name == "AL")
		{
			building[1] = new Academic(this, "AL", 1, "Arts1", 40, 50, 2, 10, 30, 90, 160, 250, RealOwner, level);
			notifyBuilding(level, 1, "load");
			dynamic_cast<OwnableBuilding *>(building[1])->setOwner(RealOwner, "load");
		}
		else if(name == "ML")
		{
			building[3] = new Academic(this, "ML", 3, "Arts1", 60, 50, 4, 20, 60, 180, 320, 450, RealOwner, level);
			notifyBuilding(level, 3, "load");
			dynamic_cast<OwnableBuilding *>(building[3])->setOwner(RealOwner, "load");
		}
		else if(name == "ECH")
		{
			building[6] = new Academic(this, "ECH", 6, "Arts2", 100, 50, 6, 30, 90, 270, 400, 550, RealOwner, level);
			notifyBuilding(level, 6, "load");
			dynamic_cast<OwnableBuilding *>(building[6])->setOwner(RealOwner, "load");
		}
		else if(name == "PAS")
		{
			building[8] = new Academic(this, "PAS", 8, "Arts2", 100, 50, 6, 30, 90, 270, 400, 550, RealOwner, level);
			notifyBuilding(level, 8, "load");
			dynamic_cast<OwnableBuilding *>(building[8])->setOwner(RealOwner, "load");
		}
		else if(name == "HH")
		{
			building[9] = new Academic(this, "HH", 9, "Arts2", 120, 50, 8, 40, 100, 300, 450, 600, RealOwner, level);
			notifyBuilding(level, 9, "load");
			dynamic_cast<OwnableBuilding *>(building[9])->setOwner(RealOwner, "load");
		}
		else if(name == "RCH")
		{
			building[11] = new Academic(this, "RCH", 11, "Eng", 140, 100, 10, 50, 150, 450, 625, 750, RealOwner, level);
			notifyBuilding(level, 11, "load");
			dynamic_cast<OwnableBuilding *>(building[11])->setOwner(RealOwner, "load");
		}
		else if(name == "DWE")
		{
			building[13] = new Academic(this, "DWE", 13, "Eng", 140, 100, 10, 50, 150, 450, 625, 750, RealOwner, level);
			notifyBuilding(level, 13, "load");
			dynamic_cast<OwnableBuilding *>(building[13])->setOwner(RealOwner, "load");
		}
		else if(name == "CPH")
		{
			building[14] = new Academic(this, "CPH", 14, "Eng", 160, 100, 12, 60, 180, 500, 700, 900, RealOwner, level);
			notifyBuilding(level, 14, "load");
			dynamic_cast<OwnableBuilding *>(building[14])->setOwner(RealOwner, "load");
		}
		else if(name == "LHI")
		{
			building[16] = new Academic(this, "LHI", 16, "Health", 180, 100, 14, 70, 200, 550, 750, 950, RealOwner, level);
			notifyBuilding(level, 16, "load");
			dynamic_cast<OwnableBuilding *>(building[16])->setOwner(RealOwner, "load");
		}
		else if(name == "BMH")
		{
			building[18] = new Academic(this, "BMH", 18, "Health", 180, 100, 14, 70, 200, 550, 750, 950, RealOwner, level);
			notifyBuilding(level, 18, "load");
			dynamic_cast<OwnableBuilding *>(building[18])->setOwner(RealOwner, "load");
		}
		else if(name == "OPT")
		{
			building[19] = new Academic(this, "OPT", 19, "Health", 200, 100, 16, 80, 220, 600, 800, 1000, RealOwner, level);
			notifyBuilding(level, 19, "load");
			dynamic_cast<OwnableBuilding *>(building[19])->setOwner(RealOwner, "load");
		}
		else if(name == "EV1")
		{
			building[21] = new Academic(this, "EV1", 21, "Env", 220, 150, 18, 90, 250, 700, 875, 1050, RealOwner, level);
			notifyBuilding(level, 21, "load");
			dynamic_cast<OwnableBuilding *>(building[21])->setOwner(RealOwner, "load");
		}
		else if(name == "EV2")
		{
			building[23] = new Academic(this, "EV2", 23, "Env", 220, 150, 18, 90, 250, 700, 875, 1050, RealOwner, level);
			notifyBuilding(level, 23, "load");
			dynamic_cast<OwnableBuilding *>(building[23])->setOwner(RealOwner, "load");
		}	
		else if(name == "EV3")
		{
			building[24] = new Academic(this, "EV3", 24, "Env", 240, 150, 20, 100, 300, 750, 925, 1100, RealOwner, level);
			notifyBuilding(level, 24, "load");
			dynamic_cast<OwnableBuilding *>(building[24])->setOwner(RealOwner, "load");
		}
		else if(name == "PHYS")
		{
			building[26] = new Academic(this, "PHYS", 26, "Sci1", 260, 150, 22, 110, 330, 800, 975, 1150, RealOwner, level);
			notifyBuilding(level, 26, "load");
			dynamic_cast<OwnableBuilding *>(building[26])->setOwner(RealOwner, "load");
		}
		else if(name == "B1")
		{
			building[27] = new Academic(this, "B1", 27, "Sci1", 260, 150, 22, 110, 330, 800, 975, 1150, RealOwner, level);
			notifyBuilding(level, 27, "load");
			dynamic_cast<OwnableBuilding *>(building[27])->setOwner(RealOwner, "load");
		}
			
		else if(name == "B2")
		{
			building[29] = new Academic(this, "B2", 29, "Sci1", 280, 150, 24, 120, 360, 850, 1025, 1200, RealOwner, level);
			notifyBuilding(level, 29, "load");
			dynamic_cast<OwnableBuilding *>(building[29])->setOwner(RealOwner, "load");
		}
			
		else if(name == "EIT")
		{
			building[31] = new Academic(this, "EIT", 31, "Sci2", 300, 200, 26, 130, 390, 900, 1100, 1275, RealOwner, level);
			notifyBuilding(level, 31, "load");
			dynamic_cast<OwnableBuilding *>(building[31])->setOwner(RealOwner, "load");
		}
		else if(name == "ESC")
		{
			building[32] = new Academic(this, "ESC", 32, "Sci2", 300, 200, 26, 130, 390, 900, 1100, 1275, RealOwner, level);
			notifyBuilding(level, 32, "load");
			dynamic_cast<OwnableBuilding *>(building[32])->setOwner(RealOwner, "load");
		}
		else if(name == "C2")
		{
			building[34] = new Academic(this, "C2", 34, "Sci2", 320, 200, 28, 150, 450, 1000, 1200, 1400, RealOwner, level);
			notifyBuilding(level, 34, "load");
			dynamic_cast<OwnableBuilding *>(building[34])->setOwner(RealOwner, "load");
		}
		else if(name == "MC")
		{
			building[37] = new Academic(this, "MC", 37, "Math", 350, 200, 35, 175, 500, 1100, 1300, 1500, RealOwner, level);
			notifyBuilding(level, 37, "load");
			dynamic_cast<OwnableBuilding *>(building[37])->setOwner(RealOwner, "load");
		}
		else if(name == "DC")
		{
			building[39] = new Academic(this, "DC", 39, "Math", 400, 200, 50, 200, 600, 1400, 1700, 2000, RealOwner, level);
			notifyBuilding(level, 39, "load");
			dynamic_cast<OwnableBuilding *>(building[39])->setOwner(RealOwner, "load");
		}
		else if(name == "MKV")
		{
			building[5] = new Residence(this, "MKV", 5, level, RealOwner);
			dynamic_cast<OwnableBuilding *>(building[5])->setOwner(RealOwner, "load");
		}
		else if(name == "UWP")
		{
			building[15] = new Residence(this, "UWP", 15, level, RealOwner);
			dynamic_cast<OwnableBuilding *>(building[15])->setOwner(RealOwner, "load");
		}
		else if(name == "V1")
		{
			building[25] = new Residence(this, "V1", 25, level, RealOwner);
			dynamic_cast<OwnableBuilding *>(building[25])->setOwner(RealOwner, "load");
		}
		else if(name == "REV")
		{
			building[35] = new Residence(this, "REV", 35, level, RealOwner);
			dynamic_cast<OwnableBuilding *>(building[35])->setOwner(RealOwner, "load");
		}
			
		else if(name == "PAC")
		{
			building[12] = new Gym(this, "PAC", 12, level, RealOwner);
			dynamic_cast<OwnableBuilding *>(building[12])->setOwner(RealOwner, "load");
		}
			
		else if(name == "CIF")
		{
			building[28] = new Gym(this, "CIF", 28, level, RealOwner);
			dynamic_cast<OwnableBuilding *>(building[28])->setOwner(RealOwner, "load");
		}
			
		else
		{
			cout << "Error: file broken(building)" << endl;
			return;
		}
	}
}

//see header file
int Game::getNumPlayer()
{
	return this->numPlayer;
}

//see header file
Player * Game::getPlayer(int numPlayer)
{
	return this->player[numPlayer];
}

//see header file
Player * Game::getPlayer(string playerName)
{
	for(int i=0; i<this->numPlayer; i++)
	{
		if(player[i] == NULL)
		{
			continue;
		}
		if(player[i]->getName() == playerName)
		{
			return player[i];
		}
	}
	return NULL;
}

//see header file
Building * Game::getBuilding(int buildingNum)
{
	return this->building[buildingNum];
}

//see header file
Building * Game::getBuilding(std::string buildingName)
{
	for(int i=0; i<40; i++)
	{
		if(building[i]->getName() == buildingName)
		{
			return building[i];
		}
	}
	return NULL;
}

//see header file
char Game::getOwnerSymbol(int buildingNum)
{
	return dynamic_cast<OwnableBuilding *>(building[buildingNum])->getOwnerSymbol();
}

//see header file
int Game::cupLeft()
{
	return this->cupAvailable;
}

//see header file
void Game::changeCup(int amount)
{
	cupAvailable += amount;
}

//see header file
void Game::setNumPlayer(int numPlayer)
{
	this->numPlayer = numPlayer;
}

//see header file
void Game::trade()
{
	string sGiver = player[currentPlayer]->getName();
	string sReceiver;
	if(sGiver == sReceiver)
	{
		cout << "You can't trade to yourself!" << endl;
		return;
	}
	string give;
	string receive;
	cin >> sReceiver >> give >> receive;
	
	Player * giver = getPlayer(sGiver);
	Player * receiver = getPlayer(sReceiver);

	if(receiver == NULL)
	{
		cout << "No player: " << sReceiver << "! Check name again!" << endl;
		return;
	}

	int giveInt;
	int receiveInt;

	int state = 0;
	if(istringstream ( give ) >> giveInt)
	{
		if(istringstream ( receive ) >> receiveInt)
		{
			cout << "It does not make sense for a player to offer to give money in return for money." << endl;
			return;
		}
		else
		{
			if(giver->getMoney() < giveInt)
			{
				cout << "You do not have enough money!" << endl;
				return;
			}
			else
			{
				if(receiver->checkProperty(receive))
				{
					if(dynamic_cast<OwnableBuilding *>(getBuilding(receive))->getBuildingLevel() > 0)
					{
						cout << "You can't trade building with improvements!" << endl;
						return;
					}
					if(checkMonopolyNoImprovement(receive))
					{
						cout << "You can't trade building since there exist building(s) in this monopoly has improvements!" << endl;
						return;
					}
					state = 1;
				}
				else
				{
					cout << sReceiver << " do not have the property!" << endl;
					return;
				}
			}
		}
	}
	else
	{
		if(giver->checkProperty(give))
		{
			if(dynamic_cast<OwnableBuilding *>(getBuilding(give))->getBuildingLevel() > 0)
			{
				cout << "You can't trade building with improvements!" << endl;
				return;
			}
			if(checkMonopolyNoImprovement(give))
			{
				cout << "You can't trade building since there exist building(s) in this monopoly has improvements!" << endl;
				return;
			}
			if(istringstream ( receive ) >> receiveInt)
			{
				if(receiver->getMoney() >= receiveInt)
				{
					state = 2;
				}
				else
				{
					cout << sReceiver << " do not have enough money!" << endl;
					return;
				}
			}
			else
			{
				if(receiver->checkProperty(receive))
				{
					if(dynamic_cast<OwnableBuilding *>(getBuilding(receive))->getBuildingLevel() > 0)
					{
						cout << "You can't trade building with improvements!" << endl;
						return;
					}
					if(checkMonopolyNoImprovement(receive))
					{
						cout << "You can't trade building since there exist building(s) in this monopoly has improvements!" << endl;
						return;
					}
					state = 3;
				}
				else
				{
					cout << sReceiver << " do not have the property!" << endl;
					return;
				}
			}
		}
		else
		{
			cout << "You do not have the property!" << endl;
			return;
		}
	}

	cout << giver->getName() << " offers a trade to " << receiver->getName() << " offering " << give << " and requesting " << receive << "!" << endl;
	cout << "Do you agree with the trade (y/n)?" << endl;
	string command;
	while(true)
	{
		cin >> command;
		if(command == "y")
		{
			if(state == 1)
			{
				giver->changeMoney(giveInt * -1, receiver);
				dynamic_cast<OwnableBuilding *>(this->getBuilding(receive))->setOwner(giver);
			}
			else if(state == 2)
			{
				receiver->changeMoney(receiveInt * -1, giver);
				dynamic_cast<OwnableBuilding *>(this->getBuilding(give))->setOwner(receiver);
			}
			else if(state == 3)
			{
				dynamic_cast<OwnableBuilding *>(this->getBuilding(receive))->setOwner(giver);
				dynamic_cast<OwnableBuilding *>(this->getBuilding(give))->setOwner(receiver);
			}
			else
			{
				cout << "Error! Not possiable!" << endl;
				return;
			}
			cout << "Trade conplete!" << endl;
			return;
		}
		else if(command == "n")
		{
			cout << "Trade Reject!" << endl;
			return;
		}
		else
		{
			cout << "Wrong command, please try again!" << endl;
		}

	}
}

//see header file
void Game::auction(OwnableBuilding * building, int price)
{
	int currentNumBidder = 0;

	int bidderList[totalPlayer];

	for(int i=0; i< totalPlayer; i++)
	{
		if(player[i] != NULL)
		{
			bidderList[currentNumBidder] = i;
			currentNumBidder++;
		}
		else
			bidderList[currentNumBidder] = -1;
	}

	int currentBid = price;

	cout << "Auction begin!" << endl;
	cout << "Proporty: " << building->getName() << " The base bid is: " << currentBid << endl;

	int currentHighestBidder = -1;
	int i = 0;
	while(currentNumBidder != 0)//when there still are bidder exist
	{
		if(currentNumBidder == 1 && currentHighestBidder != -1) //only 1 bidder left and there is people bid for this building already
		{
			cout << "Player: " <<  player[currentHighestBidder]->getName() << " win the bid!" <<endl;
			player[currentHighestBidder]->changeMoney(currentBid * -1);
			building->setOwner(player[currentHighestBidder]);
			return;
		}

		while(bidderList[i] == -1)
		{
			i++;
			if(i == totalPlayer)
				i = 0;
		}

		if(player[i]->getMoney() < currentBid)			
		{
			bidderList[i] = -1; //quit
			currentNumBidder--;
			cout << player[i]->getName() << " get kicked out the auction due to you don't have enough money!" << endl;
			continue;
		}

		cout << "Player: " << player[currentNumBidder]->getName() << endl;
		cout << "Current bid is: " << currentBid << ", raise bid / quit (r/q)?" << endl;

		string command;
		while(true)
		{
			cin >> command;
			if(command == "r")
			{
				currentBid *= raiseBidRatio;
				currentHighestBidder = i;
				break;
			}
			else if(command == "q")
			{
				currentNumBidder--;
				cout << "Player: " << player[i]->getName() << " quit this bid!" <<endl;
				break;
			}
			else
			{
				cout << "Wrong command, please try again!" << endl;
				continue;
			}
		}
	}
	i++;
}

//see header file
void Game::buildingEffect(int buildingNum)
{
	this->building[buildingNum]->effect(player[currentPlayer]);
}

//see header file
void Game::notifyPlayer(char piece, int location, char active, string mode)
{
	controller->notifyPlayer(piece, location, active, mode);
}

//see header file
void Game::notifyBuilding(int level, int building, string mode)
{
	controller->notifyBuilding(level, building, mode);
}


//see header file
int Game::rollInt()
{
	int a = rand() % 6 + 1;
	return a;
}

//see header file
bool Game::checkMonopolyNoImprovement(string give)
{
	string monopolyBlock = dynamic_cast<OwnableBuilding *>(getBuilding(give))->getBuildingMono();
	if(monopolyBlock == "Arts1")
		return (dynamic_cast<OwnableBuilding *>(this->building[1])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[3])->getBuildingLevel() != 0);
	else if(monopolyBlock == "Arts2")
		return (dynamic_cast<OwnableBuilding *>(this->building[6])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[8])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[9])->getBuildingLevel() != 0);
	else if(monopolyBlock == "Eng")
		return (dynamic_cast<OwnableBuilding *>(this->building[11])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[13])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[14])->getBuildingLevel() != 0);
	else if(monopolyBlock == "Health")
		return (dynamic_cast<OwnableBuilding *>(this->building[16])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[18])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[19])->getBuildingLevel() != 0);
	else if(monopolyBlock == "Env")
		return (dynamic_cast<OwnableBuilding *>(this->building[21])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[23])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[24])->getBuildingLevel() != 0);
	else if(monopolyBlock == "Sci1")
		return (dynamic_cast<OwnableBuilding *>(this->building[26])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[27])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[29])->getBuildingLevel() != 0);
	else if(monopolyBlock == "Sci2")
		return (dynamic_cast<OwnableBuilding *>(this->building[31])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[33])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[34])->getBuildingLevel() != 0);
	else if(monopolyBlock == "Math")
		return (dynamic_cast<OwnableBuilding *>(this->building[37])->getBuildingLevel() != 0 || dynamic_cast<OwnableBuilding *>(this->building[39])->getBuildingLevel() != 0);
	else
		return false;
}


//see header file
void Game::rolledDice()
{
	this->controller->rolledDice();
}

//see header file
void Game::roll(char mode)
{
	if(player[currentPlayer]->getTimsState() == 1)
	{
		player[currentPlayer]->timsLineTurn(mode);
		return;
	}

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

	if (a != b)
	{
		this->controller->rolledDice();

		int sum = a + b;
		cout << "Dice1: " << a << "    Dice2: " << b << endl;
		player[currentPlayer]->move(sum);
		player[currentPlayer]->rollTimeClear();
	}
	else
	{
		player[currentPlayer]->rollTimeAdd();

		if(player[currentPlayer]->getRollTime() == 3)//tim
		{
			this->controller->rolledDice();

			player[currentPlayer]->goToTimsLine();
			player[currentPlayer]->rollTimeClear();

			cout << "You rolled doubles 3 times in a roll! GO TO DC TIMS LINE!" << endl;
			return;
		}
		else
		{
			cout << "You rolled doubles, you need to roll again." << endl;
		}
	}
}

//see header file
void Game::next()
{
	while(true)
	{	
		this->currentPlayer++;

		if(this->currentPlayer >= totalPlayer)
		{
			this->currentPlayer = 0;
		}
		if(this->player[currentPlayer] == NULL)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	cout << player[currentPlayer]->getName() << "'s turn!" << endl;
}

//see header file
void Game::improve()
{
	string buildingName;
	string command;

	while(true)
	{
		cin >> buildingName;
		cin >> command;
		if(command == "buy")
		{
			player[currentPlayer]->changeImprove(buildingName, '+');
			break;
		}
		else if(command == "sell")
		{
			player[currentPlayer]->changeImprove(buildingName, '-');
			break;
		}
		else
		{
			cout << "Wrong command, please try again!" << endl;
			break;
		}
	}
}

//see header file
void Game::mortgage()
{
	player[currentPlayer]->changeMortgage('+');
}

//see header file
void Game::unmortgage()
{
	player[currentPlayer]->changeMortgage('-');
}

//see header file
void Game::assets()
{
	player[currentPlayer]->assets();
}

//see header file
void Game::save()
{
	// open file first
	string saveFileName;
	cin >> saveFileName;
	ofstream myfile;
	myfile.open(saveFileName.c_str());
	// write the players

	myfile << this->numPlayer << endl;
	int playerCounter = numPlayer;
	int loopCounter = 0;
	while(playerCounter != 0)
	{
		if (player[loopCounter] != NULL)
		{
			myfile << player[loopCounter]->getName();
			myfile << " ";
			myfile << player[loopCounter]->getSymbol();
			myfile << " ";
			myfile << player[loopCounter]->getCup();
			myfile << " ";
			myfile << player[loopCounter]->getMoney();
			myfile << " ";
			myfile << player[loopCounter]->getLocation();
			
			// if in TimsLine
			if (player[loopCounter]->getLocation() == 10)
			{
				if (player[loopCounter]->getTimsState() == 0)
				{
					myfile << " 0";
				}
				else
				{
					myfile << " 1 ";
					myfile << player[loopCounter]->getTimsTurn();
				}
			}
			myfile << endl;
			playerCounter--;
		}
		loopCounter++;
	}
	// write the buildings
	for (int i=0; i < 40; ++i)
	{
		if (dynamic_cast<OwnableBuilding *>(building[i]) != NULL) // resi + gym
		{
			myfile << building[i]->getName() << " ";
			myfile << dynamic_cast<OwnableBuilding *>(building[i])->getOwnerName() << " ";
			if (dynamic_cast<OwnableBuilding *>(building[i]) != NULL)// academic
			{
				myfile << dynamic_cast<OwnableBuilding *>(building[i])->getBuildingLevel() << endl;
			}
			else
			{
				myfile << 0 << endl;
			}
		}
		else
		{
			continue;
		}
	}
	myfile.close();
}

//see header file
void Game::bankrupt()
{
	numPlayer--;
	//checkWin();//dnqbybyj
}

//see header file
void Game::playerOut()
{
	//delete player[currentPlayer];
	cout << "Player: " << player[currentPlayer]->getName() << " get kick out from this game!" << endl;
	player[currentPlayer] = NULL;
	this->controller->rolledClear();

	next();
}

//see header file
void Game::checkWin()
{
	this->controller->checkWin();
}
