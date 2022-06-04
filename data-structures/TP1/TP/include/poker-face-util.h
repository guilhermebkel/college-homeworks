#ifndef POKER_FACE_UTIL_H
#define POKER_FACE_UTIL_H

#include "poker-face.h"

enum TieResult {
	OVERWRITE_WINNER = 1,
	ADD_WINNER = 2,
	NO_TIE_FOUND = 3
};

int getBalanceSortingParam (Balance balance);
int getCardComboSortingParam (CardCombo cardCombo);
int getCardSortingParam (Card card);
GroupedCardCombo groupCardsWithEqualValues (Hand hand);
int getCardComboScore (CardCombo cardCombo);
Card getGreaterCard (Hand hand);
ClassifiedHand classifyHand (Hand hand);
TieResult assertTie (RoundWinner currentWinner, Play possibleWinnerPlay);

#endif