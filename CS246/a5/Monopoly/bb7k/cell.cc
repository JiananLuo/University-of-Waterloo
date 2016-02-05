#include <iostream>
#include <string>
#include "cell.h"

using namespace std;

//see header file
void Cell::notifyPlayer(char piece, char active)
{
	if(active == '+')
	{
		this->line[3] += piece;
	}
	else if(active == '-')
	{
		size_t index = this->line[3].find(piece);
		this->line[3].erase(index, 1);
	}
	else
		cout << "Error! Not possiable!" << endl;
}

//see header file
void Cell::notifyBuilding(int level)
{
	std::string levelInRome;
	if(level == 1)
		levelInRome = "I";
	else if(level == 2)
		levelInRome = "II";
	else if(level == 3)
		levelInRome = "III";
	else if(level == 4)
		levelInRome = "IV";
	else if(level == 5)
		levelInRome = "V";
	else
		levelInRome = "";
	this->line[0] = levelInRome;
}

//see header file
string Cell::getLine(int lineNum)
{
	return line[lineNum];
}
