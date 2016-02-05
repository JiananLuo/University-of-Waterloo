#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

string terminal[] = {"BOF", "BECOMES", "COMMA", "ELSE", "EOF", "EQ", "GE", "GT", "ID", "IF", "INT", "LBRACE", "LE", "LPAREN", "LT", "MINUS", "NE", "NUM", "PCT", "PLUS", "PRINTLN", "RBRACE", "RETURN", "RPAREN", "SEMI", "SLASH", "STAR", "WAIN", "WHILE", "AMP", "LBRACK", "RBRACK", "NEW", "DELETE", "NULL"};
map<string, vector<string> > parameterTable;
map<string, map<string, string> > symbolTable;
string currentScope;

string errorDuplicate = "duplicate error! ";
string errorUndefined = "undefined error! ";
string errorType = "type error! ";
string errorReturnType = "return type error! ";
string errorParameter = "parameter error! ";
string errorWellType = "not well type! ";

map<string, map<string, int> > symbolAddress;
int currentWhile = 0;
int currentIf = 0;

struct Tree
{
	string rule;
	vector <string> token;
	vector <Tree *> child;
};

bool isTerminal(string name)
{
	for(int i=0; i<35; i++)
	{
		if(name == terminal[i])
			return true;
	}
	return false;
}

Tree * readTree()
{
	Tree * newTree = new Tree;
	
	getline(cin, newTree->rule);
	stringstream ss;
	ss.str(newTree->rule);
	
	string temp;
	while(ss >> temp)
	{
		newTree->token.push_back(temp);
	}
	
	if(!isTerminal(newTree->token[0]))
	{
		for(int i=0; i< newTree->token.size()-1; i++)
		{
			newTree->child.push_back(readTree());
		}
	}
	return newTree;
}

void printTree(Tree *t)
{
	for(vector<Tree *>::iterator it = t->child.begin(); it != t->child.end(); it++)
	{
		printTree(*it);
	}
	cout << t->rule << endl;
}

void checkSymbol(string name)
{
	map<string,string>::iterator it;
	it = symbolTable[currentScope].find(name);
	if(it == symbolTable[currentScope].end())
	{
		throw errorUndefined + name + " can not be found in symbolTable: " + currentScope;
	}
}

void addSymbol(Tree *t)
{
	string type, id;
	if(t->child[0]->token.size() == 2)
	{
		type = "int";
	}
	else
	{
		type = "int*";
	}
	id = t->child[1]->token[1];
	
	map<string,string>::iterator it;
	it = symbolTable[currentScope].find(id);
	if(it != symbolTable[currentScope].end())
	{
		throw errorDuplicate;
	}
	
	symbolTable[currentScope][id] = type;
}

void addParameterMain(Tree * t)
{
	string type;
	if(t->child[0]->token.size() == 2)
		type = "int";
	else
		type = "int*";
	
	parameterTable[currentScope].push_back(type);
}

void addParameter(Tree * t)
{
	addParameterMain(t->child[0]);
}


string getTypeExpr(Tree *t);
string getTypeTerm(Tree *t);
string getTypeFactor(Tree *t);
string getTypeLvalue(Tree *t);

void makeArgList(Tree *t, vector<string> &p)
{
	p.push_back(getTypeExpr(t->child[0]));
	if(t->token.size() == 4)
	{
		makeArgList(t->child[2], p);
	}
}

string getType(string name)
{
	map<string, string>::iterator it;
	
	it = symbolTable[currentScope].find(name);
	if(it == symbolTable[currentScope].end())
	{
		throw errorUndefined + "can not find" + name;
	}
	else
	{
		return symbolTable[currentScope][name];
	}
}

