#include "Grid.h"
#include <algorithm>

Grid::Grid() {

}
Grid::Grid(std::string path)
{
	std::ifstream file;

	file.open(path);
	file >> width;

	std::vector<std::string> lines;
	std::vector<std::vector<char>> gridmatrix;

	// reads the contents line by line
	while (!file.eof()) {
		std::string l;
		std::getline(file, l);
		lines.push_back(l);
	}
	file.close();

	for (int i = 0; i < lines.size(); ++i) {
		std::vector<char> row;
		for (char& c : lines[i]) {
			if (c != ' ') {
				row.push_back(c);
			}
		}
		if (row.size() > 0) gridmatrix.push_back(row);
	}

	grid = gridmatrix;
}


Grid::~Grid()
{
}


std::vector<std::string> Grid::SearchGrid(size_t len, int x, int y)
{
	// all possible directional lines
	std::string lines[8] = {
		GetHorizontalLine(len, y, x),
		GetVerticalLine(len, y, x),
		GetDiagonalDownLine(len, y, x),
		GetDiagonalUpLine(len, y, x),
		GetLineHorizontalInverse(len, y, x),
		GetLineVerticalInverse(len, y, x),
		GetLineDiagonalDownInverse(len, y, x),
		GetLineDiagonalUpInverse(len, y, x)
	};	
	std::vector<std::string> v;

	// Copy over the string only if its length is equal to the words
	std::copy_if(std::begin(lines), std::end(lines), std::back_inserter(v), 
		[len](const std::string& i) { return len == i.length(); });
	
	return v;
}

int Grid::size()
{
	return width;
}

void Grid::Clear()
{
	grid.clear(); 
}



std::string Grid::GetHorizontalLine(size_t len, int zeroindex, int oneindex) {
	// returns the horizontal line from the current point right
	std::string line = ""; 

	for (int i = 0; oneindex < width && i < len; i++, oneindex++) {
		line += grid[zeroindex][oneindex];
	}
	return line;
}

std::string Grid::GetVerticalLine(size_t len, int zeroindex, int oneindex) {
	// returns the vertical line from current point down
	std::string line = ""; 

	for (int i = 0; zeroindex < width && i < len; i++, zeroindex++) {
		line += grid[zeroindex][oneindex];
	}
	return line;
}
std::string Grid::GetDiagonalUpLine(size_t len, int zeroindex, int oneindex) {
	// returns the diagonal line from current point -> NE 
	std::string line = ""; 

	for (int i = 0; zeroindex >= 0 && oneindex < width && i < len; i++, oneindex++, zeroindex--) {
		line += grid[zeroindex][oneindex];
	}
	return line;
}
std::string Grid::GetDiagonalDownLine(size_t len, int zeroindex, int oneindex) {
	// returns the diagonal line from current point -> SE 
	std::string line = ""; 
	
	for (int i = 0; zeroindex < width && oneindex < width && i < len; i++, zeroindex++, oneindex++) {
		line += grid[zeroindex][oneindex];
	}
	return line;
}

std::string Grid::GetLineHorizontalInverse(size_t len, int zeroindex, int oneindex){
	// returns the horizontal line from current point left 
	std::string line = "";

	for (int i = 0; oneindex >= 0 && i < len; i++, oneindex--) {
		line += grid[zeroindex][oneindex];
	}
	return line;
}

std::string Grid::GetLineVerticalInverse(size_t len, int zeroindex, int oneindex){
	// returns the vertical line from current point up 
	std::string line = "";

	for (int i = 0; zeroindex >= 0 && i < len; i++, zeroindex--) {
		line += grid[zeroindex][oneindex];
	}
	return line;
}

std::string Grid::GetLineDiagonalDownInverse(size_t len, int zeroindex, int oneindex){
	// returns the diagonal line from current point -> SW 
	std::string line = "";

	for (int i = 0; zeroindex >= 0 && oneindex >= 0 && i < len; i++, zeroindex--, oneindex--) {
		line += grid[zeroindex][oneindex];
	}
	return line;
}

std::string Grid::GetLineDiagonalUpInverse(size_t len, int zeroindex, int oneindex)
{
	// returns the diagonal line from current point -> SW 
	std::string line = "";

	for (int i = 0; zeroindex < width && oneindex >= 0 && i < len; i++, zeroindex++, oneindex--) {
		line += grid[zeroindex][oneindex];
	}
	return line;
}