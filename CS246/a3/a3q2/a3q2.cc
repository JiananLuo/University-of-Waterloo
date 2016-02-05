#include "istring.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/* NOTES:

   MAKE SURE YOU UNDERSTAND WHAT THIS CODE DOES BEFORE TRYING TO WRITE TEST CASES.
  
   YOU SHOULD NOT NEED TO MODIFY THIS FILE.

   Commands are given in a regex style, e.g. saba, p a 3, f a, etc.
   Copy Constructor needs to work before operator* and operator+ can be tested.
   
   Note on commands: Spaces are not necessary but are used here for readability.
   All instances of source, source1, source2 and destination listed below are in the range [a-d].
   
   Command descriptions:
   s destination source1 source2 // operator+: destination = source1 + source2
   t destination source1 string  // operator+: destination = source1 + string
   r destination string          // operator>>: read a string into an iString object
   w source                      // operator<<: output the source iString object
   * destination int source      // operator*: destination = int * source 
   n destination string          // iString(char*): create an iString object with given string as contents
   i destination source          // copy constructor: copy an existing iString object (like strdup)
   = destination source          // assignment operator: copy an existing iString object
   f destination                 // default constructor: create empty iString (basically, empty string)
   e source                      // delete source: cleans up memory by calling destructor
   l source                      // print length of source iString
   c source                      // print capacity of source iString
   q/eof                         // terminates the test harness
*/
int main() {  
    bool     done = false;       // Received quit command or eof?
    iString *a[4] = {NULL, NULL, NULL, NULL}; // iString objects to manipulate
    
    while ( !done ) {
        char      c;     // command
        char      which; // which iString to modify; one of a, b, c or d.
        char      op1;   // command operands
        char      op2;
        int       int_op;
        string    temp;
        iString * tmp;   // temporary iString
    
//        cerr << "Command?" << endl;
        cin >> c;  
    
      if ( cin.eof() ) break;
    
        switch( c ) {
          case 'r':
              cin >> which;  

              /* 
               * The following kind of calculation is explained once and used throughout.
               *
               * "which" is a char whose valid values are a, b, c, or d; otherwise, the
               * program behaviour is undefined. Subtracting 'a' from which will give us
               * a value in the range 0 to 3. This is used to index into the "a" array
               * that stores our iStrings.
               */
              delete a[which-'a'];
              a[which-'a'] = new iString;
              cin >> *(a[which-'a']); //whitespace delimited read
//cout << strlen((*(a[which-'a'])).chars);
              break;
          
          case 'w':
              cin >> which;  
              if ( a[which-'a'] != NULL ) cout << *(a[which-'a']) << endl;
//		if((*(a[which-'a'])).chars != NULL)
//cout << strlen((*(a[which-'a'])).chars) << endl;
              break;
          
          case 'n':
              cin >> which >> temp;
              delete a[which-'a'];
              a[which-'a'] = new iString( temp.c_str() );
              break;
          
          case 'i':
              cin >> op1 >> op2;
              tmp = new iString( *(a[op2-'a']) );
              delete a[op1-'a'];
              a[op1-'a'] = tmp;
              break;
          
          case '=':
              cin >> op1 >> op2;
              *a[op1-'a'] = *a[op2-'a'];
              break;
          
          case 's':
              cin >> which >> op1 >> op2;
              tmp = new iString( *(a[op1-'a']) + *(a[op2-'a']) );
              delete a[which-'a'];
              a[which-'a'] = tmp;
              break;
          
          case 't':
              cin >> which >> op1 >> temp;
              tmp = new iString(*(a[op1-'a']) + temp.c_str());
              delete a[which-'a'];
              a[which-'a'] = tmp;
              break;
          
          case '*':
              cin >> which >> int_op >> op2;
              tmp = new iString( (int_op * *(a[op2-'a'])) );
              delete a[which-'a'];
              a[which-'a'] = tmp;
              break;
          
          case 'e':
              cin >> which;
              delete a[which-'a'];
              a[which-'a'] = NULL;
              break;
          
          case 'f':
              cin >> which;
              delete a[which-'a'];
              a[which-'a'] = new iString();
              break;
          
          case 'l':
              cin >> which;
              if ( a[which-'a'] != NULL ) cout << a[which-'a']->length << endl;
              break;
          
          case 'c':
              cin >> which;
              if ( a[which-'a'] != NULL ) cout << a[which-'a']->capacity << endl;
              break;
         
          case 'q': 
              done = true;
     
        } // switch
    } // while
} // main
