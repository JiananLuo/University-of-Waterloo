#include <string>

#include "improvable.h"

using namespace std;

//see header file
Improvable::Improvable(std::string buildingName, std::string player)
{
	string empty;
	this->line[0] = empty;
	this->line[1] = "--------";
	this->line[2] = buildingName;
	this->line[3] = player;
	this->line[4] = "________";
}
