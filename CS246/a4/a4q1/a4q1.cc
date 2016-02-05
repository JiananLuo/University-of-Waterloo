#include "Expression.h"
#include "LoneInt.h"
#include "Unary.h"
#include "Binary.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int MAX = 10;//max expression can be held

/********** Main **********
     Purpose: Main function
     Returns: Nothing
     Error: None
************************************/
int main()
{
	Expression *expAry[MAX];
	for(int i=0; i<MAX; i++)
	{
		expAry[i] = NULL;
	}

	int numExp = 0;

	string s;
	int n;
	while(cin >> s)
	{
		stringstream ss(s);
		
		if(s == "ABS")//case ABS
		{
			expAry[numExp-1] = new Unary('a', expAry[numExp-1]);
		}
		else if(s == "NEG")//case NEG
		{
			expAry[numExp-1] = new Unary('n', expAry[numExp-1]);
		}
		else if(s == "+") //case +
		{
			if(numExp < 2)
				break;
			Binary *b = new Binary('+', expAry[numExp-2], expAry[numExp-1]);
			expAry[numExp-1] = NULL;
			numExp--;
			expAry[numExp-1] = b;
		}
		else if(s == "-") //case -
		{
			if(numExp < 2)
				break;
			Binary *b = new Binary('-', expAry[numExp-2], expAry[numExp-1]);
			expAry[numExp-1] = NULL;
			numExp--;
			expAry[numExp-1] = b;
		}
		else if(s == "*") //case *
		{
			if(numExp < 2)
				break;
			Binary *b = new Binary('*', expAry[numExp-2], expAry[numExp-1]);
			expAry[numExp-1] = NULL;
			numExp--;
			expAry[numExp-1] = b;
		}
		else if(s == "/") //case /
		{
			if(numExp < 2)
				break;
			Binary *b = new Binary('/', expAry[numExp-2], expAry[numExp-1]);
			expAry[numExp-1] = NULL;
			numExp--;
			expAry[numExp-1] = b;
		}
		else if(ss >> n)//case number
		{
			numExp++;
			if(numExp<=MAX)
			{
				LoneInt *l = new LoneInt(n);
				expAry[numExp-1] = l;
			}
			else
			{
				cerr << "Stack overflow" << endl;
				return -1;
			}
		}
		else
		{
			cin.ignore();
		}
	}
	if(numExp != 0)//print
	{
		expAry[0]->prettyprint();
		cout << endl;
		cout << "= " << expAry[0]->evalute() << endl;
	}
	for(int i=0; i<MAX; i++)
		delete expAry[i];
}
