#ifndef __PRINTER__
#define __PRINTER__

#include "q2voter.h"

class PrinterInfo {
	public:
		Voter::States state;
		TallyVotes::Tour tour;
		TallyVotes::Ballot ballot;
		unsigned int numBlocked;
	public:
		PrinterInfo(Voter::States state, TallyVotes::Tour tour, TallyVotes::Ballot ballot, unsigned int numBlocked) :
			state(state), tour(tour), ballot(ballot), numBlocked(numBlocked) {}
};

_Monitor Printer {
	private:
		unsigned int voters;
		PrinterInfo **printerInfo;
		void printAllInfo();
	public:
		Printer(unsigned int voters);
		~Printer();
		void print(unsigned int id, Voter::States state);
		void print(unsigned int id, Voter::States state, TallyVotes::Tour tour);
		void print(unsigned int id, Voter::States state, TallyVotes::Ballot ballot);
		void print(unsigned int id, Voter::States state, unsigned int numBlocked);
};

#endif
