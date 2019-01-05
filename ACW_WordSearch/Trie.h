#pragma once
#include <string>
#include <map>
#include <vector>
#include "Word.h"
#include "Trie.h"


struct Node {
	char val; 
	std::map<char, Node*> children;
};
class Trie
{
public:
	Trie();
	~Trie();

	void Construct(std::vector<Word> words);
	void Add(std::string word);
	bool DoesTreeContain(std::string target);
	int Size(); 

private:
	Node head; 
	std::vector<Node*> children; 
};

