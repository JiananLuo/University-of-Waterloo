#include "Unary.h"
#include <iostream>
#include <cstdlib> 
#include <string>

//see header file
void Unary::prettyprint()const
{
	if(op == 'a')
	{
		std::cout << "|";
		this->mid->prettyprint();
		std::cout << "|";
	}
	else
	{
		std::cout << "-";
		this->mid->prettyprint();
	}

}

//see header file
int Unary::evalute ()const
{
	if(op == 'a')
		return abs(this->mid->evalute());
	else
		return -1 * this->mid->evalute();
}

//see header file
Unary::Unary(char op, Expression * mid)
{
	this->op = op;
	this->mid = mid;
}//constructor

//see header file
Unary::~Unary()
{
	delete this->mid;
}//destructor
