#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <string>
#include <fstream>

#include "controller.h"
#include "player.h"
#include "building.h"

class Controller;
class Player;
class Building;
class OwnableBuilding;
class Game
{
	int totalPlayer;//total number of player in this game, include bankruped player
	int numPlayer;//total number of player in this game, exclude bankruped player
	int currentPlayer;//the current player for this game
	int cupAvailable;//the cup still avaliable for this game 4 limit

	Controller * controller;//the pointer to the controller

	std::string pieceAvailable[8];
	Player ** player;//pointer to player list in this game
	Building ** building;//pointer to building list in this game

	public:
		//constructor of game
		Game(Controller *notify);

		//destructor of game
		~Game();
		
		//initialization of the game
		void init();

		//load from a file
		void load(std::string file);

		//get the number of players in the game
		int getNumPlayer();

		//get the pointer of the player
		Player * getPlayer(int player);

		//get the the name of the player
		Player * getPlayer(std::string playerName);

		//return the pointer of the specific building
		Building * getBuilding(int buildingNum);

		//return the pointer of the building with the name buildingName
		Building * getBuilding(std::string buildingName);

		//return the piece of the owner who owns the building
		char getOwnerSymbol(int buildingNum);

		//return the number of aviable cups left
		int cupLeft();

		//change the amount for cup in this game
		void changeCup(int amount);

		//set the number of players
		void setNumPlayer(int numPlayer);
		
		//roll the Dice
		void rolledDice();

		//the effect of specific building
		void buildingEffect(int buildingNum);

		//notify the player in the View, load mode do not print board at the end of the function, otherwise print
		void notifyPlayer(char piece, int location, char active, std::string mode = "load");//call controller then call view

		//notify the building in the View, load mode do not print board at the end of the function, otherwise print
		void notifyBuilding(int level, int building, std::string mode = "load");//notify controller then notify view

		//roll the dice and return the result for gym
		int rollInt();

		//auction the building with the specific price
		void auction(OwnableBuilding * building, int price);

		//check a building's monopoly, return true if monopoly has improvement, returns false other wise
		bool checkMonopolyNoImprovement(std::string give);

		//check if theres only 1 player left in this game
		void checkWin();

		//the current player bankrupt effects
		void bankrupt();

		//after the current player bankrupt, delete this player
		void playerOut();

	//general commands:
		//default roll dice, otherwise for testing mode
		void roll(char mode);

		//proceed to next player
		void next();

		//launch the trade between players
		void trade();

		//improve the building
		void improve();

		//mortgage the building
		void mortgage();

		//unmortgage the building
		void unmortgage();

		//show the assets owned by the player
		void assets();

		//save the game
		void save();
};

#endif
