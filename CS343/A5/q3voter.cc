#include <iostream>

#include "q3printer.h"
#include "q3tallyVotes.h"
#include "q3voter.h"
#include "MPRNG.h"

extern MPRNG mprng;

Voter::Voter(unsigned int id, TallyVotes &voteTallier, Printer &printer)
		: id(id), voteTallier(voteTallier), printer(printer) {}

TallyVotes::Ballot Voter::cast() {
	// cast 3-way vote
	static unsigned int voting[3][2][2] = { { {2,1}, {1,2} }, { {0,2}, {2,0} }, { {0,1}, {1,0} } };
	unsigned int picture = mprng( 2 ), statue = mprng( 1 );
	return (TallyVotes::Ballot){ picture, voting[picture][statue][0], voting[picture][statue][1] };
}

void Voter::main() {
	// yield a random number of times, between 0 and 19 inclusive, so all tasks do not start simultaneously
	yield(mprng(19));
	// print start message
	this->printer.print(this->id, Voter::States::Start);
	// yield once
	yield(1);
	// vote
	TallyVotes::Tour tour = this->voteTallier.vote(this->id, this->cast());
	// yield once
	yield(1);
	// print finish message
	this->printer.print(this->id, Voter::States::Finished, tour);
}
