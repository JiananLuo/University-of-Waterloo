#ifndef __TUITION_H__
#define __TUITION_H__

#include "unownableBuilding.h"
#include "player.h"

const int tuitionAmout = 300;
const float tuitionPresent = 0.1;

class Game;
class Player;
class Tuition : public UnownableBuilding
{
	public:
		//constructor of Tuition
		Tuition(Game * game, int buildingNum);

		//effect of Tuition
		virtual void effect(Player * player);
};

#endif