string getTypeExpr(Tree *t)//ggggg
{
	if(t->token.size() == 2)//expr → term
	{
		return getTypeTerm(t->child[0]);
	}
	else
	{
		string expr = getTypeExpr(t->child[0]);
		string term = getTypeTerm(t->child[2]);
		if(t->token[2] == "PLUS")//expr → expr PLUS term
		{
			if(expr == "int" && term == "int")
			{
				return "int";
			}
			else if(expr == "int*" && term == "int*")
			{
				throw errorType + "int* + int *";
			}
			else
			{
				return "int*";
			}
		}
		else//expr → expr MINUS term
		{
			if(expr == "int*" && term == "int")
			{
				return "int*";
			}
			else if(expr == "int" && term == "int*")
			{
				throw errorType + "int - int*";
			}
			else
			{
				return "int";
			}
		}
	}
}

string getTypeTerm(Tree *t)
{
	if(t->token.size() == 2)//expr → factor
	{
		return getTypeFactor(t->child[0]);
	}
	else//term → term STAR factor || term → term SLASH factor || term → term PCT factor
	{
		if(getTypeTerm(t->child[0]) != "int" || getTypeFactor(t->child[2]) != "int")
		{
			throw errorType + "only int */% int";
		}
		return "int";
	}
}

string getTypeFactor(Tree *t)
{
	if(t->token.size() == 2)//expr → factor
	{
		if(t->token[1] == "ID")//factor → ID
		{
			return getType(t->child[0]->token[1]);
		}
		else if(t->token[1] == "NUM")//factor → NUM
		{
			return "int";
		}
		else//factor → NULL
		{
			return "int*";
		}
	}
	else if(t->token.size() == 3)
	{
		if(t->token[1] == "AMP")//factor → AMP lvalue
		{
			if(getTypeLvalue(t->child[1]) == "int")
			{
				return "int*";
			}
			else
			{
				throw errorType + "& cant int*";
			}
		}
		else//factor → STAR factor
		{
			if(getTypeFactor(t->child[1]) == "int*")
			{
				return "int";
			}
			else
			{
				throw errorType + "* cant int";
			}
		}
	}
	else if(t->token[1] == "LPAREN")//factor → LPAREN expr RPAREN
	{
		return getTypeExpr(t->child[1]);
	}
	else if(t->token[1] == "NEW")//factor → NEW INT LBRACK expr RBRACK
	{
		if(getTypeExpr(t->child[3]) != "int")
			throw errorType + "new []int";
		return "int*";
	}
	else if(t->token.size() == 4)//factor → ID LPAREN RPAREN
	{
		if(parameterTable[t->child[0]->token[1]].size() != 0)
		{
			throw errorParameter + "function should not take any parameter!";
		}
		return "int";
	}
	else//factor → ID LPAREN arglist RPAREN
	{
		string functionName = t->child[0]->token[1];
		vector<string> par;
		makeArgList(t->child[2], par);
		
		if(par.size() != parameterTable[functionName].size())
		{
			throw errorParameter + "function take wrong number of arguments!";
		}
		
		for(int i=0; i<par.size(); i++)
		{
			if(par[i] != parameterTable[functionName][i])
			{
				throw errorParameter + "parameter type wrong!";
			}
		}
		return "int";
	}
}

string getTypeLvalue(Tree *t)
{
	if(t->token.size() == 2)// lvalue -> ID
	{
		return getType(t->child[0]->token[1]);
	}
	else if(t->token.size() == 3)// lvalue -> STAR factor
	{
		if(getTypeFactor(t->child[1]) == "int*")
		{
			return "int";
		}
		throw errorType + "* cant int";
	}
	else//lvalue → LPAREN lvalue RPAREN
	{
		return getTypeLvalue(t->child[1]);
	}
}

void checkTestWellType(Tree *t)
{
	if(getTypeExpr(t->child[0]) != getTypeExpr(t->child[2]))
	{
		throw errorWellType;
	}
}
void checkDclsWellType(Tree *t)
{
	if(t->token.size() != 1)
	{
		string dclType;
		if(t->child[1]->child[0]->token.size() == 2)
		{
			dclType = "int";
		}
		else
		{
			dclType = "int*";
		}
		if(t->token[4] == "NUM")//dcls → dcls dcl BECOMES NUM SEMI
		{
			if(dclType == "int*")
			{
				throw errorType + "Assignment between incompatible types.";
			}
		}
		else//dcls → dcls dcl BECOMES NULL SEMI
		{
			if(dclType == "int")
			{
				throw errorType + "Cannot initialize int with NULL.";
			}
		}
	}
}














