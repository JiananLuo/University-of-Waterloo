#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <iostream>
#include "game.h"

class View;

// More documentation in controller.cc file

class Controller : public GameNotification {

    View *td; // The text display.
    View *gd; // The graphic display.
    
    Game *game;
    void init(std::istream & input, Game & g);

	///Helper to check if the game is in a win state
    //if yes, prints Won to stdout and returns true
    //if no, returns false
     bool checkWin(int movesLeft);

  public:
    Controller();
    ~Controller();
    void play(char typ = 'n');
    void notify(int r, int c, unsigned int state);   
};

#endif
