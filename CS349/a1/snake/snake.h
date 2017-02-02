#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "displayable.h"
#include "snakeBox.h"
#include "fruit.h"

#include <vector>

const char W = 'w';
const char A = 'a';
const char S = 's';
const char D = 'd';

class Snake : public Displayable {
  private:
    int x;
    int y;
    int bodyLength;
    std::vector<SnakeBox*> body;
    char direction;

	public:
    bool movedFlag;
    Snake(int x, int y);
    ~Snake();

		int getX();
		int getY();
		char getDirection();
    int getLength();

		virtual void paint(XInfo &xInfo);
		void move(XInfo &xInfo, Fruit &fruit);
    void didEatFruit(Fruit &fruit);
    void didHitObstacle(XInfo &xInfo);
    void grow();
    void goW();
    void goS();
    void goA();
    void goD();
    bool isSnake(int cordX, int cordY);
};

#endif
