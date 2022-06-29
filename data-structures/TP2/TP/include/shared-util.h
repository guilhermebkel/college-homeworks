#ifndef SHARED_UTIL_H
#define SHARED_UTIL_H

#include <iostream>
#include <string.h>

char *castChar (std::string value);
std::string lowerCaseWord (std::string value);
char lowerCaseLetter (char value);
std::string removeSpecialCharacters (std::string value);
bool isSpecialCharacter (char character);

#endif