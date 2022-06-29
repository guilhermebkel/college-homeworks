#include <iostream>
#include <string.h>

#include "lexicographic-analyser.h"
#include "lexicographic-util.h"
#include "arrangement-list.h"
#include "shared-util.h"

LexicographicAnalyser::LexicographicAnalyser() {
	this->wordOccurences = new ArrangementList<WordOccurence>();
	this->ordering = new ArrangementList<std::string>();
};

void LexicographicAnalyser::readOrdering (std::string letter) {
	char letterInCharFormat = letter[0];

	char lowerCasedLetter = lowerCaseLetter(letterInCharFormat);

	this->ordering->create(lowerCasedLetter, letter);
};

void LexicographicAnalyser::readWord (std::string word) {
	std::string normalizedWord = normalizeWord(word);

	char *normalizedWordInChar = castChar(normalizedWord);

	bool isWordAlreadyComputed = this->wordOccurences->existsByKey(normalizedWordInChar);

	if (isWordAlreadyComputed) {
		Item<WordOccurence> computedWord = this->wordOccurences->findByKey(normalizedWordInChar);

		computedWord.model.count++;

		this->wordOccurences->update(computedWord.key, computedWord.model);
	} else {
		WordOccurence wordOccurence;

		wordOccurence.rawWord = word;
		wordOccurence.count = 1;
		wordOccurence.normalizedWord = normalizedWord;

		this->wordOccurences->create(normalizedWordInChar, wordOccurence);
	}
};

ArrangementList<WordOccurence> *LexicographicAnalyser::getResult () {
	ArrangementList<WordOccurence> *orderedWords = new ArrangementList<WordOccurence>();

	for (int i = 0; i < this->wordOccurences->getSize(); i++) {
		Item<WordOccurence> computedWord = this->wordOccurences->findByIndex(i);

		orderedWords->create(computedWord.key, computedWord.model);
	}
	
	orderedWords->sort(makeLexicographicalComparison, this->ordering);

	ArrangementList<WordOccurence> *orderedWordOccurences = new ArrangementList<WordOccurence>();

	for (int i = 0; i < orderedWords->getSize(); i++) {
		Item<WordOccurence> orderedWord = orderedWords->findByIndex(i);

		Item<WordOccurence> wordOcurrence = this->wordOccurences->findByKey(orderedWord.key);

		orderedWordOccurences->create(wordOcurrence.key, wordOcurrence.model);
	}

	return orderedWordOccurences;
};
