#ifndef __DCTIMESLINE_H__
#define __DCTIMESLINE_H__

#include "unownableBuilding.h"

class Game;
class Player;
class DcTimsLine : public UnownableBuilding
{
	public:
		//constructor fo DcTimsLine
		DcTimsLine(Game * game, int buiildingNum);

		//the effect of DcTimsLine nothing!
		virtual void effect(Player * player);
};

#endif
