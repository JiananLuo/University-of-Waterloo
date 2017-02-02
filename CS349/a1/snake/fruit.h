#ifndef __FRUIT_H__
#define __FRUIT_H__

#include "displayable.h"

class Fruit : public Displayable {
  private:
    int x;
    int y;

	public:
    Fruit(int x, int y);
    int getX();
    int getY();
  	virtual void paint(XInfo &xInfo);
		void regrow(int newX, int newY);
    bool isFruit(int x, int y);
};

#endif
