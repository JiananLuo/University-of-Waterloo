#include "Binary.h"
#include <iostream>
#include <string>

//see header file
void Binary::prettyprint()const
{
	std::cout << "(";
	this->left->prettyprint();
	std::cout << " ";
	std::cout << op;
	std::cout << " ";
	this->right->prettyprint();
	std::cout << ")";
}

//see header file
int Binary::evalute ()const
{
	if(op == '+')
		return this->left->evalute() +  this->right->evalute();
	else if(op == '-')
		return this->left->evalute() -  this->right->evalute();
	else if(op == '*')
		return this->left->evalute() *  this->right->evalute();
	else if(op == '/')
		return this->left->evalute() /  this->right->evalute();
	else
		return -1;
}

//see header file
Binary::Binary(char op, Expression * left, Expression * right)
{
	this->op = op;
	this->left = left;
	this->right = right;
}//constructor

//see header file
Binary::~Binary()
{
	delete this->left;
	delete this->right;
}//destructor