string getIDDcl(Tree *t);
void implementFactor(Tree *t);
void implementTerm(Tree *t);
void implementExpr(Tree *t);
void implementLvalue(Tree *t);

int numArgu;
void traceArglist(Tree *t)
{
	numArgu++;

	//arglist → expr || arglist → expr COMMA arglist
	implementExpr(t->child[0]);
	cout << "sw $3, -4($30)" << endl;
	cout << "sub $30, $30, $14" << endl;

	if(t->token.size() == 4)//arglist → expr COMMA arglist
	{
		traceArglist(t->child[2]);
	}
}

int traceParamlist(Tree *t, int address)
{
	//paramlist → dcl || paramlist → dcl COMMA paramlist
	symbolAddress[currentScope][getIDDcl(t->child[0])] = address;

	if(t->token.size() == 4)//paramlist → dcl COMMA paramlist
	{
		return traceParamlist(t->child[2], address-4);
	}
	else//paramlist → dcl
	{
		return address;
	}
}

void traceParams(Tree *t)
{
	if(t->token.size() == 2)//params → paramlist
	{
		int offset;
		offset = traceParamlist(t->child[0], -4);
		//recalculateParamOffset
		for(map<string, int>::iterator it = symbolAddress[currentScope].begin(); it!= symbolAddress[currentScope].end(); it++)
		{
			it->second -= offset;
		}
	}
}


void callPrecdure(string precedureName, string para1 = "$0", string para2 = "$0", Tree *t = NULL)
{
	cout << "; sw b4 call precedure" << endl;
	cout << "sw $29, -4($30)" << endl;
	cout << "sub $30, $30, $14" << endl;

	cout << "; set parameter for precedure" << endl;

	cout << "add $1, $0, " << para1 << endl;
	cout << "add $2, $0, " << para2 << endl;

	numArgu = 0;
	if(t != NULL)
	{
		traceArglist(t);
	}

	cout << "lis $10" << endl;
	cout << ".word " << precedureName << "f" << endl;
	cout << "jalr $10" << endl;

	cout << "; lw after call precedure" << endl;
	cout << "lis $1" << endl;
	cout << ".word " << numArgu*4 << endl;
	cout << "add $30, $30, $1" << endl;
	cout << "add $30, $30, $14" << endl;
	cout << "lw $29, -4($30)" << endl;
}

string getIDDcl(Tree *t)
{
	return t->child[1]->token[1];
}

void implementExpr(Tree *t)
{
	if(t->token.size() == 2)//expr → term
	{
		implementTerm(t->child[0]);
	}
	else
	{
		implementExpr(t->child[0]);
		cout << "sw $3, -4($30)" << endl;
		cout << "sub $30, $30, $14" << endl;
		implementTerm(t->child[2]);
		cout << "add $30, $30, $14" << endl;
		cout << "lw $5, -4($30)" << endl;

		if(t->token[2] == "PLUS")//expr → expr PLUS term
		{
			if(getTypeExpr(t->child[0]) == "int*")//int* + int
			{
				cout << "mult $3, $14" << endl;
				cout << "mflo $3" << endl;
			}
			else if(getTypeTerm(t->child[2]) == "int*")//int + int*
			{
				cout << "mult $5, $14" << endl;
				cout << "mflo $5" << endl;
			}
			else//int + int
			{}
			cout << "add $3, $5, $3" << endl;
		}
		else//expr → expr MINUS term
		{
			if(getTypeExpr(t->child[0]) == "int*" && getTypeTerm(t->child[2]) == "int")//int* - int
			{
				cout << "mult $3, $14" << endl;
				cout << "mflo $3" << endl;
			}
			else//int - int && int* - int*
			{}
			cout << "sub $3, $5, $3" << endl;

			if(getTypeTerm(t->child[2]) == "int*")//int* - int*
			{
				cout << "div $3, $14" << endl;
				cout << "mflo $3" << endl;
			}
		}
	}
}

