#include <iostream>
#include <string>
using namespace std;

#include "drone.h"

int main() {
  Drone d;
  Position p;
  char c;
  while (cin >> c) {
    switch(c) {
      case 'f':
        d.forward();
        break;
      case 'b':
        d.backward();
        break;
      case 'l':
        d.left();
        break;
      case 'r':
        d.right();
        break;
      case 'c':
        p = d.current();
        cout << p.ew << " " << p.ns << endl;
        cout << (d.repeated() ? "Repeated" : "Not repeated") << endl;
        break;
      case 't':
        cout << d.totalDistance() << endl;
        break;
      case 'm':
        cout << d.manhattanDistance() << endl;
    }
  }
}
