#include "game.h"
#include "snake.h"

using namespace std;

Snake::Snake(int x, int y)
{
  this->x = x;
  this->y = y;
  bodyLength = 3;
  direction = D;
  movedFlag = false;
  for(int i=0; i<bodyLength; i++)
  {
    SnakeBox *sb = new SnakeBox(x-(i*BLOCK_SIZE), y);
    body.push_back(sb);
  }
}

Snake::~Snake()
{
  for(int i=0; i<bodyLength; i++)
  {
    delete body[i];
  }
}

void Snake::paint(XInfo &xInfo)
{
  XSetForeground(xInfo.display, xInfo.gc[0], snakeColor.pixel);
	for(int i=0; i<bodyLength; i++)
	{
	  XFillArc(xInfo.display, xInfo.bufferWindow, xInfo.gc[0], body[i]->getX(), body[i]->getY(), BLOCK_SIZE, BLOCK_SIZE, 0, 360*64);
	}
}

void Snake::move(XInfo &xInfo, Fruit &fruit)
{
  if(direction == S)
  {
    y = y + BLOCK_SIZE;
  }
  else if(direction == W)
  {
    y = y - BLOCK_SIZE;
  }
  else if(direction == A)
  {
	  x = x - BLOCK_SIZE;
  }
  else if(direction == D)
  {
	  x = x + BLOCK_SIZE;
  }
  if(NO_BOUNDARY_MODE)
  {
    if(this->x < 0)
    {
      this->x = WIDTH_BOUND;
    }
    else if(this->x > WIDTH_BOUND)
    {
      this->x = 0;
    }
    else if(this->y < 0)
    {
      this->y = HEIGHT_BOUND;
    }
    else if(this->y > HEIGHT_BOUND)
    {
      this->y = 0;
    }
  }
  SnakeBox *sb = new SnakeBox(x, y);
  body.insert(body.begin(), sb);
  body.pop_back();

  didEatFruit(fruit);
  didHitObstacle(xInfo);

  movedFlag = true;
}

int Snake::getX()
{
	return x;
}

int Snake::getY()
{
	return y;
}

char Snake::getDirection()
{
	return direction;
}

int Snake::getLength()
{
  return bodyLength;
}

void getEmptySpot(int &x, int &y)
{
  int randX = WIDTH / BLOCK_SIZE;
  int randY = HEIGHT / BLOCK_SIZE;
  x = rand() % randX;
  y = rand() % randY;
  x *= BLOCK_SIZE;
  y *= BLOCK_SIZE;
  while(SNAKE->isSnake(x, y) || FRUIT->isFruit(x, y) || OBSTACLES->isObstacle(x, y))
  {
    x = rand() % randX;
    y = rand() % randY;
    x *= BLOCK_SIZE;
    y *= BLOCK_SIZE;
  }
}

void Snake::didEatFruit(Fruit &fruit)
{
  if(x == fruit.getX() && y == fruit.getY())
  {
    int w, h;
    getEmptySpot(w, h);
    grow();
    fruit.regrow(w, h);
    cout << "Time Test: " << now() - timePassed << endl;
    for(int i=0; i<GAME_LEVEL; i++)
    {
      getEmptySpot(w, h);
      OBSTACLES->addObstacle(w, h);
    }
  }
}

void Snake::grow()
{
  SnakeBox *sb = new SnakeBox(body[bodyLength]->getX(), body[bodyLength]->getY());
  body.push_back(sb);
  bodyLength++;

  MSG_SCORE->updateDisplayMsg("Score: " + to_string(bodyLength - 3));
}

void Snake::didHitObstacle(XInfo &xInfo)
{
  if(this->x < 0 || this->x > WIDTH_BOUND || this->y < 0 || this->y > HEIGHT_BOUND)
  {
    cout << x << " " << y << endl;
    gameEnd(xInfo, "Crush on Wall!");
  }
  else if(OBSTACLES->isObstacle(this->x, this->y))
  {
    gameEnd(xInfo, "Crush on Obstacle!");
  }
  else
  {
    for(int i=1; i<bodyLength; i++)
    {
      if(body[i]->getX() == this->x && body[i]->getY() == this->y)
      {
        gameEnd(xInfo, "Crush on Self!");
      }
    }
  }
}

void Snake::goW()
{
  if(direction == A || direction == D)
  {
    direction = W;
  }
}

void Snake::goS()
{
  if(direction == A || direction == D)
  {
    direction = S;
  }
}

void Snake::goA()
{
  if(direction == W || direction == S)
  {
    direction = A;
  }
}

void Snake::goD()
{
  if(direction == W || direction == S)
  {
    direction = D;
  }
}

bool Snake::isSnake(int cordX, int cordY)
{
  for(int i=0; i<bodyLength; i++)
  {
    if(cordX == body[i]->getX() && cordY == body[i]->getY())
    {
      return true;
    }
  }
  return false;
}
