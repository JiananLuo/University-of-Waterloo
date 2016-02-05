#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <string>

#include "improvable.h"
#include "unimprovable.h"

class Cell;

class TextDisplay
{
	/* 
	 * room shows the play board of the game
	 */
	Cell ** room;
	public:
		//constructor of TextDisplay
		TextDisplay();
		//destructor fo TextDisplay
		virtual ~TextDisplay();

		/*
		 * initialize the board, which contains the buildings and player
		 */
		void init();

		/*
		 * The TextDisplay calls notifyPlayer to update the state
		 * of player on a building
		 */
		virtual void notifyPlayer(char piece, int buildingNum, char active, std::string mode);

		/*
		 * The TextDisplay calls notifyBuilding to update the state
		 * of a building
		 */
		virtual void notifyBuilding(int level, int buildingNum, std::string mode);

		/*
		 * display the game by text
		 */
		virtual void print();
};

#endif
