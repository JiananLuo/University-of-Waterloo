#include "q3printer.h"
#include "q3tallyVotes.h"
#include "q3voter.h"

#if defined(IMPLTYPE_TASK)

TallyVotes::TallyVotes(unsigned int group, Printer & printer)
	: tour(0), waitings(0), group(group), printer(printer), totalGiftshop(0), totalPicture(0), totalStatue(0) {

}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Ballot ballot) {
	TallyVotes::id = id;
	TallyVotes::ballot = ballot;
	this->bench.wait(id);
	return (TallyVotes::Tour) this->tour;
}

void TallyVotes::main() {
	for(;;) {
		_Accept(~TallyVotes) {
			return;
		} or _Accept(vote) {
			/* Vote State - person can declear their ballot */
			printer.print(id, Voter::States::Vote, ballot);
			// count total votes
			this->totalPicture += ballot.picture;
			this->totalStatue += ballot.statue;
			this->totalGiftshop += ballot.giftshop;

			printer.print(id, Voter::States::Block, ++waitings);
			if(this->waitings == this->group) {
/* Complete State - if group will filled by the current person */
				printer.print(id, Voter::States::Complete);

				// find highest vote order by ranks
				if(this->totalGiftshop >= std::max(this->totalPicture, this->totalStatue)) {
					tour = TallyVotes::Tour::GiftShop;
				} else if(this->totalPicture >= std::max(this->totalGiftshop, this->totalStatue)) {
					tour = TallyVotes::Tour::Picture;
				} else {
					tour = TallyVotes::Tour::Statue;
				}
				// last person go, reset everthing
				this->totalPicture = 0;
				this->totalStatue = 0;
				this->totalGiftshop = 0;

				while(!this->bench.empty()) {
/* Unblock state - unblock the person after the group is filled */
					printer.print(this->bench.front(), Voter::States::Unblock, --waitings);
					this->bench.signalBlock();
				}
			}
		}
	}
}
#endif

