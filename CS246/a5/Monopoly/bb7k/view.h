#ifndef __VIEW_H__
#define __VIEW_H__

#include <string>

class View
{
	public:
		//constructor of View
		View();

		//destructor of View
		virtual ~View() = 0;

		//initialization of View
		virtual void init() = 0;

		/*
		 * The Controller calls notifyPlayer to update the state
		 * of player on a building
		 */
		virtual void notifyPlayer(char player, int buildingNum, char active) = 0;

		/*
		 * The Controller calls notifyBuilding to update the state
		 * of a building
		 */
		virtual void notifyBuilding(int level, int buildingNum) = 0;

		//print the game on the screen
		virtual void print() = 0;
};

#endif
