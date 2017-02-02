#ifndef __GAME_H__
#define __GAME_H__

#include <list>

#include "snake.h"
#include "fruit.h"
#include "obstacles.h"
#include "text.h"

extern list<Displayable *> dList;
extern Snake *SNAKE;
extern Fruit *FRUIT;
extern Obstacles *OBSTACLES;
extern Text *MSG_SCORE;
extern unsigned long timePassed;
extern int GAME_LEVEL;
extern bool NO_BOUNDARY_MODE;
extern int BLOCK_SIZE, WIDTH_BOUND, HEIGHT_BOUND;

unsigned long now();
void gameEnd(XInfo &xInfo, string reasonMsg);

#endif
