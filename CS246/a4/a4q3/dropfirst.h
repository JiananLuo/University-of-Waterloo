#ifndef __DROPFIRST_H__
#define __DROPFIRST_H__

#include <iostream>
#include <string>
#include "decorator.h"

class Dropfirst: public Decorator
{
	int numDrop;//the number of characters each word need to be droped

	public:
/********** Dropfirst **********
     Purpose: Constructor for Dropfirst
     Returns: Nothing
     Error: None
************************************/
		Dropfirst(TextProcessor * maTextProcessor, int numDrop) : Decorator(maTextProcessor), numDrop(numDrop) {};
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
