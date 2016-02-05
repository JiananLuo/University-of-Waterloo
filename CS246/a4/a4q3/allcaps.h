#ifndef __ALLCAPS_H__
#define __ALLCAPS_H__

#include <iostream>
#include <string>
#include "decorator.h"

class Allcaps: public Decorator
{
	public:
/************* Allcaps *************
     Purpose: Constructor for Allcaps
     Returns: Nothing
     Error: None
************************************/
		Allcaps(TextProcessor * maTextProcessor) : Decorator(maTextProcessor) {};
/************* setSource ***********
     Purpose: Set the istream parameter to the field-source
     Returns: Nothing
     Error: None
************************************/
		virtual void setSource(std::istream *inp);
/************** getWord ************
     Purpose: Return a string which is the motified source
     Returns: A string which is the motified source
     Error: None
************************************/
		virtual std::string getWord();
/*************** fail *************
     Purpose: Return a bool to check if cin/iftream fail to read
     Returns: Bool
     Error: None
************************************/
		virtual bool fail() const;
};

#endif
