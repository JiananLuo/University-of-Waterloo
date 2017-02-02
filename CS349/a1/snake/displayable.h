#ifndef __DISPLAYABLE_H__
#define __DISPLAYABLE_H__

#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*
 * Global game state variables
 */
const int Border = 1;
const int BufferSize = 10;
const int WIDTH = 800;
const int HEIGHT = 600;

extern XColor snakeColor, fruitColor, obstacleColor;

/*
 * Information to draw on the window.
 */
struct XInfo {
	Display	 *display;
	int		 screen;
	Window	 window;
	GC		 gc[3];
	int		width;		// size of window
	int		height;
	Colormap colorMap;
	Pixmap bufferWindow;
};

/*
 * An abstract class representing displayable things.
 */
class Displayable {
	public:
		virtual void paint(XInfo &xInfo) = 0;
};

void error(std::string str);
void initX(int argc, char *argv[], XInfo &xInfo);
void initColor(XInfo &xInfo);
void repaint(XInfo &xInfo);
#endif
