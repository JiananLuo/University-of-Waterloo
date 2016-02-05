#ifndef __COLLECTOSAP_H__
#define __COLLECTOSAP_H__

#include "unownableBuilding.h"
#include "player.h"

const int moneyCollect = 200;//OSAP

class Game;
class Player;

class CollectOsap : public UnownableBuilding
{
	public:
		//constructor of CollectOsap
		CollectOsap(Game * game, int buildingNum);

		//effect of CollectOsap
		virtual void effect(Player * player);
};

#endif
