#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__

#include "window.h"
#include "view.h"


class GraphicDisplay : public View
{
    Xwindow * windows;          //the n x n display 
  
    public:
        GraphicDisplay(int n); //one arg constructor where the parameter is the gridSize

        ~GraphicDisplay(); //dtor
  
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
