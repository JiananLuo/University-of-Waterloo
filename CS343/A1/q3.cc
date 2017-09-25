#include <iostream>
#include <fstream>
#include <stdlib.h>		/* exit, EXIT_FAILURE */
#include <string>		/* string */
#include "q3stringliteral.h"

using namespace std;

int main(int argc, char *argv[]) {
	istream *input;

	// argument check to determine input from file / cin
	switch (argc) {
		// input from file
		case 2:
			try {
				input = new ifstream(argv[1]);
			} catch(uFile::Failure) {
				cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
			}
			break;
		// input from cin
		case 1:
			input = &cin;
			break;
		// number of argument is incorrect
		default:
			exit(EXIT_FAILURE);
	}

	// the varible to store readin string line by line
	string line;

	// read input line by line
	for (;;) {
		getline (*input,line);

		// create coroutine on stack
		StringLiteral stringLiteral;
		// check for EOF
		if (input->fail()) {
			break;
		}

		// keep format as given executable
		cout << "'" << line << "' : ";
		// append newLine char in the end of string
		line += '\n';
		int lineIndex = 0;
		int lineLength = line.length();
		try {
			_Enable {
			// pass char to coroutine 1 by 1
				for(; lineIndex < lineLength; lineIndex++) {
					stringLiteral.next(line[lineIndex]);
					stringLiteral.resumer();
				}
			}
		} catch (StringLiteral::Match) {
			// increment the index by 1, due to throw
			lineIndex++;
			cout << "' yes";
			// if line haven't finish yet, print the rest
			if (lineIndex < lineLength-1) {
				cout << " -- extraneous characters '" << line.substr(lineIndex, lineLength-lineIndex-1) << "'";
			}
			cout << endl;
		} catch (StringLiteral::Error) {
			// increment the index by 1, due to throw
			lineIndex++;
			cout << "' no";
			// if line haven't finish yet, print the rest
			if (lineIndex < lineLength-1) {
				cout << " -- extraneous characters '" << line.substr(lineIndex, lineLength-lineIndex-1) << "'";
			}
			cout << endl;
		}
	}

	// close file, do not delete cin!
	if (input != &cin) {
		delete input;
	}
}
