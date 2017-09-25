#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int times = 1000;

int rtn1(int i) {
	int rtnStatus = -1;
	for(int j = 0; j < times; j += 1) {
		if(rtnStatus == -1 && rand() % 10000 == 42) {
			rtnStatus = j;
		}
	}
	return rtnStatus;
}

int rtn2(int i) {
	int rtnStatus = -1;
	for(int j = times; j >= 0; j -= 1) {
		if(rtnStatus == -1 && rand() % 10000 == 42) {
			rtnStatus = j;
		}
	}
	return rtnStatus;
}

int g(int i) {
	int rtnStatus = -1;
	for(int j = 0; j < times; j += 1) {
		if(rtnStatus == -1) {
			if(rand() % 2 == 0) {
				rtnStatus = rtn1(i);
			} else {
				rtnStatus = rtn2(i);
			}
		}
	}
	if(rtnStatus == -1 && i % 2) {
		rtnStatus = rtn2(i);
	}
	if(rtnStatus == -1) {
		rtnStatus = rtn1(i);
	}
	return rtnStatus;
}

int f(int i) {
	int rtnStatus = -1;
	for(int j = 0; j < times; j += 1) {
		if(rtnStatus == -1) {
			rtnStatus = g(i);
		}
	}
	if(rtnStatus == -1 && i % 2) {
		rtnStatus = g(i);
	}
	if(rtnStatus == -1) {
		rtnStatus = g(i);
	}
	return rtnStatus;
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
	int rtnStatus = -1;
	rtnStatus = f(3);
	if(rtnStatus == -1) {
		cout << "seed:" << seed << " times:" << times << " complete" << endl;
	} else {
		cout << "seed:" << seed << " times:" << times << " rc:" << rtnStatus << endl;
	}
}
