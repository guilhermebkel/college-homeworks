#ifndef POKER_FACE_VALIDATION_H
#define POKER_FACE_VALIDATION_H

#include "poker-face.h"

class PokerFaceValidation {
  public:
		bool handHasClassificationType (Hand hand, ClassifiedHandType classifiedHandType);

	private:
		bool handHasSingleSuit (Hand hand);
		bool handHasCardsWithEqualValues (Hand hand, int group1, int group2, int group3, int group4, int group5);
		bool handHasSequentialCombination (Hand hand);
};

#endif