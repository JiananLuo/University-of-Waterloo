#ifndef __BUILDING_H__
#define __BUILDING_H__

#include <string>

class Game;
class Player;
class Building
{
	protected:
		Game *game; //game pointer
		std::string name; //name for this building
		int buildingNum; //building number
	public:
		//get the name for this building
		std::string getName();
		//get the pointer for this building
		Building * getBuilding();
		//virtual char getOwnerSymbol() = 0;
		virtual void effect(Player * player) = 0;
};

#endif
