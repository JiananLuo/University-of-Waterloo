#ifndef __UNIMPROVABLE_H__
#define __UNIMPROVABLE_H__

#include "cell.h"

class Unimprovable : public Cell
{
	public:
		//show a player on a unimprovable building
		Unimprovable(std::string name1, std::string name2, std::string player);
};

#endif
