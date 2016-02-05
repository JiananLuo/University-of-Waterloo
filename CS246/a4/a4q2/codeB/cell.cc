#include "cell.h"
#include "game.h"

// see header file
void Cell::notifyNeighbours()
{
  for(int i = 0; i<numNeighbours; i++)
  {
    neighbours[i]->notify(this->state,this->prevState);
  }
}

// see header file
void Cell::notifyGame()
{
  game->notify(this->r, this->c, this->prevState, this->state);
}

// see header file
Cell::Cell()
{
  state = 0;
  prevState = 0;
  numNeighbours = 0;
  game = NULL;
  for(int i=0; i<maxNeighbours; i++)
  {
    neighbours[i] = NULL;
  }
}//constructor

// see header file
char Cell::getState()
{
  return this->state + '0';
}

// see header file
void Cell::setState(const int& change)
{
  this->prevState = this->state;
  this->state = change;
}

// see header file
void Cell::setCoords(const int r, const int c)
{
  this->r = r;
  this->c = c;
}

// see header file
void Cell::setGame(Game * game)
{
  this->game = game;
}

// see header file
void Cell::addNeighbour(Cell *neighbour)
{
  neighbours[numNeighbours] = neighbour;
  numNeighbours++;
}

// see header file
void Cell::notify( const int & change)
{
  this->setState(change);
  this->notifyGame();
  this->notifyNeighbours();

}

// see header file
void Cell::notify( const int & current, const int & previous)
{
  if(current == previous)
    return;
  if(this->state == previous)
  {
    this->state = current;
    this->prevState = previous;
    this->notifyNeighbours();
    this->notifyGame();
  }
}
