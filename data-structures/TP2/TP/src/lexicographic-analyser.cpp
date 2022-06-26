#include <iostream>
#include <string.h>

#include "lexicographic-analyser.h"
#include "lexicographic-util.h"
#include "arrangement-list.h"
#include "shared-util.h"

LexicographicAnalyser::LexicographicAnalyser(std::string lexicographicalOrdering) {
	this->lexicographicalOrdering =  lexicographicalOrdering;

	this->wordOcurrences = new ArrangementList<int>();
};

void LexicographicAnalyser::readWord (std::string word) {
	std::string normalizedWord = normalizeWord(word);

	char *normalizedWordInChar = castChar(normalizedWord);

	bool isWordAlreadyComputed = this->wordOcurrences->existsByKey(normalizedWordInChar);

	if (isWordAlreadyComputed) {
		Item<int> computedWord = this->wordOcurrences->findByKey(normalizedWordInChar);

		this->wordOcurrences->update(computedWord.key, computedWord.model + 1);
	} else {
		this->wordOcurrences->create(normalizedWordInChar, 1);
	}
};

ArrangementList<int> *LexicographicAnalyser::getResult () {
	return this->wordOcurrences;
};
