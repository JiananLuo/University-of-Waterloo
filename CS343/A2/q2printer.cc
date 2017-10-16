#include <iostream>
#include "q2printer.h"

using namespace std;

// constructor
Printer::Printer(const unsigned int NoOfPlayers, const unsigned int NoOfCards) {
	this->totalPlayers = NoOfPlayers;
	this->numOfCardsLeft = NoOfCards;
	this->printerInfo = new PrinterInfo[NoOfPlayers];
}

// destructor
Printer::~Printer() {
	delete this->printerInfo;
}

void Printer::printAllInfo() {
	// start print
	int endIndex = 0;
	for(int i=0; i<this->totalPlayers; i++) {
		if(this->printerInfo[i].deckTake != 0) {
			endIndex = i;
		}
	}
	for(int i=0; i<=endIndex; i++) {
		int deckTake = this->printerInfo[i].deckTake;
		int deckLeft = this->printerInfo[i].deckLeft;

		if(deckTake == -1) {
			// print drink
			cout << "D";
		} else if(deckTake != 0) {
			// print normal deck
			if(this->printerInfo[i].playerLeft == 1) {
				// case WIN 1 player left
				cout << '#' << deckTake << '#';
			} else if (deckLeft == 0) {
				// case WIN player take last deck
				cout << deckTake << ":" << deckLeft << '#';
			} else {
				// case CONTINUE pass deck
				cout << deckTake << ":" << deckLeft;
				(deckLeft % 2 == 0) ? cout << '>' : cout << '<';
			}
			// case die
			if((deckLeft + deckTake) % 7 == 0) {
				cout << 'X';
			}
		}

		// print indentation
		if(i != endIndex) {
			cout << '\t';
		} else {
			cout << '\n';
		}

		// reset
		this->printerInfo[i].deckTake = 0;
	}
}

void Printer::prt(unsigned int id, int took, int RemainingPlayers) {
	// if print info filled, print
	if(this->printerInfo[id].deckTake != 0) {
		printAllInfo();
	}

	// overwrite print info
	this->printerInfo[id].deckTake = took;
	if(took != -1) {
		this->numOfCardsLeft -= took;
	}
	this->printerInfo[id].deckLeft = numOfCardsLeft;
	this->printerInfo[id].playerLeft = RemainingPlayers;

	// if remaining player equals to 1, print again
	if(RemainingPlayers == 1) {
		printAllInfo();
	}
}
