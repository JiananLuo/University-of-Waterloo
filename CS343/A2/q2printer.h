#ifndef __PRINTER__
#define __PRINTER__

class PrinterInfo {
	public:
		int deckTake;
		int deckLeft;
		int playerLeft;
	public:
		PrinterInfo() : deckTake(0), deckLeft(0), playerLeft(0) {}
};

class Printer {
	private:
		int totalPlayers;
		int numOfCardsLeft;
		PrinterInfo *printerInfo;
		void printAllInfo();
	public:
		Printer(const unsigned int NoOfPlayers, const unsigned int NoOfCards);
		~Printer();
		void prt(unsigned int id, int took, int RemainingPlayers);
};

#endif
