#include "q3printer.h"
#include "q3tallyVotes.h"
#include "q3voter.h"

#if defined(IMPLTYPE_INTB)

TallyVotes::TallyVotes(unsigned int group, Printer & printer)
	: tickets(0), serving(group), waitings(0), group(group), printer(printer), totalGiftshop(0), totalPicture(0), totalStatue(0) {
}

void TallyVotes::wait() {
	// wait until signalled
	this->bench.wait();
	// multiple bargers allowed
	while(rand() % 2 == 0) {
		// accept barging callers
		_Accept(TallyVotes::vote) {
		} _Else {
			// do not wait if no callers
		} // _Accept
	} // while
}

void TallyVotes::signalAll() {
	// drain the condition
	while(!this->bench.empty()) {
		this->bench.signal();
	}
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Ballot ballot) {
	unsigned int currentTickets = this->tickets++;
	while(currentTickets >= this->serving) {
		/* Barging State - start barging */
		this->printer.print(id, Voter::States::Barging);
		this->wait();
	}

/* Vote State - person can declear their ballot */
	printer.print(id, Voter::States::Vote, ballot);
	// count total votes
	this->totalPicture += ballot.picture;
	this->totalStatue += ballot.statue;
	this->totalGiftshop += ballot.giftshop;

	this->waitings++;
	if(this->waitings < this->group) {
/* Block state - block the person until the group is filled */
		printer.print(id, Voter::States::Block, waitings);
		this->wait();
/* Unblock state - unblock the person after the group is filled */
		printer.print(id, Voter::States::Unblock, waitings-1);
	} else {
/* Complete State - if group will filled by the current person */
		printer.print(id, Voter::States::Complete);
		this->signalAll();
	}
	this->waitings--;

	// find highest vote order by ranks
	Tour tour;
	if(this->totalGiftshop >= std::max(this->totalPicture, this->totalStatue)) {
		tour = TallyVotes::Tour::GiftShop;
	} else if(this->totalPicture >= std::max(this->totalGiftshop, this->totalStatue)) {
		tour = TallyVotes::Tour::Picture;
	} else {
		tour = TallyVotes::Tour::Statue;
	}
	// last person go, reset everthing
	if(this->waitings == 0) {
		this->totalPicture = 0;
		this->totalStatue = 0;
		this->totalGiftshop = 0;
		this->serving += this->group;
		this->signalAll();
	}

	return tour;
}

#endif
