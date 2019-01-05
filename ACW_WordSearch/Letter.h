#pragma once
#include <string>
class Letter
{
public:
	Letter(char val);
	Letter();
	~Letter();

	char value = '0'; 
	bool isFound = false; 

	char GetValue();
};


