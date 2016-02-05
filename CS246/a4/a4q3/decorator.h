#ifndef __DECORATOR_H__
#define __DECORATOR_H__

#include <iostream>
#include <string>
#include "textprocess.h"

class Decorator: public TextProcessor
{
	protected:
		TextProcessor * currentTextProcessor;//point to TextProcessor

		std::istream *source;//source
		bool failed;//bool
	public:
/********** Decorator **********
     Purpose: Constructor for Decorator
     Returns: Nothing
     Error: None
************************************/
		Decorator(TextProcessor * maTextProcessor);
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
/************ ~Decorator ***********
     Purpose: Destructor for Decorator
     Returns: Nothing
     Error: None
************************************/
		virtual ~Decorator();
};

#endif
