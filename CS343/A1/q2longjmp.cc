#include <iostream>
#include <cstdlib>
#include <unistd.h>	 
#include <setjmp.h>
#include <cstring>

using namespace std;

#ifdef NOOUTPUT
    #define PRT(stmt)
#else
    #define PRT(stmt) stmt
#endif

jmp_buf globalJmpBuf;

PRT(struct T { ~T() { cout << "~"; } };)

struct E {};
long int freq = 5;

long int Ackermann(long int m, long int n) {
	jmp_buf lastStackJmpBuf;
	memcpy(lastStackJmpBuf, globalJmpBuf, sizeof(jmp_buf));

	PRT(T t;)
	if (m == 0) {
		if (rand() % freq == 0) {
			longjmp(globalJmpBuf, 1);
		}
		return n + 1;
	} else if (n == 0) {
		if (setjmp(globalJmpBuf) == 0) {
			int result = Ackermann(m - 1, 1);
			memcpy(globalJmpBuf, lastStackJmpBuf, sizeof(jmp_buf));
			return result;
		} else {
			memcpy(globalJmpBuf, lastStackJmpBuf, sizeof(jmp_buf));
			PRT(cout << "E1 " << m << " " << n << endl);
			if (rand() % freq == 0) {
				longjmp(globalJmpBuf, 1);
			}
		}
	} else {
		if (setjmp(globalJmpBuf) == 0) {
			int result = Ackermann(m - 1, Ackermann(m, n - 1));
			memcpy(globalJmpBuf, lastStackJmpBuf, sizeof(jmp_buf));
			return result;
		} else {
			PRT(cout << "E2 " << m << " " << n << endl);
			memcpy(globalJmpBuf, lastStackJmpBuf, sizeof(jmp_buf));
		}
	}
	return 0;
}
int main(int argc, const char *argv[]) {
	long int Ackermann(long int m, long int n);
	long int m = 4, n = 6, seed = getpid();
	try {
		switch (argc) {
			case 5: freq = stoi(argv[4]); if (freq <= 0) throw 1;
			case 4: seed = stoi(argv[3]); if (seed <= 0) throw 1;
			case 3: n = stoi(argv[2]); if (n < 0) throw 1;
			case 2: m = stoi(argv[1]); if (m < 0) throw 1;
			case 1: break;
			default: throw 1;
		}
	} catch(...) {
		cout << "Usage: " << argv[0] << " [ m (> 0) [ n (> 0) [ seed (> 0)"
			" [ freq (> 0) ] ] ] ]" << endl;
		exit(1);
	}
	srand(seed);
	if (setjmp(globalJmpBuf) == 0) {
		PRT(cout << m << " " << n << " " << seed << " " << freq << endl);
		long int val = Ackermann(m, n);
		PRT(cout << val << endl);
	} else {
		PRT(cout << "E3" << endl);
	}
}

