#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

class Expression
{
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
/************ ~Expression **********
     Purpose: Destructor for Expression
     Returns: Nothing
     Error: None
************************************/
		virtual ~Expression();
};

#endif
