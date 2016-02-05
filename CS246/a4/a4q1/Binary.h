#ifndef __BINARY_H__
#define __BINARY_H__

#include "Expression.h"

class Binary : public Expression
{
	char op;//Binary operation: +/-/*//
	Expression * left;//point to the left Expression which hold by the Binary
	Expression * right;//point to the right Expression which hold by the Binary

	public:
/*********** prettyprint ***********
     Purpose: Print the prefect expression
     Returns: Nothing
     Error: None
************************************/
		virtual void prettyprint()const;
/************** evalute ************
     Purpose: Returns a int which represent the value after evaluation
     Returns: Int which is the value after evalute
     Error: None
************************************/
		virtual int evalute ()const;
/************** Binary ************
     Purpose: Constructor for Binay
     Returns: Nothing
     Error: None
************************************/
		Binary(char op, Expression * left, Expression * right);
/************ ~Binary **********
     Purpose: Destructor for Binary
     Returns: Nothing
     Error: None
************************************/
		~Binary();

};

#endif
