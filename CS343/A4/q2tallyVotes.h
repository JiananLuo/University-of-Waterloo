#ifndef __TALLYVOTES__
#define __TALLYVOTES__

_Monitor Printer;

#if defined(IMPLTYPE_MC)
/* mutex/condition solution */
class TallyVotes {
	private:
		uOwnerLock ownerLock;
		uCondLock condLockBlock;
		uCondLock condLockBarging;
		bool isBarging;
		unsigned int waiting;
#elif defined(IMPLTYPE_BAR)
/* barrier solution */
#include <uBarrier.h>
_Cormonitor TallyVotes : public uBarrier {
	private:
		int tour;
		void last();
#elif defined(IMPLTYPE_SEM)
/* semaphore solution */
#include <uSemaphore.h>
class TallyVotes {
	private:
		unsigned int waitings;
		uSemaphore bargingLock;
		uSemaphore syncLock;
#else
	#error unsupported voter type
#endif
	private:
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
};

#endif
