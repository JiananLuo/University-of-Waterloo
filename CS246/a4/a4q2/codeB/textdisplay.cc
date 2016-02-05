#include "view.h"
#include "textdisplay.h"

// see header file
TextDisplay::TextDisplay(int n): View(n)
{
  theDisplay = new char*[n];

  for (int i=0; i<n; i++)
  {
    theDisplay[i] = new char[n];
  }
  for(int r=0; r<n; r++)
  {
    for(int c=0; c<n; c++)
    {
      theDisplay[r][c] = '0';
    }
  }
}//constructor

// see header file
TextDisplay::~TextDisplay()
{
  for(int i=0; i<gridSize; i++)
  {
    delete [] theDisplay[i];
  }
  delete [] theDisplay;
}//destructor

// see header file
void TextDisplay::notify(int r, int c, char ch)
{
  theDisplay[r][c] = ch;
}

// see header file
void TextDisplay::print(std::ostream &out)
{
  for(int i=0; i<gridSize; i++)
  {
    for(int j=0; j<gridSize; j++)
    {
      out << theDisplay[i][j];
    }
    out << '\n';
  }
}
