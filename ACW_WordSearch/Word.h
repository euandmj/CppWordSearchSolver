#include <string>
#pragma once
struct Point {
	unsigned short X;
	unsigned short Y;
};

class Word
{
private:
public:	
	Word();
	Word(std::string &val);
	~Word();

	bool isFound = false;
	std::string value = "-NAN-";
	Point point;
};