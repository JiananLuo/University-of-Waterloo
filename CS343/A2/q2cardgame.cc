#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "q2printer.h"
#include "q2player.h"
#include "PRNG.h"

using namespace std;

PRNG prng;
unsigned int Player::numOfPlayers = 0;

void usage(char * argv0) {
	cerr << "Usage: " << argv0 << " [ games (>= 0) | \"x\" [ players (>= 2) | \"x\" [ cards (> 0) | \"x\" [ random-seed (> 0) | \"x\" ] ] ] ]" << endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) 
{
	int nGames, nPlayers, nCards;

	// check args failure
	if(argc > 5) {
		usage(argv[0]);
	}

	// init prng
	if(argc > 4 && *argv[4] != 'x') {
		if(atoi(argv[4]) <=0) {
			usage(argv[0]);
		}
		prng = PRNG(atoi(argv[4]));
	} else {
		prng = PRNG(getpid());
	}

	// init nGames
	if(argc >1 && *argv[1] != 'x') {
		nGames = atoi(argv[1]);
	} else {
		nGames = 5;
	}

	// when games = 0, check rest args
	if(nGames <= 0) {
		if(argc > 2 && *argv[2] != 'x') {
			nPlayers = atoi(argv[2]);
		} else {
			nPlayers = prng(2, 10);
		}
		if(argc > 3 && *argv[3] != 'x') {
			nCards = atoi(argv[3]);
		} else {
			nCards = prng(10, 200);
		}
		if(nGames<0 || nPlayers<2 || nCards<=0 || prng.seed()<=0) {
			usage(argv[0]);
		}
	}

	// game loops
	for(int iGame = 0; iGame < nGames; iGame++) {
		// init playerList
		if(argc > 2 && *argv[2] != 'x') {
			nPlayers = atoi(argv[2]);
		} else {
			nPlayers = prng(2, 10);
		}
		Player::players(nPlayers);
		Player *playerList[nPlayers];

		// init nCards
		if(argc > 3 && *argv[3] != 'x') {
			nCards = atoi(argv[3]);
		} else {
			nCards = prng(10, 200);
		}

		// incorrect args
		if(nGames<0 || nPlayers<2 || nCards<=0 || prng.seed()<=0) {
			usage(argv[0]);
		}
		// init printer
		Printer printer(nPlayers, nCards);

		// init all Players
		cout << "Players: " << nPlayers << "    Cards: " << nCards << endl;
		for(int playerIndex = 0; playerIndex < nPlayers; playerIndex++) {
			playerList[playerIndex] = new Player(printer, playerIndex);

			cout << "P" << playerIndex;
			if(playerIndex != nPlayers-1) {
				cout << '\t';
			}
		}
		cout << endl;

		// create link to players right & left
		for(int playerIndex = 0; playerIndex < nPlayers; playerIndex++) {
			int left = playerIndex - 1;
			if(left == -1) {
				left = nPlayers-1;
			}
			int right = playerIndex + 1;
			if(right == nPlayers) {
				right = 0;
			}
			playerList[playerIndex]->start(*playerList[left], *playerList[right]);
		}

		// check whos first
		int startPlayer = prng(1, nPlayers) - 1;

		// start to play
		playerList[startPlayer]->play(nCards);

		// iGame end delete all Players
		for(int playerIndex = 0; playerIndex < nPlayers; playerIndex++) {
			delete playerList[playerIndex];
		}

		// if not last iGame, print new lines
		if(iGame != nGames-1) {
			cout << endl << endl;
		}
	}
}
