#ifndef __VOTER__
#define __VOTER__

#include "q2tallyVotes.h"

_Task Voter {
	private:
		unsigned int id;
		TallyVotes & voteTallier;
		Printer & printer;

		// Choose ranking of picture tour, then relationship of statue to gift shop.
		TallyVotes::Ballot cast();
		void main();
	public:
		enum States {
			Start = 'S',
			Vote = 'V',
			Block = 'B',
			Unblock = 'U',
			Barging = 'b',
			Complete = 'C',
			Finished = 'F' };
		Voter(unsigned int id, TallyVotes &voteTallier, Printer &printer);
};

#endif
