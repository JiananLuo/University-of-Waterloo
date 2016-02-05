#ifndef __GYM_H__
#define __GYM_H__

#include "ownableBuilding.h"

class Gym : public OwnableBuilding
{
	int gymFeeMultiple[2];//the gym fee multiplier

	public:
		//constructor for Gym
		Gym(Game * game, std::string name, int buildingNum, int improvementLevel = 0, Player * owner = NULL, int purchaseCost = 150);

		//buy improvements for this building
		virtual void buyImprovement();

		//sell improvements for this building
		virtual void sellImprovement();
		
		//get this building's total value, purachse amount and improvemtns
		virtual int getBuildingValue();

		//get the pay amount when people land on this building
		virtual int payAmount();

		//this building's effect when its owner get bankrupt
		virtual void ownerBankrupt();
};

#endif
