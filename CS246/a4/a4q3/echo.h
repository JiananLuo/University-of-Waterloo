#ifndef __ECHO_H__
#define __ECHO_H__
#include <iostream>
#include <string>
#include "textprocess.h"

class Echo: public TextProcessor {
    std::istream *source;//source
    bool failed;//bool
 public:
/*************** Echo *************
     Purpose: Constructor for Echo
     Returns: Nothing
     Error: None
************************************/
    Echo();
/************* setSource ***********
     Purpose: Set the istream parameter to the field-source
     Returns: Nothing
     Error: None
************************************/
    void setSource(std::istream *inp);
/************** getWord ************
     Purpose: Return a string which is the motified source
     Returns: A string which is the motified source
     Error: None
************************************/
    std::string getWord();
/*************** fail *************
     Purpose: Return a bool to check if cin/iftream fail to read
     Returns: Bool
     Error: None
************************************/
    bool fail() const;
};

#endif
