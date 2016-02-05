#ifndef __UNOWNABLEBUILDING_H__
#define __UNOWNABLEBUILDING_H__

#include "building.h"

class Player;

/*
 * An abstract class presents unownablebuildings
 */
class UnownableBuilding : public Building
{
	public:
		 // the effect of building
		virtual void effect(Player * player) = 0;
};

#endif
