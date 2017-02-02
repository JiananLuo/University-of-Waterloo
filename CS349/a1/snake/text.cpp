#include "text.h"

void Text::paint(XInfo &xInfo)
{
  XSetForeground(xInfo.display, xInfo.gc[0], BlackPixel(xInfo.display, xInfo.screen));
  XDrawImageString( xInfo.display, xInfo.bufferWindow, xInfo.gc[0], this->x, this->y, this->s.c_str(), this->s.length());
}

void Text::updateDisplayMsg(string newString)
{
  this->s = newString;
}
