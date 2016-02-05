#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

using namespace std;

void ifile(TrieNode &t, string &filename)
{
  ifstream file(filename.c_str());
  while (true)
  {
    char  c;
    string  temp;
    string listo;
    file >> c;
    if(file.eof()) 
      break;
    switch( c ) 
    {
      case 'i':
      {
        file >> temp >> temp;
        ifile(t, temp);
        break;//include
      }
      case '+':
        file >> temp;
        t.insert(temp);
        break;//insert
      case '-':
        file >> temp;
        t.remove(temp);
        break;//remove
      case '?':
        file >> temp;
        listo = t.find(temp);
        if(listo.length() != 0)
        {
          listo.erase(listo.length()-1,1);
        }
        else
        {
          t.smartDelete(temp);
        }
        cout << listo << endl;
        break;//find
      case '$':
        cout << t.size() << endl;
        break;//size
    }
  }
}

int main()
{
  TrieNode t;

  while (true)
  {
    char  c;
    string  temp;
    string listo;
    cin >> c;
    if(cin.eof()) 
      break;
    switch( c ) 
    {
      case 'i':
      {
        cin >> temp >> temp;
        ifile(t, temp);
        break;
      }//include
      case '+':
        cin >> temp;
        t.insert(temp);
        break;//insert
      case '-':
        cin >> temp;
        t.remove(temp);
        break;//remove
      case '?':
        cin >> temp;
        listo = t.find(temp);
        if(listo.length() != 0)
        {
          listo.erase(listo.length()-1,1);
        }
        else
        {
          t.smartDelete(temp);
        }
        cout << listo << endl;
        break;//find
      case '$':
        cout << t.size() << endl;
        break;//size
    } // switch
  }
  //delete t; // while
} // main
