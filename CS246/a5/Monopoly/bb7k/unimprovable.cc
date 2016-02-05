#include <string>

#include "unimprovable.h"

using namespace std;

//see header file
Unimprovable::Unimprovable(std::string name1, std::string name2, std::string player)
{
	std::string empty;
	this->line[0] = name1;
	this->line[1] = name2;
	this->line[3] = player;
	this->line[4] = "________";
}
