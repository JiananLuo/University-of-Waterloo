#include <iostream>
#include "game.h"

// see header file
void Game::clearGame()
{
  for(int i=0; i<gridSize; i++)
  {
    delete [] theGrid[i];
  }
  delete [] theGrid;
  for(int i=0; i<5; i++)
  {
    colours[i] = 0;
  }
}

// see header file
Game::Game()
{
  theGrid = NULL;
  gridSize = 0;
  notification = NULL;
}//constructor

// see header file
Game::~Game()
{
  this->clearGame();
}//destructor

// see header file
void Game::notify(int r, int c, unsigned int oldState, unsigned int newState)
{
  colours[oldState]--;
  colours[newState]++;
  //std::cout << newState << std::endl;
  notification->notify(r, c, newState);
}

// see header file
bool Game::isWon()
{
	for(int i=0; i<5; i++)
	{
		int single = colours[i];
		if(single == gridSize * gridSize)
		{
			return true;
		}
	}
	return false;
}

// see header file
void Game::init(int n, GameNotification *gameNotification)
{
  if(gridSize != 0)
  {
    this->clearGame();
  }
  gridSize = n;
  theGrid = new Cell*[gridSize];
  notification = gameNotification;

  for(int i=0; i<gridSize; i++)
  {
    theGrid[i] = new Cell[gridSize];
  }//new cells

  for(int i=0; i<5; i++)
  {
    colours[i]=0;
  }//set colours
  colours[0] = gridSize * gridSize;

  for(int r=0; r<gridSize; r++)
  {
    for(int c=0; c<gridSize; c++)
    {
      theGrid[r][c].setCoords(r, c);//set coordinate
      theGrid[r][c].setState(0);//set state
      theGrid[r][c].setGame(this);//set game
      //add neighbour
      if(r > 0)
      {
        theGrid[r][c].addNeighbour(& theGrid[r-1][c]);
      }
      if(r < gridSize-1)
      {
        theGrid[r][c].addNeighbour(& theGrid[r+1][c]);
      }
      if(c > 0)
      {
        theGrid[r][c].addNeighbour(& theGrid[r][c-1]);
      }
      if(c < gridSize-1)
      {
        theGrid[r][c].addNeighbour(& theGrid[r][c+1]);
      }
    }
  }
}

// see header file
void Game::change(const int & c)
{
  theGrid[0][0].notify(c);
}

// see header file
void Game::init(int r, int c, int change)
{
  if((r<= gridSize) && (c<= gridSize) && (r>= 0) && (c>= 0) && (change >= 0) && (change <= 5))
  {
    int pre = theGrid[r][c].getState() - '0';
    theGrid[r][c].setState(change);
    notify(r,c,pre,change);
  }
}
