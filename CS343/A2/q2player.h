#ifndef __PLAYER__
#define __PLAYER__

class Printer;

_Coroutine Player {
	private:
		static unsigned int numOfPlayers;
		Printer &printer;
		int id;
		Player *lp, *rp;
		unsigned int deck;
		_Event Schmilblick {};
		void main();
	public:
		enum { DEATH_DECK_DIVISOR = 7 };
		static void players(unsigned int num);
		Player(Printer &printer, unsigned int id);
		void start(Player &lp, Player &rp);
		void play(unsigned int deck);
		void drink();
};

#endif