void implementTerm(Tree *t)
{
	if(t->token.size() == 2)//term → factor
	{
		implementFactor(t->child[0]);
	}
	else
	{
		implementTerm(t->child[0]);
		cout << "sw $3, -4($30)" << endl;
		cout << "sub $30, $30, $14" << endl;
		implementFactor(t->child[2]);
		cout << "add $30, $30, $14" << endl;
		cout << "lw $5, -4($30)" << endl;

		if(t->token[2] == "STAR")//term → term STAR factor
		{
			cout << "mult $5, $3" << endl;
			cout << "mflo $3" << endl;
		}
		else if(t->token[2] == "SLASH")//term → term SLASH factor
		{
			cout << "div $5, $3" << endl;
			cout << "mflo $3" << endl;
		}
		else//term → term PCT factor
		{
			cout << "div $5, $3" << endl;
			cout << "mfhi $3" << endl;
		}
	}
}

void implementFactor(Tree *t)
{
	if(t->token.size() == 2)
	{
		if(t->token[1] == "ID")//factor → ID
		{
			cout << "lw $3, " << symbolAddress[currentScope][t->child[0]->token[1]] << "($29)" << endl;
		}
		else if(t->token[1] == "NUM")//factor → NUM
		{
			cout << "lis $3" << endl;
			string num = t->child[0]->token[1];
			cout << ".word " << num << endl;
		}
		else//factor → NULL
		{
			cout << "add $3, $0, $11" << endl;
		}
	}
	else if(t->token[1] == "LPAREN")//factor → LPAREN expr RPAREN
	{
		implementExpr(t->child[1]);
	}
	else if(t->token[1] == "AMP")//factor → AMP lvalue
	{
		implementLvalue(t->child[1]);
	}
	else if(t->token[1] == "STAR")//factor → STAR factor
	{
		implementFactor(t->child[1]);
		cout << "lw $3, 0($3)" << endl;
	}
	else if(t->token[1] == "NEW")//factor → NEW INT LBRACK expr RBRACK
	{
		implementExpr(t->child[3]);
		cout << endl << "; NEW!" << endl;
		cout << "add $1, $3, $0" << endl;
		cout << "lis $10" << endl;
		cout << ".word new" << endl;
		cout << "jalr $10" << endl;
		cout << "bne $3, $0, 1" << endl;
		cout << "add $3, $0, $11" << endl;
	}
	else if(t->token[1] == "ID")//factor → ID LPAREN RPAREN
	{
		if(t->token.size() == 4)
		{
			callPrecdure(t->child[0]->token[1]);
		}
		else//factor → ID LPAREN arglist RPAREN
		{
			callPrecdure(t->child[0]->token[1], "$0", "$0", t->child[2]);
		}
	}
}

void implementLvalue(Tree *t)
{
	if(t->token[1] == "ID")//lvalue → ID
	{
		cout << "lis $3" << endl;
		cout << ".word " << symbolAddress[currentScope][t->child[0]->token[1]] << endl;
		cout << "add $3, $3, $29" << endl;
	}
	else if(t->token[1] == "STAR")//lvalue → STAR factor
	{
		implementFactor(t->child[1]);
	}
	else//lvalue → LPAREN lvalue RPAREN
	{
		implementLvalue(t->child[1]);
	}
}

void traceTest(Tree *t)
{
	implementExpr(t->child[0]);
	cout << "sw $3, -4($30)" << endl;
	cout << "sub $30, $30, $14" << endl;
	implementExpr(t->child[2]);
	cout << "add $30, $30, $14" << endl;
	cout << "lw $5, -4($30)" << endl;
	if(t->token[2] == "LT" || t->token[2] == "GE")
	{
		cout << "slt $3, $5, $3" << endl;
		if(t->token[2] == "GE")
		{
			cout << "sub $3, $11, $3" << endl;
		}
	}
	else if(t->token[2] == "GT" || t->token[2] == "LE")
	{
		cout << "slt $3, $3, $5" << endl;
		if(t->token[2] == "LE")
		{
			cout << "sub $3, $11, $3" << endl;
		}
	}
	else if(t->token[2] == "EQ" || t->token[2] == "NE")
	{
		cout << "slt $7, $3, $5" << endl;
		cout << "slt $8, $5, $3" << endl;
		cout << "add $3, $7, $8" << endl;
		if(t->token[2] == "EQ")
		{
			cout << "sub $3, $11, $3" << endl;
		}
	}
}


