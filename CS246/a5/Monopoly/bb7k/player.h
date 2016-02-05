#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <string>
#include <map>

#include "game.h"
#include "ownableBuilding.h"

class OwnableBuilding;
class Game;
class Player
{

	Game * game;//pointer to the game
	std::string name;//the player's name
	char symbol;//the player's symbol(piece)
	
	int money;//the money hold by the player
	int location;//the location the player stand on
	int cupOwn;//the cup the player have
	bool atTimsLine;//each the player is at tims line or not
	int atTimsTurn;//the turn the player stay the dc tims line
    int rollTime;//how many times the player have already roll in this turn
	std::map <std::string, OwnableBuilding *> properties;//properties the player owns

	public:
        //constructor of Player
		Player(Game * game, std::string name, char symbol, int money = 1500, int location = 0, int cupOwn = 0, bool atTimsline = false, int atTimsTurn = 0, std::map <std::string, OwnableBuilding *> **properties = NULL);

        //get the name of player
		std::string getName();

        //get the piece which represents the Player
		char getSymbol();

        //get the number of cups the Player owns
		int getCup();

        //get the money owned by the Player
		int getMoney();

        //get the Location of the Player
		int getLocation();

        //get the number of rolls rolled by the player
        int getRollTime();

        //get the state presents if the Player is in Timsline
		int getTimsState();

        //get the number of turns taken in the TimsLine
		int getTimsTurn();

        //player at tims line turn + 1
        void rollTimeAdd();

        //player at tims line turn reset to 0
        void rollTimeClear();

        //player go to dc tims line effect
		void goToTimsLine();

        //player to go collect osap effect
        void goToCollectOsap();

        //player's turn at dc tims line
		void timsLineTurn(char mode);

		//change player's proporties, action: '+' or '-'
		void changeBuilding(std::string buildingName, char action);

        //change player's proporties' improvements, action: '+' or '-'
		void changeImprove(std::string buildingName, char action);

        //change player's proporties' mortgage state, action: '+' or '-'
		void changeMortgage(char action);

        //change player's cup
        void changeCup(int amount);

        //change player's money
		void changeMoney(int amount, Player * to = NULL);

        //check if player have the property given by the parameter
		bool checkProperty(std::string buildingName);

        //prints the player's assets include money and building
		void assets();

        //get the player's total value, include money and building value
		int getTotalValue();

        //if a player declear bankrupt to either a player or bank(NULL)
		void bankrupt(Player * player);

        //this player move steps for the given steps
		void move(int steps);
};

#endif
