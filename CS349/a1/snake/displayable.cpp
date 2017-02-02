#include "displayable.h"
#include "game.h"

using namespace std;

XColor snakeColor, fruitColor, obstacleColor;

void error( string str )
{
  cerr << str << endl;
  exit(0);
}

void initX(int argc, char *argv[], XInfo &xInfo)
{
  xInfo.width = 800;
  xInfo.height = 600;
	XSizeHints hints;
	unsigned long white, black;

   /*
	* Display opening uses the DISPLAY	environment variable.
	* It can go wrong if DISPLAY isn't set, or you don't have permission.
	*/
	xInfo.display = XOpenDisplay( "" );
	if ( !xInfo.display )	{
		error( "Can't open display." );
	}

   /*
	* Find out some things about the display you're using.
	*/
	xInfo.screen = DefaultScreen( xInfo.display );
  xInfo.colorMap = DefaultColormap(xInfo.display, xInfo.screen);

	white = XWhitePixel( xInfo.display, xInfo.screen );
	black = XBlackPixel( xInfo.display, xInfo.screen );

	hints.x = 100;
	hints.y = 100;
	hints.width = 800;
	hints.height = 600;
	hints.flags = PPosition | PSize;

	xInfo.window = XCreateSimpleWindow(
		xInfo.display,				// display where window appears
		DefaultRootWindow( xInfo.display ), // window's parent in window tree
		hints.x, hints.y,			// upper left corner location
		hints.width, hints.height,	// size of the window
		Border,						// width of window's border
		black,						// window border colour
		white );					// window background colour


  int depth = DefaultDepth(xInfo.display, xInfo.screen);
  xInfo.bufferWindow = XCreatePixmap(xInfo.display, xInfo.window, xInfo.width, xInfo.height, depth);

	XSetStandardProperties(
		xInfo.display,		// display containing the window
		xInfo.window,		// window whose properties are set
		"animation",		// window's title
		"Animate",			// icon's title
		None,				// pixmap for the icon
		argv, argc,			// applications command line args
		&hints );			// size hints for the window

	/*
	 * Create Graphics Contexts
	 */
	int i = 0;
	xInfo.gc[i] = XCreateGC(xInfo.display, xInfo.window, 0, 0);
	XSetForeground(xInfo.display, xInfo.gc[i], BlackPixel(xInfo.display, xInfo.screen));
	XSetBackground(xInfo.display, xInfo.gc[i], WhitePixel(xInfo.display, xInfo.screen));
	XSetFillStyle(xInfo.display, xInfo.gc[i], FillSolid);
	XSetLineAttributes(xInfo.display, xInfo.gc[i],
	                     1, LineSolid, CapButt, JoinRound);

	XSelectInput(xInfo.display, xInfo.window,
		ButtonPressMask | KeyPressMask |
		PointerMotionMask |
		EnterWindowMask | LeaveWindowMask |
		StructureNotifyMask);  // for resize events

	/*
	 * Put the window on the screen.
	 */
	XMapRaised( xInfo.display, xInfo.window );
	XFlush(xInfo.display);
}

void initColor(XInfo &xInfo)
{
  snakeColor.red = 0; snakeColor.green = 65000; snakeColor.blue = 0;
  XAllocColor(xInfo.display, xInfo.colorMap, &snakeColor);

  fruitColor.red = 65000; fruitColor.green = 0; fruitColor.blue = 0;
  XAllocColor(xInfo.display, xInfo.colorMap, &fruitColor);

  obstacleColor.red = 0; obstacleColor.green = 0; obstacleColor.blue = 0;
  XAllocColor(xInfo.display, xInfo.colorMap, &obstacleColor);
}

void repaint(XInfo &xInfo)
{
  XSetForeground(xInfo.display, xInfo.gc[0], WhitePixel(xInfo.display, xInfo.screen));
  XFillRectangle(xInfo.display, xInfo.bufferWindow, xInfo.gc[0], 0, 0, WIDTH, HEIGHT);

  //start print
  list<Displayable *>::const_iterator begin = dList.begin();
  list<Displayable *>::const_iterator end = dList.end();
  while( begin != end )
  {
    Displayable *d = *begin;
    d->paint(xInfo);
    begin++;
  }

  XCopyArea(xInfo.display, xInfo.bufferWindow, xInfo.window, xInfo.gc[0], 0, 0, xInfo.width, xInfo.height, 0, 0);
	XFlush( xInfo.display );
}
