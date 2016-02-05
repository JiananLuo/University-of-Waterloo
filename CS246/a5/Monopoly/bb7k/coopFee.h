#ifndef __COOPFEE_H__
#define __COOPFEE_H__

#include "unownableBuilding.h"
#include "player.h"

const int coopFee = 150;

class Player;
class CoopFee : public UnownableBuilding
{
	public:
		//constructor of CoopFee
		CoopFee(Game * game, int buildingNum);

		//the effect of CoopFee
		virtual void effect(Player * player);
};

#endif
