#include <iostream>
#include <string>
#include <sstream>
#include "count.h"

//see header file
void Count::setSource(std::istream *inp)
{
	this->currentTextProcessor->setSource(inp);
}

//see header file
std::string Count::getWord()
{
	std::string word;
	std::string newWord;
	word = currentTextProcessor->getWord();
	int len = word.length();
	for(int i=0; i<len; i++)
	{
		if(word[i] == this->countChar)
		{
			std::stringstream ss;
			ss << this->count;
			newWord += ss.str();
			this->count++;
		}
		else
			newWord += word[i];
	}
	return newWord;
}

//see header file
bool Count::fail() const
{
	return this->currentTextProcessor->fail();
}