void traceStatements(Tree *t);

void traceStatement(Tree *t)
{
	if(t->token[1] == "PRINTLN")
	{
		implementExpr(t->child[2]);
		cout << endl << "; PRINT!" << endl;
		cout << "add $1, $3, $0" << endl;
		cout << "lis $10" << endl;
		cout << ".word print" << endl;
		cout << "jalr $10" << endl;
	}
	else if(t->token[1] == "lvalue")//statement → lvalue BECOMES expr SEMI
	{
		implementExpr(t->child[2]);
		cout << "add $6, $3, $0" << endl;
		implementLvalue(t->child[0]);
		cout << "sw $6, 0($3)" << endl;
	}
	else if(t->token[1] == "WHILE")//statement → WHILE LPAREN test RPAREN LBRACE statements RBRACE
	{
		int thisWhile = currentWhile;
		currentWhile++;
		cout << "while" << thisWhile << ":" << endl;
		traceTest(t->child[2]);
		cout << "beq $3, $0, endWhile" << thisWhile << endl;

		traceStatements(t->child[5]);
		cout << "beq $0, $0, while" << thisWhile << endl;
		cout << "endWhile" << thisWhile << ":" << endl;
	}
	else if(t->token[1] == "IF")//statement → IF LPAREN test RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE
	{
		int thisIf = currentIf;
		currentIf++;
		traceTest(t->child[2]);
		cout << "beq $3, $0, else" << thisIf << endl;

		traceStatements(t->child[5]);
		cout << "beq $0, $0, endIf" << thisIf << endl;

		cout << "else" << thisIf << ":" << endl;
		traceStatements(t->child[9]);

		cout << "endIf" << thisIf << ":" << endl;
	}

	else if(t->token[1] == "DELETE")//statement → DELETE LBRACK RBRACK expr SEMI
	{
		implementExpr(t->child[3]);
		cout << endl << "; DELETE!" << endl;
		cout << "beq $3, $11, 4" << endl;
		cout << "add $1, $3, $0" << endl;
		cout << "lis $10" << endl;
		cout << ".word delete" << endl;
		cout << "jalr $10" << endl;
	}
}

void traceStatements(Tree *t)
{
	if(t->token.size() == 3)
	{
		traceStatements(t->child[0]);
		traceStatement(t->child[1]);
	}
}


void traceDcls(Tree *t, int address)
{
	if(t->token.size() == 6)
	{
		string symbolName = getIDDcl(t->child[1]);
		symbolAddress[currentScope][symbolName] = address;
		cout << "lis $3" << endl;

		if(t->token[4] == "NUM")//dcls → dcls dcl BECOMES NUM SEMI
		{
			cout << ".word " << t->child[3]->token[1] << endl;
		}
		else//dcls → dcls dcl BECOMES NULL SEMI
		{
			cout << ".word 1" << endl;
		}
		cout << "sw $3, -4($30)" << endl;
		cout << "sub $30, $30, $14" << endl;
		traceDcls(t->child[0], address-4);
	}
}



