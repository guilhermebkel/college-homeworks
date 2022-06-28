#include <string.h>

#include "lexicographic-util.h"
#include "arrangement-list.h"
#include "shared-util.h"

std::string normalizeWord (std::string word) {
	std::string lowerCasedWord = toLowerCase(word);

	std::string wordWithoutSpecialCharacters = removeSpecialCharacters(lowerCasedWord);

	return wordWithoutSpecialCharacters;
};

CompareKeys compareLexicographicalWords (ArrangementList<std::string> *ordering) {
	struct Currying {
    static bool compare (std::string firstWord, std::string secondWord) {
			return true;
    }
  };

	return Currying::compare;
};
