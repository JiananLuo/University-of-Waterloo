#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int times = 1000;
int rtnStatus = -1;

void rtn1(int i) {
	for (int j = 0; j < times; j += 1) {
		if (rand() % 10000 == 42) {
			rtnStatus = j;
			return;
		}
	}
}

void rtn2(int i) {
	for (int j = times; j >= 0; j -= 1) {
		if (rand() % 10000 == 42) {
			rtnStatus = j;
			return;
		}
	}
}

void g(int i) {
	for (int j = 0; j < times; j += 1) {
		if (rand() % 2 == 0) {
			rtn1(i);
			if(rtnStatus != -1) {
				return;
			}
		} else {
			rtn2(i);
			if(rtnStatus != -1) {
				return;
			}
		}
	}
	if (i % 2) {
		rtn2(i);
		if(rtnStatus != -1) {
			return;
		}
	}
	rtn1(i);
}

void f(int i) {
	for (int j = 0; j < times; j += 1) {
		g(i);
		if(rtnStatus != -1) {
			return;
		}
	}
	if (i % 2) {
		g(i);
		if(rtnStatus != -1) {
			return;
		}
	}
	g(i);
}

int main(int argc, char *argv[]) {
	int seed = getpid();
	try {
		switch (argc) {
			case 3: times = stoi(argv[2]); if (times <= 0) throw 1;
			case 2: seed = stoi(argv[1]); if (seed <= 0) throw 1;
			case 1: break;
			default: throw 1;
		}
	} catch(...) {
		cout << "Usage: " << argv[0] << " [ seed (> 0) [ times (> 0) ] ]" << endl;
		exit(1);
	}
	srand(seed);
	f(3);
	if(rtnStatus == -1) {
		cout << "seed:" << seed << " times:" << times << " complete" << endl;
	} else {
		cout << "seed:" << seed << " times:" << times << " rc:" << rtnStatus << endl;
	}
}
