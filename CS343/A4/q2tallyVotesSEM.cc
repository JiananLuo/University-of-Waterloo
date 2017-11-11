#include "q2printer.h"
#include "q2tallyVotes.h"
#include "q2voter.h"

#if defined(IMPLTYPE_SEM)

TallyVotes::TallyVotes(unsigned int group, Printer & printer)
	: waitings(0), bargingLock(1), syncLock(0), group(group), printer(printer), totalGiftshop(0), totalPicture(0), totalStatue(0) {

}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Ballot ballot) {
	if (bargingLock.counter() <= 0) {
/* Barging State - start barging */
		this->printer.print(id, Voter::States::Barging);
	}
	bargingLock.P();
	this->totalPicture += ballot.picture;
	this->totalStatue += ballot.statue;
	this->totalGiftshop += ballot.giftshop;
/* Vote State - person can declear their ballot */
	this->printer.print(id, Voter::States::Vote, ballot);

	// default tour value
	Tour tour = Tour::Statue;
	if (waitings != group - 1) {
		this->waitings++;
/* Block state - block the person until the group is filled */
		this->printer.print(id, Voter::States::Block, this->waitings);
		bargingLock.V();
		syncLock.P();
/* Unblock state - unblock the person after the group is filled */
		this->waitings--;
		this->printer.print(id, Voter::States::Unblock, this->waitings);
	} else {
/* Complete State - if group will filled by the current person */
		this->printer.print(id, Voter::States::Complete);
		if(this->totalGiftshop >= std::max(this->totalPicture, this->totalStatue)) {
			tour = TallyVotes::Tour::GiftShop;
		} else if(this->totalPicture >= std::max(this->totalGiftshop, this->totalStatue)) {
			tour = TallyVotes::Tour::Picture;
		} else {
			tour = TallyVotes::Tour::Statue;
		}
	}

	if (waitings == 0) {
		// reset everthing
		this->totalPicture = 0;
		this->totalStatue = 0;
		this->totalGiftshop = 0;
		// release lock
		bargingLock.V();
	} else {
		// release lock
		syncLock.V();
	}
	return tour;
}

#endif
