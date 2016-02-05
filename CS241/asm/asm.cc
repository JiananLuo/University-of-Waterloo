#include "kind.h"
#include "lexer.h"
#include <vector>
#include <string>
#include <iostream>
// Use only the neeeded aspects of each namespace
#include <sstream>
#include <cstdio>
#include <map>
using std::string;
using std::vector;
using std::endl;
using std::cerr;
using std::cin;
using std::getline;
using ASM::Token;
using ASM::Lexer;

string generalError = "ERROR";
string sizeError = "SIZE ERROR";
string labelError = "LABEL ERROR";
string registerError = "REGISTER ERROR";
string typeError = "TYPE ERROR";
string iOutOfRangeError = "i OUT OF RANGE ERROR";

void checkIRangeINT(int i)
{
	if(i<-32768 || i>32767)
		throw iOutOfRangeError;
}
void checkIRangeHEX(int i)
{
	if(i<0 || i > 65535)
		throw iOutOfRangeError;
}
int rType(int s, int t, int d, int opcode)
{
	return (s << 21) | (t << 16) | (d << 11) | opcode;
}
int iType(int s, int t, int i, int opcode)
{
	if(i < 0)
	{
		if(i == -32768)
		i = 32768;
		else
		{
			i = ~(i & 0xffff) * -1;
			i--;
		}
	}
	return opcode | (s << 21) | (t << 16) | i ;
}
void output_bytes(int n)
{
	putchar((n >> 24) & 0xff);
	putchar((n >> 16) & 0xff);
	putchar((n >> 8) & 0xff);
	putchar((n >> 0) & 0xff);
}

