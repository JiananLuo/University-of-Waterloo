#include <iostream>
#include <string>
#include "echo.h"
using namespace std;

//see header file
Echo::Echo(): source(0) {}//constructor

//see header file
void Echo::setSource(istream *in) { source = in; }

//see header file
string Echo::getWord() {
  string s;
  *source >> s;
  failed = source->fail();
  return s;
}

//see header file
bool Echo::fail() const { return failed; }
