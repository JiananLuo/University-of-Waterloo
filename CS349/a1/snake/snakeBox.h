#ifndef __SNAKEBOX_H__
#define __SNAKEBOX_H__

class SnakeBox
{
  private:
    int x;
    int y;

  public:
    SnakeBox(int x, int y): x(x), y(y) {}
    int getX();
    int getY();
    void updateX(int x);
    void updateY(int y);
};

#endif
