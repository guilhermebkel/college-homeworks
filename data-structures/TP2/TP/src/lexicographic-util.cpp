#include <string.h>

#include "lexicographic-util.h"
#include "arrangement-list.h"
#include "shared-util.h"
#include "lexicographic-analyser.h"

std::string normalizeWord (std::string word) {
	std::string lowerCasedWord = toLowerCase(word);

	std::string wordWithoutSpecialCharacters = removeSpecialCharacters(lowerCasedWord);

	return wordWithoutSpecialCharacters;
};

CompareKeys<WordOccurence> compareLexicographicalWords (ArrangementList<std::string> *ordering) {
	struct Currying {
    static bool compare (WordOccurence firstModel, WordOccurence secondModel) {
			return true;
    }
  };

	return Currying::compare;
};
