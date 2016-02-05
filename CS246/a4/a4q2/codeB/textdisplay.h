#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>
#include "view.h"

class TextDisplay : public View {
  char **theDisplay;          //the n x n display 
  
 public:
  TextDisplay(int n); //one arg constructor where the parameter is the gridSize

  ~TextDisplay(); //dtor
  
  /*
   * The Controller calls notify to 
   * update the (r,c) location to be ch
   */
  virtual void notify(int r, int c, char ch);

  /*
   * Prints the grid as specified in the assignment specification.
   */
  virtual void print(std::ostream &out);
};

#endif