void checkTree(Tree * t)
{
	for(vector<Tree *>::iterator it = t->child.begin(); it != t->child.end(); it++)
	{
		if((*it)->token[0] == "procedure")//procedure → INT ID LPAREN params RPAREN LBRACE dcls statements RETURN expr SEMI RBRACE
		{
			currentScope = (*it)->child[1]->token[1];
			map<string, vector<string> >::iterator itt;;
			itt = parameterTable.find(currentScope);
			if(itt != parameterTable.end())
			{
				throw errorDuplicate;
			}
			
			parameterTable[currentScope];
			
			checkTree(*it);
			if(getTypeExpr((*it)->child[9]) != "int")
			{
				throw errorReturnType;
			}


			traceParams((*it)->child[3]);

			//building asm
			cout << endl << (*it)->child[1]->token[1] << "f:" << endl;
			cout << "add $29, $30, $0" << endl;
			//push dcls
			traceDcls((*it)->child[6], -4);

			//push registers
			cout << "sw $1, -4($30)" << endl;
			cout << "sw $2, -8($30)" << endl;
			cout << "sw $5, -12($30)" << endl;
			cout << "sw $6, -16($30)" << endl;
			cout << "sw $7, -20($30)" << endl;
			cout << "sw $8, -24($30)" << endl;
			cout << "sw $10, -28($30)" << endl;
			cout << "sw $11, -32($30)" << endl;
			cout << "sw $14, -36($30)" << endl;
			cout << "sw $31, -40($30)" << endl;

			cout << "lis $1" << endl;
			cout << ".word 40" << endl;
			cout << "sub $30, $30, $1" << endl;
			
			//code for statements
			traceStatements((*it)->child[7]);
			//code for return expression
			implementExpr((*it)->child[9]);
			//pop registers
			cout << "lis $1" << endl;
			cout << ".word 40" << endl;
			cout << "add $30, $30, $1" << endl;
			cout << "lw $1, -4($30)" << endl;
			cout << "lw $2, -8($30)" << endl;
			cout << "lw $5, -12($30)" << endl;
			cout << "lw $6, -16($30)" << endl;
			cout << "lw $7, -20($30)" << endl;
			cout << "lw $8, -24($30)" << endl;
			cout << "lw $10, -28($30)" << endl;
			cout << "lw $11, -32($30)" << endl;
			cout << "lw $14, -36($30)" << endl;
			cout << "lw $31, -40($30)" << endl;

			cout << "add $30, $29, $0" << endl;
			cout << "jr $31" << endl;
		}
		else if((*it)->token[0] == "procedures")
		{
			if((*it)->token.size() == 2)//procedures → main
			{
				currentScope = "wain";
			}
			checkTree(*it);
		}
		else if((*it)->token[0] == "paramlist")//parameters
		{
			addParameter(*it);
			checkTree(*it);
		}
		else if((*it)->token[0] == "main")//main → INT WAIN LPAREN dcl COMMA dcl RPAREN LBRACE dcls statements RETURN expr SEMI RBRACE
		{
			addParameterMain((*it)->child[3]);
			addParameterMain((*it)->child[5]);
			if((*it)->child[5]->child[0]->token.size() == 3)
				throw errorParameter + "second argument should be int!";
			checkTree(*it);
			if(getTypeExpr((*it)->child[11]) != "int")
			{
				throw errorReturnType;
			}




			//building asm
			cout << endl << "main:" << endl;
			cout << "; parameters" << endl;
			cout << "add $29, $30, $0" << endl;
			cout << "sw $31, -4($30)" << endl;
			cout << "sub $30, $30, $14" << endl;
			symbolAddress[currentScope][getIDDcl((*it)->child[3])] = -8;
			cout << "sw $1, -4($30)" << endl;
			cout << "sub $30, $30, $14" << endl;
			symbolAddress[currentScope][getIDDcl((*it)->child[5])] = -12;
			cout << "sw $2, -4($30)" << endl;
			cout << "sub $30, $30, $14" << endl << endl;
			
			cout << endl << "; INIT!" << endl;
			if((*it)->child[3]->child[0]->token.size() != 3)
			{
				cout << "add $2, $0, $0" << endl;
			}
			cout << "lis $10" << endl;
			cout << ".word init" << endl;
			cout << "jalr $10" << endl;


			cout << "; dcls" << endl;
			traceDcls((*it)->child[8], -16);

			cout << endl << "; statements" << endl;
			traceStatements((*it)->child[9]);
			implementExpr((*it)->child[11]);

			cout << endl << "; return" << endl;
			cout << "lw $31, -4($29)" << endl;
			cout << "jr $31" << endl;
		}
		else if(((*it)->token[0] == "factor") && ((*it)->token[1] == "ID") && ((*it)->token.size() != 2))//factor → ID LPAREN RPAREN
		{
			string name = (*it)->child[0]->token[1];
			map<string, vector<string> >::iterator itt;;
			itt = parameterTable.find(name);
			if(itt == parameterTable.end())
			{
				throw errorUndefined;
			}
			map<string,string>::iterator ittt;
			ittt = symbolTable[currentScope].find(name);
			if(ittt != symbolTable[currentScope].end())
			{
				throw errorUndefined;
			}
			checkTree(*it);
		}
		else if((*it)->token[0] == "statement")//statement
		{
			checkTree(*it);
			if((*it)->token[1] == "DELETE")//statement → DELETE LBRACK RBRACK expr SEMI
			{
				if(getTypeExpr((*it)->child[3]) != "int*")
				{
					throw errorType;
				}
			}
			else if((*it)->token[1] == "PRINTLN")//statement → PRINTLN LPAREN expr RPAREN SEMI
			{
				if(getTypeExpr((*it)->child[2]) == "int*")
				{
					throw errorType + "cant print int*";
				}
			}
			else if((*it)->token[1] == "lvalue")//statement → lvalue BECOMES expr SEMI
			{
				if(getTypeLvalue((*it)->child[0]) != getTypeExpr((*it)->child[2]))
				{
					throw errorType + "assignment LHS type != RHS type!";
				}
			}
			else if((*it)->token[1] == "IF")//statement → IF LPAREN test RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE
			{
				checkTestWellType((*it)->child[2]);
			}
			else if((*it)->token[1] == "WHILE")//statement → WHILE LPAREN test RPAREN LBRACE statements RBRACE
			{
				checkTestWellType((*it)->child[2]);
			}
			else
			{
				cerr << "Never gona happen :D!" << endl;
			}
			
		}
		else if((*it)->token[0] == "dcl")//ID
		{
			addSymbol(*it);
		}
		else if((*it)->token[0] == "dcls")
		{
			checkTree(*it);
			checkDclsWellType(*it);
		}
		else if((((*it)->token[0] == "lvalue") && ((*it)->token.size() == 2)) || (((*it)->token[0] == "factor") && ((*it)->token.size() == 2) && ((*it)->token[1] == "ID")))
		{
			checkSymbol((*it)->child[0]->token[1]);
		}
		else
		{
			checkTree(*it);
		}
	}
}

