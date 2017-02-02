#include "obstacle.h"

int Obstacle::getX()
{
  return x;
}

int Obstacle::getY()
{
  return y;
}

void Obstacle::updateX(int x)
{
  x=x;
}

void Obstacle::updateY(int y)
{
  y=y;
}

void Obstacle::regrow(int newX, int newY)
{
  x = newX;
  y = newY;
}
