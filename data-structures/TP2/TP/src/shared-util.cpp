#include <string.h>
#include <iostream>
#include <locale>

char *castChar (std::string value) {
	char *charValue = new char[value.length()];

	strcpy(charValue, value.c_str());

	return charValue;
};

char lowerCaseLetter (char value) {
	std::locale loc;

	char lowerCasedLetter = std::tolower(value, loc);

	return lowerCasedLetter;
};

std::string lowerCaseWord (std::string value) {
	std::string lowerCasedValue;

	for(auto letter : value) {
		char lowerCasedLetter = lowerCaseLetter(letter);

		lowerCasedValue.push_back(lowerCasedLetter);
	}

	return lowerCasedValue;
};

bool isSpecialCharacter (char character) {
	return (character < 'A' || character > 'Z') && (character < 'a' || character > 'z');
};

std::string removeSpecialCharacters (std::string value) {
	std::string valueWithoutSpecialCharacters = value;

	for (int i = 0; i < valueWithoutSpecialCharacters.size(); i++) {
		char character = valueWithoutSpecialCharacters[i];

		if (isSpecialCharacter(character)) {
			valueWithoutSpecialCharacters.erase(i, 1);

			i--;
		}
	}

	return valueWithoutSpecialCharacters;
};
