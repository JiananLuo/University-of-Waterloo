#include "fruit.h"
#include "game.h"
Fruit::Fruit(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Fruit::paint(XInfo &xInfo)
{
  XSetForeground(xInfo.display, xInfo.gc[0], fruitColor.pixel);
  XFillArc(xInfo.display, xInfo.bufferWindow, xInfo.gc[0], x, y, BLOCK_SIZE, BLOCK_SIZE, 0, 360*64);
}

int Fruit::getX()
{
  return x;
}

int Fruit::getY()
{
  return y;
}

void Fruit::regrow(int newX, int newY)
{
  x = newX;
  y = newY;
}

bool Fruit::isFruit(int x, int y)
{
  if(this->x == x && this->y == y)
  {
    return true;
  }
  return false;
}
