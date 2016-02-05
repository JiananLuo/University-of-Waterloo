#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "textprocess.h"
#include "echo.h"
#include "decorator.h"
#include "dropfirst.h"
#include "doublewords.h"
#include "allcaps.h"
#include "count.h"

/**************** main *************
     Purpose: Main function
     Error: None
************************************/
int main()
{
  string s;

  while(1)
  {
    getline(cin,s);
    if (cin.fail()) break;
    istringstream iss(s);
    string fname;
    iss >> fname;
    istream *in = (fname == "stdin") ? &cin : new ifstream(fname.c_str());

    TextProcessor *tp = new Echo;
    string dec;
    while (iss >> dec)
    {
      if (dec == "dropfirst")
      {
        int n;
        iss >> n;
        tp = new Dropfirst(tp, n);
      }
      else if (dec == "doublewords")
      {
        tp = new Doublewords(tp);
      }
      else if (dec == "allcaps")
      {
        tp = new Allcaps(tp);
      }
      else if (dec == "count")
      {
        char c;
        iss >> c;
        tp = new Count(tp, c);
      }
   } 

   tp->setSource(in);

   string word;

  while (word = tp->getWord(), !tp->fail())
  {
    cout << word << endl;
  }

   if (in != &cin) delete in;

   delete tp;
  }
}
