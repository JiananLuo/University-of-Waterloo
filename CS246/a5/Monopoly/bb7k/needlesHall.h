#ifndef __NEEDLESHALL_H__
#define __NEEDLESHALL_H__

#include "player.h"
#include "unownableBuilding.h"

const int probabilityOSAP_N200 = 1;
const int probabilityOSAP_N100 = 2;
const int probabilityOSAP_N50 = 3;
const int probabilityOSAP_P25 = 6;
const int probabilityOSAP_P50 = 3;
const int probabilityOSAP_P100 = 2;
const int probabilityOSAP_P200 = 18;

const int AmountOSAP_N200 = -200;
const int AmountOSAP_N100 = -100;
const int AmountOSAP_N50 = - 50;
const int AmountOSAP_P25 = 25;
const int AmountOSAP_P50 = 50;
const int AmountOSAP_P100 = 100;
const int AmountOSAP_P200 = 200;

class Game;
class Player;
class NeedlesHall : public UnownableBuilding
{
	public:
		//constructor of NeedlesHall
		NeedlesHall(Game * game, int buildingNum);

		//the effect of NeedlesHall
		virtual void effect(Player * player);
};

#endif
