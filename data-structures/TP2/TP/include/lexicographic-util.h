#ifndef LEXICOGRAPHIC_UTIL_H
#define LEXICOGRAPHIC_UTIL_H

#include "string.h"
#include "iostream"

#include "arrangement-list.h"

typedef bool (*compareKeys)(std::string, std::string);

std::string normalizeWord (std::string word);
CompareKeys compareLexicographicalWords (ArrangementList<std::string> *ordering);

#endif
