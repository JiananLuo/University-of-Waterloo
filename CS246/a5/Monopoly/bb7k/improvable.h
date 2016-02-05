#ifndef __IMPROVABLE_H__
#define __IMPROVABLE_H__

#include "cell.h"

class Improvable : public Cell
{
	public:
		//construct a improvable Building on the display with player on it
		Improvable(std::string buildingName, std::string player);
};

#endif
