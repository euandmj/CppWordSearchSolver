#include "WordSearch.h"
#include <iostream>
#include <tuple>
#include <fstream>
using namespace std;

WordSearch::WordSearch(){
	adv_dictionary = Dictionary();
}

WordSearch::WordSearch(string filename) {
	output_filename = filename;
	adv_dictionary = Dictionary(); 
}

WordSearch::~WordSearch() {
	// Add your code here
}

void WordSearch::ReadSimplePuzzle() {
	ifstream file;

	file.open(puzzleName);
	file >> n;

	vector<string> lines;
	vector<vector<char>> gridmatrix;

	// reads the contents line by line
	while (!file.eof()) {
		string l;
		getline(file, l);
		lines.push_back(l);
	}
	file.close();

	// loop through every line adding complete rows. 
	for (int i = 0; i < lines.size(); i++) {
		vector<char> row;
		for (char c : lines[i]) {
			if (c != ' ') {
				row.push_back(c);
			}
		}
		if (row.size() > 0) gridmatrix.push_back(row);
	}
	simple_grid = gridmatrix;
}

void WordSearch::ReadSimpleDictionary() {
	ifstream file;
	file.open(dictionaryName);

	if (file.is_open()) {
		while (!file.eof()) {
			string word;
			getline(file, word);
			simple_dictionary.push_back(word);
		}
	}
	else {
		cout << "Error: Could not open " << dictionaryName << endl;
	}
	file.close();
}

void WordSearch::ReadAdvancedDictionary() {
	ifstream file;
	file.open(dictionaryName);

	if (file.is_open()) {
		while (!file.eof()) {
			string word;
			getline(file, word);
			Word w = Word(word);
			adv_dictionary.dictionaryList.push_back(w);
		}

		adv_dictionary.dictionaryTree.Construct(adv_dictionary.dictionaryList);
	}
	else {
		cout << "Error: Could not open " << dictionaryName << endl;
	}
	file.close();
}

void WordSearch::ReadAdvancedPuzzle() {
	adv_grid = Grid(puzzleName);
}

void WordSearch::SolvePuzzleSimple() {
	// Similar method to the advanced solve but less condition checking. 
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			numCellsVisited++;
			// loop through the simple dictionary checking for matches.
			for (int j = 0; j < simple_dictionary.size(); j++){
				if (simple_grid[y][x] == simple_dictionary[j].at(0)) {
					// first letter match. 
					numDictEntriesVisited++;
					bool found = false;

					string lines[8] = {
						buildLineHorizontal(y, x),
						buildLineVertical(y, x),
						buildLineDiagonalDown(y, x),
						buildLineDiagonalUp(y, x),
						buildLineHorizontalInverse(y, x),
						buildLineVerticalInverse(y, x),
						buildLineDiagonalDownInverse(y, x),
						buildLineDiagonalUpInverse(y, x),
					};

					for (string l : lines) {

						found |= l.find(simple_dictionary[j]) != string::npos;
					}
					if (found) {
						simple_tuple.push_back(make_tuple(simple_dictionary[j], true, x, y));
						numWordsMatched++;
					}

				}
			}
		}
	}

	printPuzzle(simple_grid);

	// Fill out the simple tuple
	for (auto word : simple_dictionary) {
		bool isWordInTuple = false;
		for (auto t : simple_tuple) {
			isWordInTuple |= get<0>(t) == word;
		}
		if (!isWordInTuple) {
			simple_tuple.push_back(make_tuple(word, false, 0, 0));
		}
	}
}

void WordSearch::SolvePuzzleAdvanced() {
	/*
	A crawl of the advanced grid comparing to the advanced dictionary
	*/ 
	// Error handling for if the solve advanced has not been properly set up. 
	if (adv_grid.width == 0 || adv_dictionary.dictionaryList.size() == 0 || adv_dictionary.dictionaryTree.Size() == 0) {
		try {
			throw IncompleteAdvancedStructureException();
		}
		catch (IncompleteAdvancedStructureException& e) {
			cout << e.what() << endl; 
			system("pause"); 
			return;
		}
	}

	printPuzzle(adv_grid.grid); 

	for (int y = 0; y < adv_grid.width; ++y) {
		for (int x = 0; x < adv_grid.width; ++x) {
			numCellsVisited++;
			// loop through advanced dictionary.
			for (auto& word : adv_dictionary.dictionaryList) {
				if (adv_grid.grid[y][x] == word.value.at(0) && !word.isFound) {
					numDictEntriesVisited++;

					vector<string> lines = adv_grid.SearchGrid(word.value.length(), x, y);

					for (string l : lines) {					
							word.isFound |= adv_dictionary.dictionaryTree.DoesTreeContain(l); // call a prefix tree search for the word
					}
					if (word.isFound) {
						// log the find
						word.point = {
							(unsigned short)x, (unsigned short)y
						};
						numWordsMatched++;

						
						if (AllWordsAreFound()) return;
					}
				}
			}
		}
	} 
}

bool WordSearch::AllWordsAreFound() {
	// Used to potentially suspend searching through the grid. If all words are found, returns true.
	for (auto& word : adv_dictionary.dictionaryList) {
		if (!word.isFound) return false;
	}

	return true;
}

