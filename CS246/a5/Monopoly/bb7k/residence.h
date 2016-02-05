#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__

#include "ownableBuilding.h"

class Residence : public OwnableBuilding
{
	int residenceRentAmount[4];//the residence rent amout

	public:
		//constructor for Residence
		Residence(Game * game, std::string name, int buildingNum, int improvementLevel = 0, Player * owner = NULL, int purchaseCost = 200);

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
