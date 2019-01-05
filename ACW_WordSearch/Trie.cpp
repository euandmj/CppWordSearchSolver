#include "Word.h"
#include "Trie.h"

Trie::Trie()
{
}


Trie::~Trie()
{
	// delete the children nodes from memory since they aree held within
	for (auto& node : children) {
		delete node;
	}
}

void Trie::Construct(std::vector<Word> words)
{
	// send each dictionary word to the Add function
	for (auto& w : words) {
		Add(w.value); 
	}
	int x = 5;
}

void Trie::Add(std::string word)
{
	std::map<char, Node*>* tree = &head.children;
	std::map<char, Node*>::iterator it;

	// loop through characters, traversing down through the tree and inserting nodes where one
	// does not exist 
	for (char& c : word) {
		if ((it = tree->find(c)) != tree->end()){
			tree = &it->second->children;
			continue;
		}

		if (it == tree->end()) {
			// create and add the new node 
			Node* newNode = new Node();
			newNode->val = c;
			(*tree)[c] = newNode;

			tree = &newNode->children;
			children.push_back(newNode);
		}
	}
}

bool Trie::DoesTreeContain(std::string target)
{
	std::map<char, Node*> tree = head.children;
	std::map<char, Node*>::iterator it;

	for (char& c : target)
	{
		// the current letter does not match an existing node
		if ((it = tree.find(c)) == tree.end()) return false; 

		// node matches letter, continue down the tree
		tree = it->second->children;

	}
	// return true if this is an end node
	return tree.empty() ? true : false;
}

int Trie::Size()
{
	return (int)children.size();
}
