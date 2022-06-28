#include <string.h>
#include <iostream>
#include <locale>

char *castChar (std::string value) {
	char *charValue = new char[value.length()];

	strcpy(charValue, value.c_str());

	return charValue;
};

std::string toLowerCase (std::string value) {
	std::string lowerCasedValue;

	std::locale loc;

	for(auto letter : value) {
		char lowerCasedLetter = std::tolower(letter, loc);

		lowerCasedValue.push_back(lowerCasedLetter);
	}

	return lowerCasedValue;
};

std::string removeSpecialCharacters (std::string value) {
	std::string valueWithoutSpecialCharacters = value;

	for (int i = 0; i < valueWithoutSpecialCharacters.size(); i++) {
		char character = valueWithoutSpecialCharacters[i];

		bool isSpecialCharacter = (character < 'A' || character > 'Z') && (character < 'a' || character > 'z');

		if (isSpecialCharacter) { 
			valueWithoutSpecialCharacters.erase(i, 1);

			i--;
		}
	}

	return valueWithoutSpecialCharacters;
};
