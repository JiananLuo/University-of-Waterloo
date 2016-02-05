#include "view.h"
#include "graphicdisplay.h"
#include "window.h"

// see header file
GraphicDisplay::GraphicDisplay(int n): View(n)
{
	windows = new Xwindow();

	for(int r=0; r<n; r++)
		for(int c=0; c<n; c++)
			windows->fillRectangle(r*48, c*48, 48, 48, 0);
}//constructor

// see header file
GraphicDisplay::~GraphicDisplay()
{
	delete windows;
}//destructor

// see header file
void GraphicDisplay::notify(int r, int c, char ch)
{
	windows->fillRectangle(r*48, c*48, 48, 48, ch-'0');
}

// see header file
void GraphicDisplay::print(std::ostream &out)
{

}
