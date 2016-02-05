#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>

#include "textDisplay.h"

using namespace std;

//see header file
TextDisplay::TextDisplay()
{
	room = new Cell*[40];
	for(int i=0; i<40; i++)
	{
		room[i] = NULL;
	}
}

//see header file
TextDisplay::~TextDisplay()
{
	for(int i=0; i<40; i++)
		delete room[i];
}

//see header file
void TextDisplay::init()
{
	string noPlayer;
	string emptyLine;
	room[0] = new Unimprovable("COLLECT", "OSAP", noPlayer);
	room[1] = new Improvable("AL", noPlayer);
	room[2] = new Unimprovable("SLC", emptyLine, emptyLine);
	room[3] = new Improvable("ML", noPlayer);
	room[4] = new Unimprovable("TUITION", emptyLine, noPlayer);
	room[5] = new Unimprovable("MKV", emptyLine, noPlayer);
	room[6] = new Improvable("ECH", noPlayer);
	room[7] = new Unimprovable("NEEDLES", "HALL", noPlayer);
	room[8] = new Improvable("PAS", noPlayer);
	room[9] = new Improvable("HH", noPlayer);
	room[10] = new Unimprovable("DC Tims", "Line", noPlayer);
	room[11] = new Improvable("RCH", noPlayer);
	room[12] = new Unimprovable("PAC", emptyLine, noPlayer);
	room[13] = new Improvable("DWE", noPlayer);
	room[14] = new Improvable("CPH", noPlayer);
	room[15] = new Unimprovable("UWP", emptyLine, noPlayer);
	room[16] = new Improvable("LHI", noPlayer);
	room[17] = new Unimprovable("SLC", emptyLine, noPlayer);
	room[18] = new Improvable("BMH", noPlayer);
	room[19] = new Improvable("OPT", noPlayer);
	room[20] = new Unimprovable("Goose", "Nesting", noPlayer);
	room[21] = new Improvable("EV1", noPlayer);
	room[22] = new Unimprovable("NEEDLES", "HALL", noPlayer);
	room[23] = new Improvable("EV2", noPlayer);
	room[24] = new Improvable("EV3", noPlayer);
	room[25] = new Unimprovable("V1", emptyLine, noPlayer);
	room[26] = new Improvable("PHYS", noPlayer);
	room[27] = new Improvable("B1", noPlayer);
	room[28] = new Unimprovable("CIF", emptyLine, noPlayer);
	room[29] = new Improvable("B2", noPlayer);
	room[30] = new Unimprovable("GO TO", "TIMS", noPlayer);
	room[31] = new Improvable("EIT", noPlayer);
	room[32] = new Improvable("ESC", noPlayer);
	room[33] = new Unimprovable("SLC", emptyLine, noPlayer);
	room[34] = new Improvable("C2", noPlayer);
	room[35] = new Unimprovable("REV", emptyLine, noPlayer);
	room[36] = new Unimprovable("NEEDLES", "HALL", noPlayer);
	room[37] = new Improvable("MC", noPlayer);
	room[38] = new Unimprovable("COOP", "FEE", noPlayer);
	room[39] = new Improvable("DC", noPlayer);
	
	//
}


//see header file
void TextDisplay::notifyPlayer(char piece, int buildingNum, char active, string mode)
{
	room[buildingNum]->notifyPlayer(piece, active);
	if(mode != "load")
	{
		this->print();//print the game board after player move
	}
}

//see header file
void TextDisplay::notifyBuilding(int level, int buildingNum, string mode)
{
	room[buildingNum]->notifyBuilding(level);
	if(mode != "load")
	{
		this->print();//print the game board after building change level
	}
}

//see header file
void TextDisplay::print()
{
	cout << setfill('_') << setw(100) << "" << endl;
	
	for(int line = 0; line < 5; line++)
	{
		
		for(int roomNum = 20; roomNum < 31; roomNum++)
		{
			cout << "|" << left << setfill(' ') << setw(8) << room[roomNum]->getLine(line);
		}
		cout << "|" << endl;
	}

	for(int firstRoomNum = 19; firstRoomNum > 10; firstRoomNum--)
	{

		int secondRoomNum = 50 - firstRoomNum;
		for(int line = 0; line < 5; line++)
		{
			cout << "|" << left << setfill(' ') << setw(8) << room[firstRoomNum]->getLine(line) << "|";
			if(firstRoomNum == 11 && line == 4)
				cout << right << setfill('_') << setw(81);
			else
				cout << right << setfill(' ') << setw(81);
			cout << "|" << left << setfill(' ') << setw(8) << room[secondRoomNum]->getLine(line) << "|"  << endl;
		}

	}


	for(int line = 0; line < 5; line++)
	{
		for(int roomNum = 10; roomNum > -1; roomNum--)
		{
			cout << "|" << left << setfill(' ') << setw(8) << room[roomNum]->getLine(line);
		}
		cout << "|" << endl;
	}
}
