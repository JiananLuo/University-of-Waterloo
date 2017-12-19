#include <algorithm>
#include <iostream>

#include "q3voter.h"
#include "q3tallyVotes.h"
#include "q3printer.h"

#if defined(IMPLTYPE_BAR)

TallyVotes::TallyVotes(unsigned int group, Printer &printer)
	: uBarrier(group), group(group), printer(printer), totalGiftshop(0), totalPicture(0), totalStatue(0) {
}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Ballot ballot) {
/* Vote State - person can declear their ballot */
	this->printer.print(id, Voter::States::Vote, ballot);
	// update total group count
	this->totalPicture += ballot.picture;
	this->totalStatue += ballot.statue;
	this->totalGiftshop += ballot.giftshop;

	if(waiters() == total()-1) {
/* Complete State - if group will filled by the current person */
		uBarrier::block();
		this->printer.print(id, Voter::States::Complete);
	} else {
/* Block state - block the person until the group is filled */
		this->printer.print(id, Voter::States::Block, waiters() +1);
		uBarrier::block();
/* Unblock state - unblock the person after the group is filled */
		this->printer.print(id, Voter::States::Unblock, waiters());
	}
	return (TallyVotes::Tour) this->tour;
}

void TallyVotes::last() {
	// find the max vote place with pirority Giftshop > Picture > Statue
	if(this->totalGiftshop >= std::max(this->totalPicture, this->totalStatue)) {
		this->tour = TallyVotes::Tour::GiftShop;
	} else if(this->totalPicture >= std::max(this->totalGiftshop, this->totalStatue)) {
		this->tour = TallyVotes::Tour::Picture;
	} else {
		this->tour = TallyVotes::Tour::Statue;
	}
	// reset
	this->totalGiftshop = 0;
	this->totalPicture = 0;
	this->totalStatue = 0;
}

#endif
