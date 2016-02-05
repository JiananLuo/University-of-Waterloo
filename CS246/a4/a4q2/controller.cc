#include "controller.h"
#include "game.h"
#include "textdisplay.h"
//#include "graphicdisplay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// see header file
Controller::Controller(){
    game = new Game();
    td = NULL;
// TODO - for part (b)
}//constructor

/*
 * Update the View(s) to indicate the new game state
*/
void Controller::notify(int r, int c, unsigned int state)
{
	this->td->notify(r, c, state + '0');
}

/*
 * Called when command init is received
*/
void Controller::init(istream & input, Game & g)
{
  int r, c, change;
  
  while(input >> r >> c)
  {
    if (r == -1 && c == -1)
      break;
    else
    {
      input >> change;
      g.init(r, c, change);
    }
  }
}

// see header file
bool Controller::checkWin(int movesLeft){
  if(game->isWon() && movesLeft != 0){
    cout << "Won" << endl;
    return true;
  }
  return false;
}

// main play function recieves input and tell others what to do
void Controller::play(){
  srand(time(NULL));
  int moves = 0;
  string cmd;
  bool playing = false;
  while (cin >> cmd) {
    if (cmd == "new") {
      int n;
      cin >> n; 
      game->init(n, this);
      delete td;
      td = new TextDisplay(n);
// Uncomment for part (b)
//      gd = new GraphicDisplay(n);

      moves = 0;
    }
// the ? command is only needed for part (b)
// when graphics command line is enabled
//    else if (cmd == "?"){
//         cout << "White: 0" << endl;
//         cout << "Black: 1" << endl;
//         cout << "Red:   2" << endl;
//         cout << "Green: 3" << endl;
//         cout << "Blue:  4" << endl;
//
//    }

    else if (cmd == "init") {
      init(cin, *game);
      #if DEBUG
      cout << "Done initialization" << endl;
      #endif
      td->print(cout);
      if (checkWin(moves)){
        break;
      }
    }
    else if (cmd == "include"){
       string file;
       cin >> file;
       ifstream input(file.c_str());
       init(input, *game);
       td->print(cout);
       if (checkWin(moves)){
        break;
      }
    }
    else if (cmd == "switch") {
      if (checkWin(moves)){
        break;
      }
      if(moves > 0){
        int next;
        if (cin >> next && (next >= 0 || next <= 4)){
          game->change(next);
          td->print(cout);
          --moves;
	       if (moves == 1) {
          cout << moves << " move left" << endl;
	       }
         else {
          cout << moves << " moves left" << endl;
	       }
         if(game->isWon()){
	         cout << "Won" << endl;
	         break;
	       }
 	       if(moves == 0){
  	         cout << "Lost" << endl;
	         break;
	       }
        }
        else cerr << "Invalid move" << endl;
      }
    }
    else if (cmd == "game" && !playing){
      cin >> moves;
      if (moves < 0) {
        moves = 0;
      } 
      else if (moves == 1) {
        cout << moves << " move left" << endl;
      }
      else { 
        cout << moves << " moves left" << endl;
      }
      if (checkWin(moves)){
        break;
      }
    }
  }
}

// see header file
Controller::~Controller()
{
	delete td;
	delete game;
}//destructor
