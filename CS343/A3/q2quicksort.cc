#include <iostream>
#include <fstream>
#include <stdlib.h>		/* exit, EXIT_FAILURE */
#include "q2quicksort.h"

using namespace std;

/**
 * swap 2 elements
 */
template<typename T> void Quicksort<T>::swap(TYPE* a, TYPE* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/**
 * start quick loop
 */
template <typename T> void Quicksort<T>::quickSort()
{
	unsigned int currentLow = this->low;
	unsigned int currentHigh = this->high;

	// valid check
	if((int) currentLow >= (int)currentHigh) {
		return;
	}

	// partition
	int pivot = values[low + ( high - low ) / 2];
	while((int)currentLow <= (int)currentHigh) {
		while(values[currentLow] < pivot) {
			currentLow++;
		}
		while(values[currentHigh] > pivot) {
			currentHigh--;
		}
		if((int)currentLow <= (int)currentHigh) {
			swap(&values[currentLow], &values[currentHigh]);
			currentLow++;
			currentHigh--;
		}
	}

	if(depth == 0) {
		// mode -s && mode -t base case
		int tempLow = this->low;
		int tempHigh = this->high;
		if((int)tempLow < (int)currentHigh) {
			this->low = tempLow;
			this->high = currentHigh;
			quickSort();
		}
		if((int)currentLow < (int)tempHigh) {
			this->low = currentLow;
			this->high = tempHigh;
			quickSort();
		}
	} else {
		// mode -t
		if(this->low < currentHigh) {
			Quicksort<TYPE> node(values, this->low, currentHigh, depth-1);
		}
		if(this->high > currentLow) {
			Quicksort<TYPE> node(values, currentLow, this->high, depth-1);
		}
	}
}

/**
 * coroutine main function
 */
template <typename T> void Quicksort<T>::main() {
	quickSort();
}

void printArray(TYPE values[], int size, ostream *outfile) {
	for (int i=0; i < size; i++) {
		if(i != 0 && i%22 == 0) {
			*outfile << endl << "  ";
		}

		*outfile << values[i];
		if(i != size-1 && (i+1)%22 != 0) {
			*outfile << " ";
		}
	}
	*outfile << endl;
}

unsigned int uDefaultStackSize() {
	// set task stack-size to 512K
	return 512 * 1000;
}

/**
 * Usage function mean to cerr print when input para are wrong
 */
void usage(char * argv0) {
	cerr << "Usage: " << argv0 << " ( -s unsorted-file [ sorted-file ] | -t size (>= 0) [ depth (>= 0) ] )" << endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

	istream *input = &cin;
	ostream *outfile = &cout;

	// argument check to determine good/bad input
	string commandOption;
	int size = 0;
	int depth = 0;
	if(2 < argc && argc < 5) {
		commandOption = argv[1];
		if(commandOption == "-s") {
			try {
				input = new ifstream(argv[2]);
			} catch(uFile::Failure) {
				cerr << "Error! Could not open input file \"" << argv[2] << "\"" << endl;
			}
		} else if(commandOption == "-t") {
			size = atoi(argv[2]);
			if(argc == 4) depth = atoi(argv[3]);
			if(size < 0 || depth < 0) usage(argv[0]);
			#ifdef __U_MULTI__
				uProcessor p[ (1 << depth) - 1 ] __attribute__(( unused )); // 2^depth-1 kernel threads
			#endif
		} else {
			usage(argv[0]);
		}
	} else {
		usage(argv[0]);
	}

	// original unsorted array
	TYPE * unsortedArray;
	if(commandOption == "-t") {
		// mode -t
		unsortedArray = new TYPE[size];
		for(int i = size; i > 0; i--) {
			unsortedArray[size-i] = i;
		}
		// if array is not empty, call coroutine to sort it
		if(size != 0) {
			{
				Quicksort<TYPE> node(unsortedArray, 0, size-1, depth);
			}
		}
		// delete the unsorted array allocated on heap
		delete []unsortedArray;
	} else {
		// mode -s
		int arrayLength;
		while (*input >> arrayLength) {
			// keep reading elements into unsorted array
			unsortedArray = new TYPE[arrayLength];
			int val;
			for (int i=0; i<arrayLength; i++) {
				*input >> val;
				unsortedArray[i] = val;
			}
			// print the unsorted array
			printArray(unsortedArray, arrayLength, outfile);
			// if array is not empty, call coroutine to sort it
			if(arrayLength != 0) {
				{
					Quicksort<TYPE> node(unsortedArray, 0, arrayLength-1, depth);
				}
				// print the sorted array
				printArray(unsortedArray, arrayLength, outfile);
			} else {
				*outfile << endl;
			}

			*outfile << endl;
			// delete the array allocated on heap
			delete []unsortedArray;
		}
		// delete the input file
		delete input;
	}
	// delete the output file
	if (outfile != &cout) delete outfile;
}