int main(int argc, char* argv[])
{
	// Nested vector representing lines of Tokens
	// Needs to be used here to cleanup in the case
	// of an exception
	vector< vector<Token*> > tokLines;
	try
	{
		// Create a MIPS recognizer to tokenize
		// the input lines
	Lexer lexer;
	// Tokenize each line of the input
	string line;
	while(getline(cin,line))
	{
		tokLines.push_back(lexer.scan(line));
	}

	// Iterate over the lines of tokens and print them
	// to standard error
	std::map<string, int> symbolTable;
	std::map<string, int>::iterator ist;
	vector<vector<Token*> >::iterator it;

	int currentAddress = 0;
	for(it = tokLines.begin(); it != tokLines.end(); it++)//PATH ONE && PATH ONE && PATH ONE && PATH ONE && PATH ONE && PATH ONE
	{
		int numLabelFront = 0;
		vector<Token*>::iterator it2;
		for(it2 = it->begin(); it2 != it->end(); it2++)
		{
			if((*it2)->toString() == "LABEL")
			{
				numLabelFront++;

				string label = (*it2)->getLexeme();
				label = label.substr(0, label.size()-1);
				//cerr << label << endl;
				ist = symbolTable.find(label);
				if (symbolTable.find(label) == symbolTable.end())
				{
					symbolTable[label] = currentAddress;
					//cerr << label << endl;
				}
				else
				{
					throw labelError;
				}
			}
			else if((*it2)->toString() == "DOTWORD")
			{
				currentAddress+=4;
				if(it->size() - numLabelFront != 2)
				{
					throw sizeError;
				}
			}
			else if((*it2)->toString() == "ID")
			{
				currentAddress+=4;
				string instruction = (*it2)->getLexeme();

				if((instruction == "jr") || (instruction == "jalr") || (instruction == "lis") || (instruction == "mfhi") || (instruction == "mflo")) // r type 1 argu
				{
					if(it->size() - numLabelFront != 2)
					{
						throw sizeError;
					}
					*it2++;
					if((*it2)->toString() == "REGISTER")
					{
						int s;
						string sS = (*it2)->getLexeme();
						sS = sS.substr(1, sS.size());
						std::istringstream convertS(sS);
						convertS >> s;
						if(s<0 || s>31)
						{
							throw registerError;
						}
					}
					else
					{
						throw typeError;
					}
				}
				else if((instruction == "mult") || (instruction == "multu") || (instruction == "div") || (instruction == "divu"))//r type 2 argu
				{
					if(it->size() - numLabelFront != 4)
					{
						throw sizeError;
					}

					string sS, tS;
					int s, t;
					
					*it2++;
					if((*it2)->toString() == "REGISTER")
					{
						sS = (*it2)->getLexeme();
						sS = sS.substr(1, sS.size());
						std::istringstream convertS(sS);
						convertS >> s;
						if(s<0 || s>31)
							throw registerError;
					}
					else
						throw typeError;

					*it2++;
					if((*it2)->toString() != "COMMA")
						throw typeError;

					*it2++;
					if((*it2)->toString() == "REGISTER")
					{
						tS = (*it2)->getLexeme();
						tS = tS.substr(1, tS.size());
						std::istringstream convertT(tS);
						convertT >> t;
						if(t<0 || t>31)
							throw registerError;
					}
					else
						throw typeError;
				}
				else if((instruction == "add") || (instruction == "sub") || (instruction == "slt") || (instruction == "sltu"))//r type 3 argu
				{
					if(it->size() - numLabelFront != 6)
					{
						throw sizeError;
					}

					string sS, tS, dS;
					int s, t, d;

					*it2++;
					if((*it2)->toString() == "REGISTER")
					{
						dS = (*it2)->getLexeme();
						dS = dS.substr(1, dS.size());
						std::istringstream convertD(dS);
						convertD >> d;
						if(d<0 || d>31)
							throw registerError;
					}
					else
						throw typeError;

					*it2++;
					if((*it2)->toString() != "COMMA")
						throw typeError;

					*it2++;
					if((*it2)->toString() == "REGISTER")
					{
						sS = (*it2)->getLexeme();
						sS = sS.substr(1, sS.size());
						std::istringstream convertS(sS);
						convertS >> s;
						if(s<0 || s>31)
							throw registerError;
					}
					else
						throw typeError;

					*it2++;
					if((*it2)->toString() != "COMMA")
						throw typeError;

					*it2++;
					if((*it2)->toString() == "REGISTER")
					{
						tS = (*it2)->getLexeme();
						tS = tS.substr(1, tS.size());
						std::istringstream convertT(tS);
						convertT >> t;
						if(t<0 || t>31)
							throw registerError;
					}
					else
						throw typeError;
				}
				else if((instruction == "beq") || (instruction == "bne"))//r type 3 argu
				{
					if(it->size() - numLabelFront != 6)
					{
						throw sizeError;
					}

					string sS, tS, iS;
					int s, t, i;

					*it2++;
					if((*it2)->toString() == "REGISTER")
					{
						sS = (*it2)->getLexeme();
						sS = sS.substr(1, sS.size());
						std::istringstream convertS(sS);
						convertS >> s;
						if(s<0 || s>31)
						throw registerError;
					}
					else
						throw typeError;

					*it2++;
					if((*it2)->toString() != "COMMA")
						throw typeError;

					*it2++;
					if((*it2)->toString() == "REGISTER")
					{
						tS = (*it2)->getLexeme();
						tS = tS.substr(1, tS.size());
						std::istringstream convertT(tS);
						convertT >> t;
						if(t<0 || t>31)
							throw registerError;
					}
					else
						throw typeError;

					*it2++;
					if((*it2)->toString() != "COMMA")
						throw typeError;

					*it2++;
					if((*it2)->toString() == "INT")
					{
						i = (*it2)->toInt();
						checkIRangeINT(i);
						
					}
					else if((*it2)->toString() == "HEXINT")
					{
						i = (*it2)->toInt();
						checkIRangeHEX(i);
					}
					else if((*it2)->toString() == "ID")
					{

					}
					else
						throw typeError;
				}
				else if((instruction == "lw") || (instruction == "sw"))
				{
					if(it->size() - numLabelFront != 7)
					{
						throw sizeError;
					}

					string sS, tS;
					int s, t, i;

					*it2++;
					if((*it2)->toString() == "REGISTER")
					{
						tS = (*it2)->getLexeme();
						tS = tS.substr(1, tS.size());
						std::istringstream convertT(tS);
						convertT >> t;
						if(t<0 || t>31)
							throw registerError;
					}
					else
						throw typeError;

					*it2++;
					if((*it2)->toString() != "COMMA")
						throw typeError;

					*it2++;
					if((*it2)->toString() == "INT")
					{
						i = (*it2)->toInt();
						checkIRangeINT(i);
					}
					else if((*it2)->toString() == "HEXINT")
					{
						i = (*it2)->toInt();
						checkIRangeHEX(i);
					}
					else
						throw typeError;

					*it2++;
					if((*it2)->toString() != "LPAREN")
						throw typeError;

					*it2++;
					if((*it2)->toString() == "REGISTER")
					{
						sS = (*it2)->getLexeme();
						sS = sS.substr(1, sS.size());
						std::istringstream convertS(sS);
						convertS >> s;
						if(s<0 || s>31)
							throw registerError;
					}
					else
						throw typeError;
					
					*it2++;
					if((*it2)->toString() != "RPAREN")
						throw typeError;
				}
				else
				{
					throw generalError;
				}
			}
			else
			{
				throw generalError;
			}
		}
	}


	for(it = tokLines.begin(); it != tokLines.end(); it++)//CHECK LABEL EXIST && CHECK LABEL EXIST && CHECK LABEL EXIST
	{
		vector<Token*>::iterator it2;

		if(it->size() == 0)
		{
			continue;
		}
		else
		{
			for(it2 = it->begin(); it2 != it->end(); ++it2)
			{
				int numLabelFront = 0;
				while((*it2)->toString() == "LABEL")
				{
					*it2++;
					numLabelFront++;
					if(it->size() == numLabelFront)
					{
						break;
					}
				}
				if(it->size() == numLabelFront)
				{
					break;
				}
				
				if((*it2)->toString() == "ID")
				{
					string instruction = (*it2)->getLexeme();
					if(instruction == "beq" || instruction == "bne")
					{
						*it2++;
						*it2++;
						*it2++;
						*it2++;
						*it2++;
						if((*it2)->toString() == "ID")
						{
							string label = (*it2)->getLexeme();
							if (symbolTable.find(label) == symbolTable.end())
							{
								throw labelError;
							}
						}
					}
					else
					{
						break;
					}
				}
			}
		}
	}




	currentAddress = 0;
	for(it = tokLines.begin(); it != tokLines.end(); it++)//PATH TWO && PATH TWO && PATH TWO && PATH TWO && PATH TWO && PATH TWO
	{
		vector<Token*>::iterator it2;

		if(it->size() == 0)
		{
			continue;
		}
		else if(it->size() == 1)
		{
			it2 = it->begin();
			
			if((*it2)->toString() == "DOTWORD")
			{
				throw generalError;
			}
			else
			{
				continue;
			}
		}
		else //if(it->size() >= 2)
		{
			for(it2 = it->begin(); it2 != it->end(); ++it2)
			{
				int numLabelFront = 0;
				while((*it2)->toString() == "LABEL")
				{
					*it2++;
					numLabelFront++;
					if(it->size() == numLabelFront)
					{
						break;
					}
				}
				if(it->size() == numLabelFront)
				{
					break;
				}
				if((*it2)->toString() == "DOTWORD")
				{
					currentAddress+=4;
					*it2++;
					if(((*it2)->toString() == "INT") || (*it2)->toString() == "HEXINT")
					{
						int n = (*it2)->toInt();
						output_bytes(n);
						currentAddress+=4;
					}
					else if((*it2)->toString() == "ID")
					{
						string label = (*it2)->getLexeme();
						if (symbolTable.find(label) == symbolTable.end())
						{
							throw labelError;
						}
						else
						{
							output_bytes(symbolTable[label]);
						}
					}
					else
					{
						throw generalError;
					}
				}
				else if((*it2)->toString() == "ID")
				{
					currentAddress+=4;
					string instruction = (*it2)->getLexeme();
					if((instruction == "jr") || (instruction == "jalr"))
					{
						*it2++;
						int s;
						string sS = (*it2)->getLexeme();
						sS = sS.substr(1, sS.size());
						std::istringstream convertS(sS);
						convertS >> s;

						if(instruction == "jr")
							output_bytes(rType(s, 0, 0, 8));
						else
							output_bytes(rType(s, 0, 0, 9));
						
					}
					else if(instruction == "mfhi"|| instruction == "mflo" || instruction == "lis")
					{
						*it2++;
						int d;
						string dS = (*it2)->getLexeme();
						dS = dS.substr(1, dS.size());
						std::istringstream convertD(dS);
						convertD >> d;

						if(instruction == "mfhi")
						{
							output_bytes(rType(0, 0, d, 16));
						}
						else if(instruction == "mflo")
						{
							output_bytes(rType(0, 0, d, 18));
						}
						else
						{
							output_bytes(rType(0, 0, d, 20));
						}
						
					}
					else if(instruction == "add" || instruction == "sub" || instruction == "slt" || instruction == "sltu")
					{
						string sS, tS, dS;
						int s, t, d;

						*it2++;
						dS = (*it2)->getLexeme();
						*it2++;
						*it2++;
						sS = (*it2)->getLexeme();
						*it2++;
						*it2++;
						tS = (*it2)->getLexeme();

						sS = sS.substr(1, sS.size());
						std::istringstream convertS(sS);
						convertS >> s;
						tS = tS.substr(1, tS.size());
						std::istringstream convertT(tS);
						convertT >> t;
						dS = dS.substr(1, dS.size());
						std::istringstream convertD(dS);
						convertD >> d;

						if(instruction == "add")
						{
							output_bytes(rType(s, t, d, 32));
						}
						else if(instruction == "sub")
						{
							output_bytes(rType(s, t, d, 34));
						}
						else if(instruction == "slt")
						{
							output_bytes(rType(s, t, d, 42));
						}
						else
						{
							output_bytes(rType(s, t, d, 43));
						}
					}
					else if(instruction == "mult" || instruction == "multu" || instruction == "div" || instruction == "divu")
					{
						string sS, tS;
						int s, t;

						*it2++;
						sS = (*it2)->getLexeme();
						*it2++;
						*it2++;
						tS = (*it2)->getLexeme();

						sS = sS.substr(1, sS.size());
						std::istringstream convertS(sS);
						convertS >> s;
						tS = tS.substr(1, tS.size());
						std::istringstream convertT(tS);
						convertT >> t;


						if(instruction == "mult")
						{
							output_bytes(rType(s, t, 0, 24));
						}
						else if(instruction == "multu")
						{
							output_bytes(rType(s, t, 0, 25));
						}
						else if(instruction == "div")
						{
							output_bytes(rType(s, t, 0, 26));
						}
						else
						{
							output_bytes(rType(s, t, 0, 27));
						}
					}
					else if(instruction == "beq" || instruction == "bne")
					{
						string sS, tS, iS;
						int s, t, i;

						*it2++;
						sS = (*it2)->getLexeme();
						*it2++;
						*it2++;
						tS = (*it2)->getLexeme();
						*it2++;
						*it2++;
						if((*it2)->toString() == "INT" || (*it2)->toString() == "HEXINT")
						{
							i = (*it2)->toInt();
						}
						else
						{
							string label = (*it2)->getLexeme();
							i = (symbolTable[label] - currentAddress) / 4;
						}

						sS = sS.substr(1, sS.size());
						std::istringstream convertS(sS);
						convertS >> s;
						tS = tS.substr(1, tS.size());
						std::istringstream convertT(tS);
						convertT >> t;

						if(instruction == "beq")
						{
							output_bytes(iType(s, t, i, 268435456));
						}
						else
						{
							output_bytes(iType(s, t, i, 335544320));
						}
					}
					else if(instruction == "sw" || instruction == "lw")
					{
						string sS, tS;
						int s, t, i;

						*it2++;
						tS = (*it2)->getLexeme();
						*it2++;
						*it2++;
						i = (*it2)->toInt();
						*it2++;
						*it2++;
						sS = (*it2)->getLexeme();
						*it2++;

						sS = sS.substr(1, sS.size());
						std::istringstream convertS(sS);
						convertS >> s;
						tS = tS.substr(1, tS.size());
						std::istringstream convertT(tS);
						convertT >> t;

						if(instruction == "lw")
						{
							output_bytes(iType(s, t, i, 2348810240));
						}
						else
						{
							output_bytes(iType(s, t, i, 2885681152));
						}
					}
					else
					{
						throw generalError;
					}
				}
			}
		}
	}

	for(ist = symbolTable.begin(); ist != symbolTable.end(); ist++)//PRINTSYMBOLTABLE && PRINTSYMBOLTABLE && PRINTSYMBOLTABLE && PRINTSYMBOLTABLE
	{
		cerr << ist->first << " " << ist->second << endl;
	}

  } catch(const string& msg){
    // If an exception occurs print the message and end the program
    cerr << msg << endl;
  }
  // Delete the Tokens that have been made
  vector<vector<Token*> >::iterator it;
  for(it = tokLines.begin(); it != tokLines.end(); ++it){
    vector<Token*>::iterator it2;
    for(it2 = it->begin(); it2 != it->end(); ++it2){
      delete *it2;
    }
  }
}

