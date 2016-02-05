#ifndef __COUNT_H__
#define __COUNT_H__

#include <iostream>
#include <string>
#include "decorator.h"

//int initialCount = 1;
class Count: public Decorator
{
	char countChar;//the char need to be change
	int count;//number for count

	public:
/************** Count **************
     Purpose: Constructor for Count
     Returns: Nothing
     Error: None
************************************/
		Count(TextProcessor * maTextProcessor, char c) : Decorator(maTextProcessor), countChar(c), count(1) {};
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
