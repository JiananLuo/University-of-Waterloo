#ifndef __TEXTPROCESS_H__
#define __TEXTPROCESS_H__
#include <iostream>
#include <string>

class TextProcessor {
  public:
/************* setSource ***********
     Purpose: Set the istream parameter to the field-source
     Returns: Nothing
     Error: None
************************************/
    virtual void setSource(std::istream *inp) = 0;
/************** getWord ************
     Purpose: Return a string which is the motified source
     Returns: A string which is the motified source
     Error: None
************************************/
    virtual std::string getWord() = 0;
/************** ************
     Purpose: Return a bool to check if cin/iftream fail to read
     Returns: Bool
     Error: None
************************************/
    virtual bool fail() const = 0;
/********** ~TextProcessor **********
     Purpose: Destructor for TextProcessor
     Returns: Nothing
     Error: None
************************************/
    virtual ~TextProcessor();
};

#endif
