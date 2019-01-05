#include "Letter.h"


Letter::Letter(char val)
{
	value = val;
}

Letter::Letter() 
{

}


Letter::~Letter()
{
}

char Letter::GetValue() {
	return value;
	/*
	if (isFound) {
		for (int i = 0; i < alphabet.length(); i++) {
			if (alphabet[i] == value) {
				return striked_alphabet.at(i);
			}
		}
	}
	else {
		return value;
	}
	*/
}
