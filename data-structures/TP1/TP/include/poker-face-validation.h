#ifndef POKER_FACE_VALIDATION_H
#define POKER_FACE_VALIDATION_H

#include "poker-face.h"
#include "arrangement-list.h"

enum TieResult {
	OVERWRITE_WINNER = 1,
	ADD_WINNER = 2,
	NO_TIE_FOUND = 3
};

bool handHasClassificationType (Hand hand, ClassifiedHandType classifiedHandType);
bool isInvalidPlay (Round round, ArrangementList<Balance> *balances);
TieResult assertTie (RoundWinner currentWinner, Play possibleWinnerPlay);

#endif