#ifndef __ISTRING_H__
#define __ISTRING_H__
#include <iostream> 

struct iString{
	char * chars;
	unsigned int length;
	unsigned int capacity;
	/************* iString *************
	     Purpose: Constructor of iString
	     Returns: Constructor returns nothing
	     Error: None
	************************************/
	iString();
	/************** iString ************
	     Purpose: Copy constructor of iString
	     Returns: Constructor returns nothing
	     Error: None
	************************************/
	iString(const char * other);

	/************** iString ************
	     Purpose: Copy constructor of iString
	     Returns: Constructor returns nothing
	     Error: None
	************************************/
	iString(const iString& other);
	/************** ~iString() ************
	     Purpose: Destructor for the iString
	     Returns: Return nothing
	     Error: None
	************************************/
	~iString();
	/************** operator= ************
	     Purpose: Assignment operator of iString
	     Returns: Return a reference of an iString
	     Error: None
	************************************/
	iString& operator=(const iString& other);
};

/************** operator+ ************
     Purpose: Plus operator of iString
     Returns: Return a reference of an iString which is the summation of two iStrings
     Error: None
************************************/
iString operator+(const iString& s1, const iString& s2);
/************** operator+ ************
     Purpose: Plus operator of iString
     Returns: Return a reference of an iString which is the summation of an iStrings and a char
     Error: None
************************************/
iString operator+(const iString& s1, char * chars);
/************** operator* ************
     Purpose: Multiply operator of iString
     Returns: Return a reference of an iString which is the production of an integer and an iStrings
     Error: None
************************************/
iString operator*(int n, const iString& other);
/************** operator>> ************
     Purpose: Input operator of iString
     Returns: Return a istream for the iString
     Error: None
************************************/
std::istream &operator>>(std::istream &in, iString &s);
/************** operator<< ************
     Purpose: Output operator of iString
     Returns: Return a ostream for the iString
     Error: None
************************************/
std::ostream &operator<<(std::ostream &out, const iString &s);
#endif
