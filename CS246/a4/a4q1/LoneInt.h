#ifndef __LONEINT_H__
#define __LONEINT_H__

#include "Expression.h"

class LoneInt : public Expression
{
	int num;//the number hold by loneint

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
/************* LoneInt ************
     Purpose: Constructor for LoneInt
     Returns: Nothing
     Error: None
************************************/
		LoneInt(int n);
};

#endif
