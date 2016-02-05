#include <iostream>
#include <string>
#include "doublewords.h"

//see header file
void Doublewords::setSource(std::istream *inp)
{
	this->currentTextProcessor->setSource(inp);
}

//see header file
std::string Doublewords::getWord()
{
	std::string word;
	word = currentTextProcessor->getWord();
	word = word + '\n' + word;
	return word;
}

//see header file
bool Doublewords::fail() const
{
	return this->currentTextProcessor->fail();
}
