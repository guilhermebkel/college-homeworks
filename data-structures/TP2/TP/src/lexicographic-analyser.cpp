#include <iostream>
#include <string.h>

#include "lexicographic-analyser.h"
#include "lexicographic-util.h"
#include "arrangement-list.h"
#include "shared-util.h"

LexicographicAnalyser::LexicographicAnalyser() {
	this->wordOccurences = new ArrangementList<int>();
	this->ordering = new ArrangementList<std::string>();
};

void LexicographicAnalyser::readOrdering (std::string letter) {
	this->ordering->create(castChar(letter), letter);
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

	for (int i = 0; i < this->wordOccurences->getSize(); i++) {
		Item<int> computedWord = this->wordOccurences->findByIndex(i);

		orderedWords->create(computedWord.key, computedWord.key);
	}
	
	orderedWords->sort(compareLexicographicalWords(this->ordering));

	ArrangementList<int> *orderedWordOccurences = new ArrangementList<int>();

	for (int i = 0; i < orderedWords->getSize(); i++) {
		Item<std::string> orderedWord = orderedWords->findByIndex(i);

		Item<int> wordOcurrence = this->wordOccurences->findByKey(orderedWord.key);

		orderedWordOccurences->create(wordOcurrence.key, wordOcurrence.model);
	}

	return orderedWordOccurences;
};
