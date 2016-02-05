#include "LoneInt.h"
#include <iostream>

//see header file
void LoneInt::prettyprint()const
{
	std::cout << this->num;
}

//see header file
int LoneInt::evalute()const
{
	return this->num;
}

//see header file
LoneInt::LoneInt(int n)
{
	this->num = n;
}//constructor
