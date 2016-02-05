#include <iostream>
#include <string>
#include "dropfirst.h"

//see header file
void Dropfirst::setSource(std::istream *inp)
{
	this->currentTextProcessor->setSource(inp);
}

//see header file
std::string Dropfirst::getWord()
{

	std::string singleWord;
	std::string newWord;
	std::string empty;

	while(newWord.length() == 0)
	{
		singleWord.clear();
		newWord.clear();

		std::string word = currentTextProcessor->getWord();
		if(fail())
			break;

		for(int i=0; i<word.length(); i++)
		{
			if(this->fail())
				break;
			if(word[i] == '\n')
			{
					singleWord.erase(0,this->numDrop);
					newWord += singleWord;
					if(singleWord.length() > this->numDrop)
						newWord += '\n';
					singleWord.clear();
			}
			else
			{
				singleWord+=word[i];
			}
		}
		singleWord.erase(0,this->numDrop);
		newWord += singleWord;
	}

	return newWord;
}

//see header file
bool Dropfirst::fail() const
{
	if(this->failed == true)
		return true;
	return this->currentTextProcessor->fail();
}
