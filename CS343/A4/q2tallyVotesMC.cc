#include <algorithm>
#include <iostream>

#include "q2voter.h"
#include "q2tallyVotes.h"
#include "q2printer.h"

#if defined(IMPLTYPE_MC)

TallyVotes::TallyVotes(unsigned int group, Printer &printer)
	: group(group), printer(printer), totalGiftshop(0), totalPicture(0), totalStatue(0) {
	this->isBarging = false;
	this->waiting = 0;
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Ballot ballot) {
	// acquire the sync lock
	this->ownerLock.acquire();

	if (this->isBarging) {
/* Barging State - start barging */
		this->printer.print(id, Voter::States::Barging);
		this->condLockBarging.wait(this->ownerLock);
	}
/* Vote State - person can declear their ballot */
	this->printer.print(id, Voter::States::Vote, ballot);
	// update total group count
	this->totalPicture += ballot.picture;
	this->totalStatue += ballot.statue;
	this->totalGiftshop += ballot.giftshop;

	if (this->waiting == group - 1) {
/* Complete State - if group will filled by the current person */
		printer.print(id, Voter::States::Complete);
	} else {
		// otherwise, the group is not filled yet
		if (this->condLockBarging.empty()) {
			// no barging case
			this->isBarging = false;
		} else {
			// barging case
			this->isBarging = true;
			this->condLockBarging.signal();
		}
/* Block state - block the person until the group is filled */
		this->waiting++;
		printer.print(id, Voter::States::Block, this->waiting);
		this->condLockBlock.wait(this->ownerLock);
/* Unblock state - unblock the person after the group is filled */
		this->waiting--;
		printer.print(id, Voter::States::Unblock, this->waiting);
		if (this->condLockBlock.empty()) {
			this->isBarging = false;
		}
	}

	// find the max vote place with pirority Giftshop > Picture > Statue
	Tour tour;
	if (this->totalGiftshop >= std::max(this->totalPicture, this->totalStatue)) {
		tour = Tour::GiftShop;
	} else if (this->totalPicture >= std::max(this->totalStatue, this->totalGiftshop)) {
		tour = Tour::Picture;
	} else {
		tour = Tour::Statue;
	}

	if (this->condLockBlock.empty()) {
		// group not filled yet, reset everything
		this->totalPicture = 0;
		this->totalStatue = 0;
		this->totalGiftshop = 0;
		if (!this->condLockBarging.empty()) {
			// barging case 
			this->isBarging = true;
			this->condLockBarging.signal();
		}
	} else {
		// group not filled yet
		this->isBarging = true;
		this->condLockBlock.signal();
	}

	// release the sync lock
	this->ownerLock.release();
	return tour;
}

#endif
