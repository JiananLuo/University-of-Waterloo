#ifndef __TALLYVOTES__
#define __TALLYVOTES__

_Monitor Printer;

#if defined(IMPLTYPE_EXT)
/* external scheduling monitor solution */
_Monitor TallyVotes {
#elif defined(IMPLTYPE_INT)
/* internal scheduling monitor solution */
_Monitor TallyVotes {
	private:
		uCondition bench;
#elif defined(IMPLTYPE_INTB)
/* internal scheduling monitor solution with barging */
_Monitor TallyVotes {
	private:
		// ticket & serving counter
		unsigned int tickets, serving;
		// only one condition variable (you may change the variable name)
		uCondition bench;
		// barging version of wait
		void wait();
		// unblock all waiting tasks
		void signalAll();
#elif defined(IMPLTYPE_AUTO)
/* automatic-signal monitor solution */
#include "AutomaticSignal.h"
_Monitor TallyVotes {
	private:
		AUTOMATIC_SIGNAL;
		bool groupFilled;
#elif defined(IMPLTYPE_TASK)
/* internal/external scheduling task solution */
_Task TallyVotes {
	private:
		uCondition bench;
		int tour;
		void main();
#else
	#error unsupported voter type
#endif
	private:
		unsigned waitings;
		unsigned int group;
		Printer &printer;
		int totalGiftshop;
		int totalPicture;
		int totalStatue;
	public:
		TallyVotes(unsigned int group, Printer & printer);
		struct Ballot {
			unsigned int picture, statue, giftshop;
		};
		enum Tour {
			Picture = 'p',
			Statue = 's',
			GiftShop = 'g',
			None = 'n'
		};
		Tour vote(unsigned int id, Ballot ballot);
#if defined(IMPLTYPE_TASK)
	private:
		unsigned id;
		Ballot ballot;
#endif
};

#endif

