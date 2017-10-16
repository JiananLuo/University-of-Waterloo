#include <iostream>
#include <fstream>
#include <stdlib.h>		/* exit, EXIT_FAILURE */
#include "q1binsertsort.h"

using namespace std;

template <typename T> void Binsertsort<T>::main() {
	// put value in this new node
	T pivot = value;
	// construct 2 new child nodes given val as Sentinel indicate empty node
	Binsertsort<T> left(Sentinel);
	Binsertsort<T> right(Sentinel);
	suspend();

	// find where to put val
	for(;;) {
		if (value == SENTINEL) {
			// input EOF, notify child node EOF should do retrieve now
			left.sort(SENTINEL);
			right.sort(SENTINEL);
			break;
		} else if (pivot == SENTINEL) {
			// empty node, leave value here
		} else if (value < pivot) {
			// go left
			left.sort(value);
		} else {
			// value >= pivot, go right
			right.sort(value);
		}
		suspend();
	}
	suspend();

	// retrieve left
	for(;;) {
		// get retrieve value for left side of tree
		T rtn = left.retrieve();
		if (rtn == SENTINEL) {
			// if left is empty, retrieve this node
			break;
		} else {
			// if not pass this value to upper node
			value = rtn;
			suspend();
		}
	}

	// retrieve this node
	value = pivot;
	suspend();

	// retrieve right
	for(;;) {
		T rtn = right.retrieve();
		if (rtn == SENTINEL) {
			// if right is empty, this node is empty too, pass SENTINEL to upper node
			value = SENTINEL;
			break;
		} else {
			// if not pass this value to upper node
			value = rtn;
			suspend();
		}
	}
}

int main(int argc, char *argv[]) {
	istream *input;
	ostream *outfile = &cout;

	// argument check to determine input to output file / standard output
	switch (argc) {
		// input from input file && output to output file
		case 3:
			try {
				input = new ifstream(argv[1]);
			} catch(uFile::Failure) {
				cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
			}
			try {
				outfile = new ofstream(argv[2]);
			} catch(uFile::Failure) {
				cerr << "Error! Could not write to output file \"" << argv[2] << "\"" << endl;
			}
			break;
		// input from input file && output to standard output
		case 2:
			try {
				input = new ifstream(argv[1]);
			} catch(uFile::Failure) {
				cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
			}
			break;
		// number of argument is incorrect
		default:
			exit(EXIT_FAILURE);
	}

	// read int as number of nodes in the input file
	int numOfNodes;
	// read input line by line
	while (*input >> numOfNodes) {

		// create the root of the bst
		Binsertsort<TYPE> bst(SENTINEL);

		// read # of input equals to numOfNodes && construct the tree
		int nodeVal;
		for (int i=0; i<numOfNodes; i++) {
			*input >> nodeVal;
			*outfile << nodeVal;
			bst.sort(nodeVal);
			if(i != numOfNodes-1) {
				*outfile << " ";
			}
		}
		*outfile << endl;
		// tell the tree reach EOF
		bst.sort(SENTINEL);

		// start to retrieve this tree
		for(int i=0; i<numOfNodes; i++) {
			*outfile << bst.retrieve();
			if (i != numOfNodes-1) {
				*outfile << " ";
			}
		}
		*outfile << endl << endl;
	}

	// close file
	delete input;
	if (outfile != &cout) delete outfile;
}
