#pragma once
#include <vector>
#include "Word.h"
#include "Trie.h"
/*Dictionary is the container class for the advanced dictionary. 
Contains a vector of Words and a binary trie for searching.
*/
class Dictionary
{
public:
	Dictionary();
	~Dictionary();

	std::vector<Word> dictionaryList; 
	Trie dictionaryTree; 
private:
};

