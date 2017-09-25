#include <iostream>
#include "q3stringliteral.h"

using namespace std;

void StringLiteral::main() {
	// check if the input line is a empty line
	if (ch == '\n') {
		cout << "Warning! Blank line." << endl;
		return;
	}
	cout << "'";

	// check encoding-prefix-opt
	if (ch == 'u') {
		printCurrChar();
		suspend();
		// check for u8
		if(ch == '8') {
			printCurrChar();
			suspend();
		}
	} else if (ch == 'U' || ch == 'L' || ch == '\n') {
		printCurrChar();
		suspend();
	}

	// if first check of line is not ", it should be error
	if(ch != '"') {
		throwError();
	}
	// otherwise it should pass
	else {
		printCurrChar();
		suspend();
	}

	// string-literal loop
	for(;;) {
		// see the second " in input line, Match handling
		if (ch == '"') {
			throwMatch();
		}
		// theres no second " in input line, Error handling
		else if (ch == '\n') {
			throwError();
		}
		// escape-sequence handling
		else if (ch == '\\') {
			printCurrChar();
			suspend();
			// simple-escape-sequence handling
			if (isSimpleEscapeChar()) {
				printCurrChar();
				suspend();
			}
			// octal-escape-sequence handling
			else if (isOctalEscapeChar()) {
				printCurrChar();
				suspend();
				for(;;) {
					// keep checking octal-escape-sequence handling
					if (isOctalEscapeChar()) {
						printCurrChar();
						suspend();
					} else {
						break;
					}
				}
				continue;
			}
			// hexadecimal-escape-sequence handling
			else if (ch == 'x') {
				printCurrChar();
				suspend();
				// handling for first digit in hexadecimal-escape-sequence
				if(isHexEscapeChar()) {
					for(;;) {
						// keep checking hexadecimal-escape-sequence handling
						if (isHexEscapeChar()) {
							printCurrChar();
							suspend();
						} else {
							break;
						}
					}
				}
				// if first digit right after \x is not hexadecimal-escape-sequence, it should be error
				else {
					throwError();
				}
				continue;
			}
			// if char after \ is not (simple-escape-sequence || octal-escape-sequence || hexadecimal-escape-sequence), it should be error
			else {
				throwError();
			}
		}
		// normal schar handling
		else {
			printCurrChar();
			suspend();
		}
	}
}

/**
 * following methods description are in q3stringliteral.h
 */

void StringLiteral::printCurrChar() {
	cout << ch;
}

bool StringLiteral::isSimpleEscapeChar() {
	return (ch == '\'' || ch == '"' || ch == '?' || ch == '\\' || ch == 'a' || ch == 'b' || ch == 'f' ||
			ch == 'n' || ch == 'r' || ch == 't' || ch == 'v');
}

bool StringLiteral::isOctalEscapeChar() {
	return (ch >= '0' && ch <= '7');
}

bool StringLiteral::isHexEscapeChar() {
	return ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'));
}

void StringLiteral::throwMatch() {
	printCurrChar();
	_Resume Match() _At resumer();
	suspend();
}

void StringLiteral::throwError() {
	if(ch != '\n') {
		printCurrChar();
	}
	_Resume Error() _At resumer();
	suspend();
}

void StringLiteral::next(char c) {
	ch = c;
	resume();
}
