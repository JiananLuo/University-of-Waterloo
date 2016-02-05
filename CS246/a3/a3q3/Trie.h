#ifndef __TRIE_H__
#define __TRIE_H__
#include <string>

const int NumChars = 26;

struct TrieNode
{
    bool isWord;
    TrieNode *letters[NumChars];
    /************** TrieNode ************
	     Purpose: Constructor for TrieNode
	     Returns: Return nothing
	     Error: None
	************************************/
    TrieNode();
    /************** ~TrieNode ************
	     Purpose: Destructor for TrieNode
	     Returns: Return nothing
	     Error: None
	************************************/
    ~TrieNode();
	/************** insert *************
	     Purpose: Insert the word which is the parameter to the TrieNode
	     Returns: Return nothing
	     Error: None
	************************************/
    void insert(const std::string &word);
    /************** remove *************
	     Purpose: Remove the word which is the parameter from the TrieNode
	     Returns: Return nothing
	     Error: None
	************************************/
    void remove(const std::string &word);
	/*************** find **************
	     Purpose: Find the total number of node in the TrieNode
	     Returns: Return a int which is the total size of the TrieNode
	     Error: None
	************************************/
    std::string find(const std::string &word);
    /************* findPrefix ***********
	     Purpose: Find a big string which is the all possiable output for the word
	     Returns: Return a big string which is the all possiable output for the word
	     Error: None
	************************************/
    std::string findPrefix(const std::string &word, std::string &prefix);
    /************ smartDelete ***********
	     Purpose: Remove unused nodes from the TrieNode
	     Returns: Return nothing
	     Error: None
	************************************/
    void smartDelete(std::string &word);
    /*************** size **************
	     Purpose: Find the total number of node in the TrieNode
	     Returns: Return a int which is the total size of the TrieNode
	     Error: None
	************************************/
    int size();
}; // TrieNode

#endif
