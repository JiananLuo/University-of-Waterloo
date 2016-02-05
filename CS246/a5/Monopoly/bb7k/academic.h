#ifndef __ACADEMIC_H__
#define __ACADEMIC_H__

#include "ownableBuilding.h"

const int maxLevel = 5;
const int minLevel = 0;
const float sellImprovementRatio = 0.5;
const int buyImprovementRatio = -1;
const int monopolyNoImprovementRatio = 2;

class Academic : public OwnableBuilding
{
	protected:
		int improvementCost; //the cost for each improvement
		int tuitionAtImprovements[6]; //the fee need to pay under the improvement level

	public:
		//constructor for Academic building
		Academic(Game * game, std::string name, int buildingNum, std::string monopolyBlock, int purchaseCost, int improvementCost, int tuition0, int tuition1, int tuition2, int tuition3, int tuition4, int tuition5, Player * owner = NULL, int improvementLevel = 0);
		
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
