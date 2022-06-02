#include "poker-face.h"
#include "poker-face-validation.h"
#include "poker-face-util.h"

bool PokerFaceValidation::handHasCardsWithEqualValues (Hand hand, int group1 = 1, int group2 = 1, int group3 = 1, int group4 = 1, int group5 = 1) {
	PokerFaceUtil *pokerFaceUtil = new PokerFaceUtil();
	
	GroupedCardCombo groupedCardWithEqualValues = pokerFaceUtil->groupCardsWithEqualValues(hand);

	return (
		groupedCardWithEqualValues.group1.totalCards == group1 &&
		groupedCardWithEqualValues.group2.totalCards == group2 &&
		groupedCardWithEqualValues.group3.totalCards == group3 &&
		groupedCardWithEqualValues.group4.totalCards == group4 &&
		groupedCardWithEqualValues.group5.totalCards == group5
	);
}

bool PokerFaceValidation::handHasClassificationType (Hand hand, ClassifiedHandType classifiedHandType) {
	bool result = false;

	bool hasSameSuit = handHasSingleSuit(hand);
	bool hasCorrectCombination = (hand[0].value == 1) && (hand[1].value == 10) && (hand[2].value == 11) && (hand[3].value == 12) && (hand[4].value == 13);

	switch (classifiedHandType){
		case ClassifiedHandType::ROYAL_STRAIGHT_FLUSH:
			result = hasSameSuit && hasCorrectCombination;
			break;

		case ClassifiedHandType::STRAIGHT_FLUSH:
			result = this->handHasSingleSuit(hand) && this->handHasSequentialCombination(hand);
			break;

		case ClassifiedHandType::FOUR_OF_A_KIND:
			result = this->handHasCardsWithEqualValues(hand, 4);
			break;

		case ClassifiedHandType::FULL_HOUSE:
			result = this->handHasCardsWithEqualValues(hand, 3, 2);
			break;

		case ClassifiedHandType::FLUSH:
			result = this->handHasSingleSuit(hand) && !this->handHasSequentialCombination(hand);
			break;

		case ClassifiedHandType::STRAIGHT:
			result = this->handHasSequentialCombination(hand);
			break;

		case ClassifiedHandType::THREE_OF_A_KIND:
			result = this->handHasCardsWithEqualValues(hand, 3);
			break;

		case ClassifiedHandType::TWO_PAIRS:
			result = this->handHasCardsWithEqualValues(hand, 2, 2);
			break;

		case ClassifiedHandType::ONE_PAIR:
			result = this->handHasCardsWithEqualValues(hand, 2);
			break;

		default:
			break;
	}

	return result;
};

bool PokerFaceValidation::handHasSingleSuit (Hand hand) {
	bool handHasSingleSuit = true;

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		Card currentCard = hand[cardIndex];

		int nextCardIndex = cardIndex + 1;
		Card nextCard = hand[nextCardIndex];

		bool isValidNextCard = nextCardIndex < MAX_HAND_SIZE;
		bool cardsHaveSameSuit = nextCard.suit[0] == currentCard.suit[0];

		if (isValidNextCard && !cardsHaveSameSuit) {
			handHasSingleSuit = false;
		}
	}

	return handHasSingleSuit;
};

bool PokerFaceValidation::handHasSequentialCombination (Hand hand) {
	bool isSequentialCombination = true;

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		Card currentCard = hand[cardIndex];

		int nextCardIndex = cardIndex + 1;
		Card nextCard = hand[nextCardIndex];

		bool isValidNextCard = nextCardIndex < MAX_HAND_SIZE;
		bool areSequentialCards = nextCard.value - currentCard.value == 1;

		if (isValidNextCard && !areSequentialCards) {
			isSequentialCombination = false;
		}
	}

	return isSequentialCombination;
};
