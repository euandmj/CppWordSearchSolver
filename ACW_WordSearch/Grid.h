#include <vector>
#include <string>
#include <fstream>
#pragma once
class Grid
{
public:
	Grid();
	Grid(std::string path);
	~Grid();

	int width = 0;
	std::vector<std::vector<char>> grid;

	//bool SearchGrid(std::string& word, int x, int y);

	std::vector<std::string> Grid::SearchGrid(size_t, int x, int y);
	int size();  
	void Clear();

private:
	std::string GetHorizontalLine(size_t wordlength, int zeroIndex, int oneIndex);
	std::string GetVerticalLine(size_t wordlength, int zeroIndex, int oneIndex);
	std::string GetDiagonalUpLine(size_t wordlength, int zeroIndex, int oneIndex);
	std::string GetDiagonalDownLine(size_t wordlength, int zeroIndex, int oneIndex);
	std::string GetLineHorizontalInverse(size_t wordlength, int zeroIndex, int oneIndex);
	std::string GetLineVerticalInverse(size_t wordlength, int zeroIndex, int oneIndex);
	std::string GetLineDiagonalDownInverse(size_t wordlength, int zeroIndex, int oneIndex);
	std::string GetLineDiagonalUpInverse(size_t wordlength, int zeroIndex, int oneIndex);
};

