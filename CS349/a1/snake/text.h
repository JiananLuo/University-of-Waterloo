#ifndef __TEXT_H__
#define __TEXT_H__

#include "displayable.h"

using namespace std;

class Text : public Displayable
{
  private:
    int x;
    int y;
    string s;

  public:
    virtual void paint(XInfo &xinfo);
    Text(int x, int y, string s):x(x), y(y), s(s) {}
    void updateDisplayMsg(string newString);
};

#endif
