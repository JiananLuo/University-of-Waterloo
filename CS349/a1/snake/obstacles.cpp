#include "obstacles.h"
#include "game.h"

Obstacles::Obstacles() {}

Obstacles::~Obstacles()
{
  for(int i=0; i<points.size(); i++)
  {
    delete points[i];
  }
}

void Obstacles::paint(XInfo &xInfo)
{
  XSetForeground(xInfo.display, xInfo.gc[0], obstacleColor.pixel);
  for(int i=0; i<points.size(); i++)
  {
    XFillRectangle(xInfo.display, xInfo.bufferWindow, xInfo.gc[0], points[i]->getX(), points[i]->getY(), BLOCK_SIZE, BLOCK_SIZE);
  }
}

void Obstacles::addObstacle(int x, int y)
{
  Obstacle *obstacle = new Obstacle(x, y);
  points.push_back(obstacle);
}

bool Obstacles::isObstacle(int cordX, int cordY)
{
  for(int i=0; i<points.size(); i++)
  {
    if(cordX == points[i]->getX() && cordY == points[i]->getY())
    {
      return true;
    }
  }
  return false;
}
