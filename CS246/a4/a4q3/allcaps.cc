#include <iostream>
#include <string>
#include "allcaps.h"

//see header file
void Allcaps::setSource(std::istream *inp)
{
	this->currentTextProcessor->setSource(inp);
}

//see header file
std::string Allcaps::getWord()
{
	std::string word;
	word = currentTextProcessor->getWord();
	for(int i=0; i<word.length(); i++)
    		word[i] = toupper(word[i]);
	return word;
}

//see header file
bool Allcaps::fail() const
{
	return this->currentTextProcessor->fail();
}
