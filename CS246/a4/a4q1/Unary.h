#ifndef __UNARY_H__
#define __UNARY_H__

#include "Expression.h"

class Unary : public Expression
{
	char op;//unary operator ABS/NEG
	Expression * mid;//point to the mid Expression which hold by the Unary

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
		virtual int evalute()const;
/************** Unary ************
     Purpose: Constructor for Unay
     Returns: Nothing
     Error: None
************************************/
		Unary(char op, Expression * mid);
/************ ~Unary **********
     Purpose: Destructor for Unary
     Returns: Nothing
     Error: None
************************************/
		~Unary();
};

#endif
