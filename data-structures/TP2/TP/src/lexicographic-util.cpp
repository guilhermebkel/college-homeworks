#include <string.h>
#include <iostream>

#include "lexicographic-util.h"
#include "arrangement-list.h"
#include "shared-util.h"
#include "lexicographic-analyser.h"

std::string normalizeWord (std::string word) {
	std::string lowerCasedWord = lowerCaseWord(word);

	std::string wordWithoutSpecialCharacters = removeSpecialCharacters(lowerCasedWord);

	return wordWithoutSpecialCharacters;
};

int getLexicographicalValue (char character, ArrangementList<std::string> *ordering) {
	char lowerCasedLetter = lowerCaseLetter(character);

	bool lexicographicalOrderingExists = ordering->existsByKey(lowerCasedLetter);

	if (lexicographicalOrderingExists) {
		Item<std::string> lexicographicalOrdering = ordering->findByKey(lowerCasedLetter);

		int lexicographicalValue = ordering->getSize() - lexicographicalOrdering.index;

		return lexicographicalValue;
	} else {
		return -1;
	}
};

bool makeLexicographicalComparison (WordOccurence firstModel, WordOccurence secondModel, ArrangementList<std::string> *lexicographicalOrdering) {
	int i;

	std::string firstRawWord = firstModel.rawWord;
	std::string secondRawWord = secondModel.rawWord;

	for (i = 0; firstRawWord[i] == secondRawWord[i]; ++i) {
		if (firstRawWord[i] == '\0') {
			return 0;
		}
	}

	unsigned char firstRawWordComparableLetter = firstRawWord[i];
	unsigned char secondRawWordComparableLetter = secondRawWord[i];

	int comparison;

	if (isSpecialCharacter(firstRawWordComparableLetter) || isSpecialCharacter(secondRawWordComparableLetter)) {
		comparison = secondRawWordComparableLetter - firstRawWordComparableLetter;
	} else {
		comparison = getLexicographicalValue(secondRawWordComparableLetter, lexicographicalOrdering) - getLexicographicalValue(firstRawWordComparableLetter, lexicographicalOrdering);
	}

	std::cout << firstRawWord << " " << secondRawWord << " " << comparison << std::endl;

	if (comparison > 0) {
		return true;
	} else {
		return false;
	}
}
