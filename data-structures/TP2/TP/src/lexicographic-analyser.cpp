#include <iostream>
#include <string.h>

#include "lexicographic-analyser.h"
#include "lexicographic-util.h"
#include "arrangement-list.h"
#include "shared-util.h"

LexicographicAnalyser::LexicographicAnalyser(std::string lexicographicalOrdering) {
	this->lexicographicalOrdering =  lexicographicalOrdering;

	this->wordOccurences = new ArrangementList<int>();
};

void LexicographicAnalyser::readWord (std::string word) {
	std::string normalizedWord = normalizeWord(word);

	char *normalizedWordInChar = castChar(normalizedWord);

	bool isWordAlreadyComputed = this->wordOccurences->existsByKey(normalizedWordInChar);

	if (isWordAlreadyComputed) {
		Item<int> computedWord = this->wordOccurences->findByKey(normalizedWordInChar);

		this->wordOccurences->update(computedWord.key, computedWord.model + 1);
	} else {
		this->wordOccurences->create(normalizedWordInChar, 1);
	}
};

ArrangementList<int> *LexicographicAnalyser::getResult () {
	ArrangementList<std::string> *orderedWords = new ArrangementList<std::string>();

	ArrangementList<int> *orderedWordOccurences = new ArrangementList<int>();

	for (int i = 0; i < orderedWords->getSize(); i++) {
		Item<std::string> orderedWord = orderedWords->findByIndex(i);

		Item<int> wordOcurrence = this->wordOccurences->findByKey(orderedWord.key);

		orderedWordOccurences->create(wordOcurrence.key, wordOcurrence.model);
	}

	return orderedWordOccurences;
};
