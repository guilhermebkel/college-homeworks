#ifndef POKER_FACE_UTIL_H
#define POKER_FACE_UTIL_H

#include "poker-face.h"

int getBalanceSortingParam (Balance balance);
int getCardComboSortingParam (CardCombo cardCombo);
int getCardSortingParam (Card card);
GroupedCardCombo groupCardsWithEqualValues (Hand hand);
int getCardComboScore (CardCombo cardCombo);
Card getGreaterCard (Hand hand);
ClassifiedHand classifyHand (Hand hand);

#endif