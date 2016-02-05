#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <string>
#include "Trie.h"

//see header file
TrieNode::TrieNode()
{
	this->isWord = false;
	for(int i=0; i<NumChars; i++)
	{
		this->letters[i] = NULL;
	}
}

//see header file
TrieNode::~TrieNode()
{
	for(int i=0; i<NumChars; i++)
	{
		delete this->letters[i];
	}
}

//see header file
void TrieNode::insert(const std::string &word)
{

	int n = word[0] - 'a';
	if(letters[n] == NULL)
		this->letters[n] = new TrieNode;
	if(word.length() == 1)
	{
		this->letters[n]->isWord = true;
	}
	else
	{
		std::string s = word;
		s.erase(0,1);
		this->letters[n]->insert(s);
	}
}

//see header file
void TrieNode::remove(const std::string &word)
{
	int n = word[0] - 'a';
	std::string empty;
	if(word.length() == 0)
	{
		if(this->isWord == true)
		{
			this->isWord = false;
		}
	}
	else
	{
		std::string s = word;
		s.erase(0,1);
		if(this->letters[n] != NULL)
			this->letters[n]->remove(s);
	}
}

//see header file
std::string TrieNode::findPrefix(const std::string &word, std::string &prefix)
{
	std::string s;
	if(word.length() == 0)
	{
		if(this->isWord == true)
		{
			s = s + prefix + " ";
		}
		for(int i=0; i<NumChars; i++)
		{
			if(this->letters[i] != NULL)
			{
				char c = 'a' + i;
				std::string nodePrefix = prefix + c;
				s = s + this->letters[i]->findPrefix(word, nodePrefix);
			}
		}
	}
	else
	{
		int n = word[0] - 'a';
		prefix += word[0];
		std::string t = word;
		t.erase(0,1);
		if(this->letters[n] != NULL)
			return this->letters[n]->findPrefix(t, prefix);
		else
			return s;//word doesnt exist
	}
	return s;
}

//see header file
void TrieNode::smartDelete(std::string &word)
{
	if(word.length() != 0)
	{
		int n = word[0] - 'a';
		std::string t = word;
		t.erase(0,1);
		if(this->letters[n] != NULL)
			this->letters[n]->smartDelete(t);
	}
	else
	{
		for(int i=0; i<NumChars; i++)
		{
			delete this->letters[i];
			this->letters[i] = NULL;
		}
	}
}

//see header file
std::string TrieNode::find(const std::string &word)
{
	std::string empty;
	return this->findPrefix(word, empty);
}

//see header file
int TrieNode::size()
{
	int total = 1;
	for(int i=0; i<NumChars; i++)
	{
		if(this->letters[i] != NULL)
			total = total + this->letters[i]->size();
	}
	return total;
}
