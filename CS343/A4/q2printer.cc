#include <iostream>

#include "q2printer.h"
#include "q2tallyVotes.h"
#include "q2voter.h"

/**
  * Constructor
  */
Printer::Printer(unsigned int voters) {
	this->voters = voters;
	printerInfo = new PrinterInfo*[voters];
	for(unsigned int i=0; i<voters; i++) {
		printerInfo[i] = NULL;
		std::cout << "V" << i;
		if(i != voters-1) {
			std::cout << '\t';
		}
	}
	std::cout << '\n';
	for(unsigned int i=0; i<voters; i++) {
		printerInfo[i] = NULL;
		std::cout << "*******";
		if(i != voters-1) {
			std::cout << '\t';
		}
	}
	std::cout << '\n';
}

/**
  * Destructor
  */
Printer::~Printer() {
	this->printAllInfo();
	std::cout << "*****************" << std::endl;
	std::cout << "All tours started" << std::endl;

	delete[] printerInfo;
}

/**
  * Print all info on the printerInfo list
  */
void Printer::printAllInfo() {
	// find the last index of presentated state
	unsigned int endIndex = 0;
	for(unsigned int i=0; i<this->voters; i++) {
		if(this->printerInfo[i]) {
			endIndex = i;
		}
	}
	// start print all the states to the last index
	for(unsigned int i=0; i<this->voters; i++) {
		if(this->printerInfo[i]) {
			std::cout << (char) printerInfo[i]->state;
			if(this->printerInfo[i]->state == Voter::States::Vote) {
				// Vote case
				std::cout << " " << this->printerInfo[i]->ballot.picture << "," << this->printerInfo[i]->ballot.statue << "," << this->printerInfo[i]->ballot.giftshop;
			} else if(this->printerInfo[i]->state == Voter::States::Block || this->printerInfo[i]->state == Voter::States::Unblock) {
				// Block / Unblock case
				std::cout << " " << this->printerInfo[i]->numBlocked;
			} else if(this->printerInfo[i]->state == Voter::States::Finished) {
				// Finished case
				std::cout << " " << (char) this->printerInfo[i]->tour;
			}
			// reset the printerInfo
			delete this->printerInfo[i];
			this->printerInfo[i] = NULL;
		}
		if(i < endIndex) {
			std::cout << '\t';
		}
	}
	std::cout << '\n';
}

/**
  * Update state only to the printInfo element, if filled already, do printAllInfo
  */
void Printer::print(unsigned int id, Voter::States state) {
	if(printerInfo[id]) printAllInfo();
	printerInfo[id] = new PrinterInfo(state, TallyVotes::Tour::None, {}, (unsigned int) 0);
}

/**
  * Update state & tour to the printInfo element, if filled already, do printAllInfo
  */
void Printer::print(unsigned int id, Voter::States state, TallyVotes::Tour tour) {
	if(printerInfo[id]) printAllInfo();
	printerInfo[id] = new PrinterInfo(state, tour, {}, (unsigned int) 0);
}

/**
  * Update state & ballot to the printInfo element, if filled already, do printAllInfo
  */
void Printer::print(unsigned int id, Voter::States state, TallyVotes::Ballot ballot) {
	if(printerInfo[id]) printAllInfo();
	printerInfo[id] = new PrinterInfo(state, TallyVotes::Tour::None, ballot, (unsigned int) 0);
}

/**
  * Update state & numBlocked to the printInfo element, if filled already, do printAllInfo
  */
void Printer::print(unsigned int id, Voter::States state, unsigned int numBlocked) {
	if(printerInfo[id]) printAllInfo();
	printerInfo[id] = new PrinterInfo(state, TallyVotes::Tour::None, {}, numBlocked);
}
