#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include "Trie.h"
#include "Word.h"
#include "Grid.h"
using namespace std;

class WordSearch {
	const char* puzzleName = "wordsearch_grid.txt";
	const char* dictionaryName = "dictionary.txt";

	struct IncompleteAdvancedStructureException : public exception {
		const virtual char* what() const throw() {
			return "Advanced solve uses the two advanced data structures \"adv_grid\" and \"adv_dictionary\".\nPlease call \"WordSearch::ReadAdvancedPuzzle()\" and \"WordSearch::ReadAdvancedDictionary()\"";
		}
	};

	struct Dictionary {
		vector<Word> dictionaryList;
		Trie dictionaryTree;
	};
	
	// Add your code here
public:
	WordSearch(); 
	explicit WordSearch(string filename);
	~WordSearch();

	int numWordsMatched = 0, numCellsVisited = 0, numDictEntriesVisited = 0;


	void ReadSimplePuzzle();
	void ReadSimpleDictionary();
	void ReadAdvancedPuzzle();
	void ReadAdvancedDictionary();
	void SolvePuzzleSimple();
	void SolvePuzzleAdvanced();
	void WriteResults(const	double loadTime, const double solveTime);
	void WriteResults(const double loadTime, const double solveTime, string path);

	template <class T> void printPuzzle(T grid);

	// Add your code here
private:
	int n = 0; 

	string output_filename = "";
	vector<vector<char>> simple_grid;
	Dictionary adv_dictionary;
	Grid adv_grid;

	vector<tuple<string, bool, int, int>> simple_tuple; // word, isfound, x, y.
	vector<string> simple_dictionary;

	bool AllWordsAreFound();
	string buildLineHorizontal(int zeroIndex, int oneIndex);
	string buildLineHorizontalInverse(int zeroindex, int oneindex);
	string buildLineVertical(int zeroIndex, int oneIndex);
	string buildLineVerticalInverse(int zeroindex, int oneindex);
	string buildLineDiagonalDown(int zeroIndex, int oneIndex);
	string buildLineDiagonalDownInverse(int zeroIndex, int oneIndex);
	string buildLineDiagonalUp(int zeroIndex, int oneIndex);
	string buildLineDiagonalUpInverse(int zeroIndex, int oneIndex);
	// Seperate overloaded functions required due to not being able to modify Main.cpp
	void WriteResultsToFile(const double loadTime, const double solveTime, vector<tuple<string, bool, int, int>>& results);
	void WriteResultsToFile(const double loadTime, const double solveTime, vector<Word>& results);
};