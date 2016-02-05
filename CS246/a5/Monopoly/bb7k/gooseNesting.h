#ifndef __GOOSENESTING_H__
#define __GOOSENESTING_H__

#include "unownableBuilding.h"

class Game;
class Player;
class GooseNesting : public UnownableBuilding
{
	public:
		//constructor of GooseNesting
		GooseNesting(Game * game, int buildingNum);

		//effect of the GooseNesting
		virtual void effect(Player * player);
};

#endif
