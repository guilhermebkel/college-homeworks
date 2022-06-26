#include <string.h>
#include <iostream>

char *castChar (std::string value) {
	char *charValue = new char[value.length()];

	strcpy(charValue, value.c_str());

	return charValue;
};
