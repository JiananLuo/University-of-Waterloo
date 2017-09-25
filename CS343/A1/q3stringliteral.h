#ifndef __STRINGLITERAL_
#define __STRINGLITERAL_

_Coroutine StringLiteral {
	private:
		char ch;						// simple char stored on this coroutine struct
		void main();					// main for coroutine
		void printCurrChar();			// print the ch to cout
		bool isSimpleEscapeChar();		// return a boolean to check if ch is a simpleEscapeChar or not
		bool isOctalEscapeChar();		// return a boolean to check if ch is a octalEscapeChar or not
		bool isHexEscapeChar();			// return a boolean to check if ch is a hexEscapeChar or not
		void throwMatch();				// handle throw match case
		void throwError();				// handle throw error case
	public:
		_Event Match {};				// last character match
		_Event Error {};				// last character invalid
		void next(char c);				// next function for this coroutine
};

#endif
