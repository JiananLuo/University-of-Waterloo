#include <iostream>
#include <stdlib.h>

#include "MPRNG.h"
#include "q3printer.h"
#include "q3tallyVotes.h"
#include "q3voter.h"

using namespace std;

MPRNG mprng;

void usage(char * argv0) {
	cerr << "Usage: " << argv0 << "  Voters (> 0 & V mod G = 0, default 6)  Group (> 0, default 3)  Seed (> 0)" << endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	// default value for V G and seed
	int V = 6;
	int G = 3;
	mprng.set_seed(getpid());

	// argument check
	if(argc == 4) {
		if(atoi(argv[3]) <=0) usage(argv[0]);
		mprng.set_seed(atoi(argv[3]));
		if(atoi(argv[2]) <= 0) usage(argv[0]);
		G = atoi(argv[2]);
		if(atoi(argv[1]) <= 0) usage(argv[0]);
		V = atoi(argv[1]);
	} else if(argc != 1) {
		usage(argv[0]);
	}

	// init printer && tallyVotes && voters
	Printer printer(V);
	TallyVotes tallyVotes(G, printer);
	Voter *voters[V];
	for(int i=0; i<V; i++) {
		voters[i] = new Voter(i, tallyVotes, printer);
	}

	// clear all
	for(int i=0; i<V; i++) {
		delete voters[i];
	}
}
