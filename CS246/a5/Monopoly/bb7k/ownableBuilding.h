#ifndef __OWNABLEBUILDING_H__
#define __OWNABLEBUILDING_H__

#include <string>

#include "building.h"
#include "player.h"

const float mortgageRatio = 0.5;
const float unmortgageRatio = 0.55;
const float immdeiatelyFeeRatio = 0.05;
const float raiseBidRatio = 1.1;

class Player;
class OwnableBuilding : public Building
{
	protected:
		Player * owner;//pointer to owner for this building
		std::string monopolyBlock;//the monopoly block for this building
		int purchaseCost;//the purchase cost for this building
		
		int improvementLevel;// this improvement level for this building

	public:
		//set the owner of this build to player, mode play = might pay immadiatly fee from who received a mortgaged building
		void setOwner(Player * player, std::string mode = "play");

		//mortgage this building
		void mortgage();

		//unmortgage this building
		void unmortgage();

		//check if this building's monopoly has the same owner
		bool checkMonopoly();

		//go to auction for this building
		void auction();

		//get building's improvement level
		int getBuildingLevel();

		//get the monopoly for this building
		std::string getBuildingMono();

		//get the owner's name for this building
		std::string getOwnerName();

		//get the owner's symbol for this building
		char getOwnerSymbol();

		//building effect for ownableBuilding
		void effect(Player * player);

		//buy improvements for this building
		virtual void buyImprovement() = 0;

		//sell improvements for this building
		virtual void sellImprovement() = 0;
		
		//get this building's total value, purachse amount and improvemtns
		virtual int getBuildingValue() = 0;

		//get the pay amount when people land on this building
		virtual int payAmount() = 0;

		//this building's effect when its owner get bankrupt
		virtual void ownerBankrupt() = 0;
};

#endif
