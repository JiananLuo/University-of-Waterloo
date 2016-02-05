#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <iostream>
#include <string>

#include "textDisplay.h"
#include "game.h"

class Game;
class Controller
{
	TextDisplay * td;//the pointer to textdisplay
	Game * game;//the pointer to game

	bool rolled;//check if they currently player rolled or not

	public:
		//default constructor of Controller
		Controller();

		//initialization of controller, initial the buildings in the gam
		void init();

		//load from file
		void load(std::string file);

		//notify the player on the display
		void notifyPlayer(char player, int buildingNum, char active, std::string mode);

		//notify the building on the display
		void notifyBuilding(int level, int buildingNum, std::string mode);

		//roll the Dice, set the rolled flag to true
		void rolledDice();
		
		//set the rolled flag back to false
		void rolledClear();

		//start to play the game
		void play(char mode = 'n');

		//chcek if there is only 1 player left
		void checkWin();
 };

 #endif
