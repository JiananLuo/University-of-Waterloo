#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>
#include <sstream>

class View {

  protected:
    const int gridSize;
  public:
    View(int n);
    
 /*
  * The Controller calls notify to 
  * update the (r,c) location to be ch
  */
 virtual void notify(int r, int c, char ch) = 0;

 virtual void print(std::ostream &out) = 0;
    
 virtual ~View() = 0;
};

#endif