void printTable()
{
	for(map<string, vector<string> >::iterator scope = parameterTable.begin(); scope != parameterTable.end(); scope++)
	{
		if(scope->first == "wain")
			continue;
		currentScope = scope->first;
		cerr << currentScope;
		for(vector<string>::iterator it = parameterTable[currentScope].begin(); it != parameterTable[currentScope].end(); it++)
		{
			cerr << " " << *it;
		}
		cerr << endl;
		for(map<string, string>::iterator it = symbolTable[currentScope].begin(); it!= symbolTable[currentScope].end(); it++)
		{
			cerr << it->first << " " << it->second << endl;
		}
		
		cerr << endl;
	}
	
	currentScope = "wain";
	cerr << currentScope;
	for(vector<string>::iterator it = parameterTable[currentScope].begin(); it != parameterTable[currentScope].end(); it++)
	{
		cerr << " " << *it;
	}
	cerr << endl;
	for(map<string, string>::iterator it = symbolTable[currentScope].begin(); it!= symbolTable[currentScope].end(); it++)
	{
		cerr << it->first << " " << it->second << endl;
	}
}

int main()
{
	Tree * bt = readTree();
	try
	{
		cout << "; preprocess" << endl;
		cout << ".import print" << endl;
		cout << ".import init" << endl;
		cout << ".import new" << endl;
		cout << ".import delete" << endl;
		cout << "lis $11" << endl;
		cout << ".word 1" << endl;
		cout << "lis $14" << endl;
		cout << ".word 4" << endl << endl;
		cout << "beq $0, $0, main" << endl;
		checkTree(bt);
		//printTable();
	}
	catch(string error)
	{
		cerr << "ERROR: " << error << endl;
	}
	//printTree(bt);
}

