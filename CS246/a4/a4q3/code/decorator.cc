#include <iostream>
#include <string>
#include "decorator.h"

//see header file
Decorator::Decorator(TextProcessor * maTextProcessor)
{
	this->currentTextProcessor = maTextProcessor;
}//constructor

//see header file
void Decorator::setSource(std::istream *in) { source = in; }

//see header file
std::string Decorator::getWord()
{
	std::string s;
	*source >> s;
	failed = source->fail();
	return s;
}

//see header file
bool Decorator::fail() const { return failed; }

//see header file
Decorator::~Decorator()
{
	delete this->currentTextProcessor;
}//destructor
