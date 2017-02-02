#ifndef __OBSTACLES_H__
#define __OBSTACLES_H__

#include "displayable.h"
#include "obstacle.h"

#include <vector>

class Obstacles : public Displayable {
  private:
    std::vector<Obstacle*> points;

	public:
    Obstacles();
    ~Obstacles();
  	virtual void paint(XInfo &xInfo);
    void addObstacle(int x, int y);
    bool isObstacle(int cordX, int cordY);
};

#endif