void WordSearch::WriteResultsToFile(const double loadTime, const double solveTime, vector<tuple<string, bool, int, int>>& results) {
	// Simple results write method	
	output_filename = output_filename == "" ? "output_simple.txt" : output_filename;
	ofstream file(output_filename);

	if (file.is_open()) {
		file << "NUMBER_OF_WORDS_MATCHED " << numWordsMatched << endl << endl;

		stringstream str1, str2;
		// loop over the tuple print found=true words and add the line to the string stream
		for (auto& tuple : results) {
			if (get<1>(tuple)) {
				str1 << get<2>(tuple) << " " << get<3>(tuple) << " " << get<0>(tuple) << endl;
			}
			else {
				str2 << get<0>(tuple) << endl;
			}
		}
		file << "WORDS_MATCHED_IN_GRID" << endl;
		file << str1.str();
		file << "\nWORDS_UNMATCHED_IN_GRID" << endl;
		file << str2.str();

		file << "\nNUMBER_OF_GRID_CELLS_VISITED " << numCellsVisited << endl;
		file << "\nNUMBER_OF_DICTIONARY_ENTRIES_VISITED " << numDictEntriesVisited << endl;
		file << "\nTIME_TO_POPULATE_GRID_STRUCTURE " << solveTime << endl;
		file << "\nTIME_TO_SOLVE_PUZZLE " << loadTime << endl;
	}

	file.close();
}

void WordSearch::WriteResultsToFile(const double loadTime, const double solveTime, vector<Word>& results) {
	// advanced results write method
	output_filename = output_filename == "" ? "output_advanced.txt" : output_filename;
	ofstream file(output_filename);

	if (file.is_open()) {
		file << "NUMBER_OF_WORDS_MATCHED " << numWordsMatched << endl << endl;

		stringstream str, str2; 
		// loop through all found words adding to corresponding string streams
		for (auto& s : results) {
			if (s.isFound) {
				str << s.point.X << " " << s.point.Y << " " << s.value << endl;
			}
			else {
				str2 << s.value << endl;
			}
		}

		

		file << "WORDS_MATCHED_IN_GRID" << endl;
		file << str.str() << endl;
		file << "WORD_UNMATCHED_IN_GRID" << endl;
		file << str2.str() << endl;
		

		file << "NUMBER_OF_GRID_CELLS_VISITED " << numCellsVisited << endl << endl;
		file << "NUMBER_OF_DICTIONARY_ENTRIES_VISITED " << numDictEntriesVisited << endl << endl;
		file << "TIME_TO_POPULATE_GRID_STRUCTURE " << loadTime << endl << endl;
		file << "TIME_TO_SOLVE_PUZZLE " << solveTime << endl;
	}
	file.close();
}

void WordSearch::WriteResults(const double loadTime, const double solveTime){
	// Determine which write method to call since the advanced dictionary holds data for the results, 
	// whereas the simple dictionary relies on a tuple. 
	// Depends on the states of certain data structures. 

	if (simple_tuple.size() > 0) {
		WriteResultsToFile(loadTime, solveTime, simple_tuple);
	}
	else {
		WriteResultsToFile(loadTime, solveTime, adv_dictionary.dictionaryList);
	}
}

void WordSearch::WriteResults(const double loadTime, const double solveTime, string path){
	// overload that takes string file path param. ACW is a bit vague on this. 
	output_filename = path;
	if (simple_tuple.size() > 0) {
		WriteResultsToFile(loadTime, solveTime, simple_tuple);
	}
	else {
		WriteResultsToFile(loadTime, solveTime, adv_dictionary.dictionaryList);
	}
}

template<class T>
void WordSearch::printPuzzle(T grid)
{
	for (int y = 0; y < grid.size(); ++y) {
		for (int x = 0; x < grid.size(); ++x) {
			cout << grid[y][x] << '|';
		}
		cout << endl;
	}
	cout << endl; 
}

string WordSearch::buildLineHorizontal(int zeroIndex, int oneIndex){
	string line = "";

	for (int i = oneIndex; i < n; i++) {
		line += simple_grid[zeroIndex][i];
	}

	return line;
}

string WordSearch::buildLineHorizontalInverse(int zeroindex, int oneindex) {
	string line = "";

	for (int i = oneindex; i >= 0; i--) {
		line += simple_grid[zeroindex][i];
	}
	return line;
}

string WordSearch::buildLineVertical(int zeroIndex, int oneIndex) {
	string line = "";

	for (int i = zeroIndex; i < n; i++) {
		line += simple_grid[i][oneIndex];
	}
	return line;
}

string WordSearch::buildLineVerticalInverse(int zeroindex, int oneindex) {
	string line = "";

	for (int i = zeroindex; i >= 0; i--) {
		line += simple_grid[i][oneindex];
	}
	return line;
}

string WordSearch::buildLineDiagonalDown(int zeroIndex, int oneIndex) {
	string line = "";

	for (int i = zeroIndex; i < n && oneIndex < n; i++,	oneIndex++) {
		line += simple_grid[i][oneIndex];
	}
	return line;
}

string WordSearch::buildLineDiagonalDownInverse(int zeroIndex, int oneIndex) {
	string line = "";

	for (int i = zeroIndex; i >= 0 && oneIndex >= 0; i--, oneIndex--) {
		line += simple_grid[i][oneIndex];
	}
	return line;
}

string WordSearch::buildLineDiagonalUp(int zeroIndex, int oneIndex) {
	string line = "";

	// x will increase whilst y will decrease. 
	for (int i = zeroIndex; i >= 0 && oneIndex < n; i--, oneIndex++) {
		line += simple_grid[i][oneIndex];
	}
	return line;
}

string WordSearch::buildLineDiagonalUpInverse(int zeroIndex, int oneIndex) {
	string line = "";

	for (int i = zeroIndex; i < n && oneIndex >= 0; i++, oneIndex--) {
		line += simple_grid[i][oneIndex];
	}
	return line;
}