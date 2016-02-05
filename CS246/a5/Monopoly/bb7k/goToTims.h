#ifndef __GOTOTIMS_H__
#define __GOTOTIMS_H__

#include "unownableBuilding.h"
#include "player.h"

class Game;
class Player;
class GoToTims : public UnownableBuilding
{
	public:
		//constructor of GoToTims
		GoToTims(Game * game, int buildingNum);

		//effect of GoToTims
		virtual void effect(Player * player);
};

#endif
