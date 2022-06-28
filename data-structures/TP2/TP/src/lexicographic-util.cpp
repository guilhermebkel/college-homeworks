#include "lexicographic-util.h"
#include "shared-util.h"

std::string normalizeWord (std::string word) {
	std::string lowerCasedWord = toLowerCase(word);

	std::string wordWithoutSpecialCharacters = removeSpecialCharacters(lowerCasedWord);

	return wordWithoutSpecialCharacters;
};

std::string lexicographicalSortingParam (std::string word) {
	return word;
};
