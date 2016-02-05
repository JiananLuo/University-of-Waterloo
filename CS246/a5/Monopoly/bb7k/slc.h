#ifndef __SLC_H__
#define __SLC_H__

#include "player.h"
#include "unownableBuilding.h"

const int probabilityBack3 = 3; 
const int probabilityBack2 = 7;
const int probabilityBack1 = 11;
const int probabilityForward3 = 15;
const int probabilityForward2 = 19;
const int probabilityForward1 = 22;
const int probabilityGoToTims = 23;
const int probabilityCollectOSAP = 24;

class Game;
class Player;
class Slc : public UnownableBuilding
{
	public:
		//constructor of Slc
		Slc(Game * game, int buildingNum);

		//the effect of Slc
		virtual void effect(Player * player);
};

#endif
