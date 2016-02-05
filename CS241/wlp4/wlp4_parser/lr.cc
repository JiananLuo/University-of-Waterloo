#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

map<int, string> rules;
map<string, string> trans;

vector<string> stack;
vector<string> stateStack;
vector<string> trace;

string currentInput;

int counter;


//Skip the grammar part of the input.
void skipLine(istream &in) {
	string s;
	getline(in, s);
}

void readRule()
{
	// read the number of rules and move to the next line
	int numRules;
	cin >> numRules;
	skipLine(cin);

	// store the production rules
	string rule;
	for(int i = 0; i < numRules; i++)
	{
		getline(cin, rule);
		rules[i] = rule;
	}
}

void readTrans()
{
	int a, b;
	cin >> a >> b;

	string n, x, action1, action2;
	string key, value;

	for(int i=0; i<b; i++)
	{
		cin >> n >> x >> action1 >> action2;
		key = n + " " + x;
		value = action1 + " " + action2;
		trans[key] = value;
	}
}

void readStack()
{
	// skip the line containing the start symbol
	string startState;
	cin >> startState;
	stack.push_back(startState);
	stateStack.push_back("0");
	skipLine(cin);
}

string predict()
{
	string n = stateStack.back();
	string key = n + " " + stack.back();
	if ( trans.find(key) == trans.end() )
	{
		throw counter;
	}
	else //shift
	{
		string action = trans[key];
		string newStateStack = action.substr(6, action.size());
		return newStateStack;
	}
}

void getAction()
{	

	while(cin)
	{
		string n = stateStack.back();
		string key = n + " " + currentInput;
		if ( trans.find(key) == trans.end() )
		{
			throw counter;
		}
		else
		{
			string action = trans[key];
			if(action[0] == 'r')//reduce
			{
				action = action.substr(7, action.size());
				int numb;
				istringstream ( action ) >> numb;
				action = rules[numb]; //print rule
				trace.push_back(action);

				istringstream ss(action);
				string replace, temp;
				ss >> replace;
				int ssSize = 0;
				while(ss >> temp)
				{
					ssSize++;
				}
				while(ssSize != 0)
				{
					stateStack.pop_back();
					stack.pop_back();
					ssSize--;
				}
				stack.push_back(replace);
				stateStack.push_back(predict());
			}
			else //shift
			{
				string newStateStack = action.substr(6, action.size());
				stateStack.push_back(newStateStack);
				stack.push_back(currentInput);
				//cout << "wocao: " << currentInput << endl;
				counter++;
				cin >> currentInput;
			}
		}
	}
	
}



void skipGrammar(istream &in)
{
	int i, numTerm, numNonTerm;

	// read the number of terminals and move to the next line
	in >> numTerm;
	skipLine(in);
	
	// skip the lines containing the terminals
	for (i = 0; i < numTerm; i++) {
		skipLine(in);
	}
	
	// read the number of non-terminals and move to the next line
	in >> numNonTerm;
	skipLine(in);
	
	// skip the lines containing the non-terminals
	for (i = 0; i < numNonTerm; i++) {
		skipLine(in);
	}
	
}

void printTrace()
{
	
	for(vector<string>::const_iterator i = trace.begin(); i != trace.end(); ++i)
	{
		cout << *i << endl;
	}

	for(vector<string>::const_iterator i = stack.begin(); i != stack.end();)
	{
		cout << *i;
		++i;
		if(i != stack.end())
			cout << " ";
	}
	cout << endl;
}

// Reads a .cfg file and prints the left-canonical
// derivation without leading or trailing spaces.
int main()
{
	string line;
	skipGrammar(cin);

	readStack();
	readRule();
	readTrans();

	cin >> currentInput;
	try
	{
		getAction();
		printTrace();
	}
	catch(int error)
	{
		error++;
		cerr << "ERROR at " << error << endl;
	}
}

