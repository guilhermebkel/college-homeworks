#ifndef LEXICOGRAPHIC_UTIL_H
#define LEXICOGRAPHIC_UTIL_H

#include "string.h"
#include "iostream"

#include "arrangement-list.h"
#include "lexicographic-analyser.h"

std::string normalizeWord (std::string word);
bool makeLexicographicalComparison (WordOccurence firstModel, WordOccurence secondModel, ArrangementList<std::string> *lexicographicalOrdering);
int getLexicographicalValue (char character, ArrangementList<std::string> *ordering);

#endif
