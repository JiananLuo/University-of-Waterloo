#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

class Obstacle
{
  private:
    int x;
    int y;

	public:
    Obstacle(int x, int y): x(x), y(y) {}
    int getX();
    int getY();
    void updateX(int x);
    void updateY(int y);
		void regrow(int newX, int newY);
};

#endif
