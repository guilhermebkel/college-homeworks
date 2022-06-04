#include "poker-face.h"
#include "poker-face-util.h"
#include "poker-face-validation.h"

int getBalanceSortingParam (Balance balance) {
	return balance.money;
};

int getCardComboSortingParam (CardCombo cardCombo) {
	return cardCombo.totalCards;
};

int getCardSortingParam (Card card) {
	return card.value;
};

GroupedCardCombo groupCardsWithEqualValues (Hand hand) {
	GroupedCardCombo groupedCardCombo;

	ArrangementList<CardCombo> *cardComboGroups = new ArrangementList<CardCombo>();

	for (int i = 0; i < MAX_HAND_SIZE; i++) {
		CardCombo cardCombo;

		cardCombo.totalCards = 1;
		cardCombo.cards[0] = hand[i];

		for (int j = i + 1; j < MAX_HAND_SIZE; j++) {
			Card currentCard = hand[i];
			Card comparedCard = hand[j];

			if (currentCard.value == comparedCard.value) {
				cardCombo.totalCards++;
				cardCombo.cards[cardCombo.totalCards] = hand[j];
			}
		}

		cardComboGroups->create(i, cardCombo);
	}

	/**
	 * Orders cards in descending ordering by amount of equal cards, in order to
	 * handle easily some business rules later.
	 */
	cardComboGroups->sort(SortingType::DESC, &getCardComboSortingParam);

	groupedCardCombo.group1 = cardComboGroups->findByIndex(0).model;
	groupedCardCombo.group2 = cardComboGroups->findByIndex(1).model;
	groupedCardCombo.group3 = cardComboGroups->findByIndex(2).model;
	groupedCardCombo.group4 = cardComboGroups->findByIndex(3).model;
	groupedCardCombo.group5 = cardComboGroups->findByIndex(4).model;

	return groupedCardCombo;
};

int getCardComboScore (CardCombo cardCombo) {
	int score = 0;

	for (int i = 0; i < cardCombo.totalCards; i++) {
		score += cardCombo.cards[i].value;
	}

	return score;
};

Card getGreaterCard (Hand hand) {
	return hand[MAX_HAND_SIZE - 1];
};

ClassifiedHand classifyHand (Hand hand) {
	ClassifiedHand classifiedHand;

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		classifiedHand.hand[cardIndex] = hand[cardIndex];
	}

	if (handHasClassificationType(hand, ClassifiedHandType::ROYAL_STRAIGHT_FLUSH)) {
		classifiedHand.type = ClassifiedHandType::ROYAL_STRAIGHT_FLUSH;
		classifiedHand.slug = "RSF";
		classifiedHand.score = 10;
	} else if (handHasClassificationType(hand, ClassifiedHandType::STRAIGHT_FLUSH)) {
		classifiedHand.type = ClassifiedHandType::STRAIGHT_FLUSH;
		classifiedHand.slug = "SF";
		classifiedHand.score = 9;
	} else if (handHasClassificationType(hand, ClassifiedHandType::FOUR_OF_A_KIND)) {
		classifiedHand.type = ClassifiedHandType::FOUR_OF_A_KIND;
		classifiedHand.slug = "FK";
		classifiedHand.score = 8;
	} else if (handHasClassificationType(hand, ClassifiedHandType::FULL_HOUSE)) {
		classifiedHand.type = ClassifiedHandType::FULL_HOUSE;
		classifiedHand.slug = "FH";
		classifiedHand.score = 7;
	} else if (handHasClassificationType(hand, ClassifiedHandType::FLUSH)) {
		classifiedHand.type = ClassifiedHandType::FLUSH;
		classifiedHand.slug = "F";
		classifiedHand.score = 6;
	} else if (handHasClassificationType(hand, ClassifiedHandType::STRAIGHT)) {
		classifiedHand.type = ClassifiedHandType::STRAIGHT;
		classifiedHand.slug = "S";
		classifiedHand.score = 5;
	} else if (handHasClassificationType(hand, ClassifiedHandType::THREE_OF_A_KIND)) {
		classifiedHand.type = ClassifiedHandType::THREE_OF_A_KIND;
		classifiedHand.slug = "TK";
		classifiedHand.score = 4;
	} else if (handHasClassificationType(hand, ClassifiedHandType::TWO_PAIRS)) {
		classifiedHand.type = ClassifiedHandType::TWO_PAIRS;
		classifiedHand.slug = "TP";
		classifiedHand.score = 3;
	} else if (handHasClassificationType(hand, ClassifiedHandType::ONE_PAIR)) {
		classifiedHand.type = ClassifiedHandType::ONE_PAIR;
		classifiedHand.slug = "OP";
		classifiedHand.score = 2;
	} else {
		classifiedHand.type = ClassifiedHandType::HIGH_CARD;
		classifiedHand.slug = "HC";
		classifiedHand.score = 1;
	}

	return classifiedHand;
};

TieResult assertTie (RoundWinner currentWinner, Play possibleWinnerPlay) {
	TieResult tieResult;

	ClassifiedHand possibleWinnerClassifiedHand = classifyHand(possibleWinnerPlay.hand);

	bool isTie = possibleWinnerClassifiedHand.score == currentWinner.classifiedHand.score;

	if (isTie) {
		Card currentWinnerGreaterCard = getGreaterCard(currentWinner.play.hand);
		GroupedCardCombo currentWinnerGroupedCardCombo = groupCardsWithEqualValues(currentWinner.play.hand);

		Card possibleWinnerGreaterCard = getGreaterCard(possibleWinnerPlay.hand);
		GroupedCardCombo possibleWinnerGroupedCardCombo = groupCardsWithEqualValues(possibleWinnerPlay.hand);

		bool overwriteWinner = false;
		bool addWinner = false;

		int possibleWinnerFirstCardComboScore = getCardComboScore(currentWinnerGroupedCardCombo.group1);
		int currentWinnerFirstCardComboScore = getCardComboScore(currentWinnerGroupedCardCombo.group1);
		int possibleWinnerSecondCardComboScore = getCardComboScore(currentWinnerGroupedCardCombo.group2);
		int currentWinnerSecondCardComboScore = getCardComboScore(currentWinnerGroupedCardCombo.group2);

		if (
			possibleWinnerClassifiedHand.type == ClassifiedHandType::FOUR_OF_A_KIND ||
			possibleWinnerClassifiedHand.type == ClassifiedHandType::THREE_OF_A_KIND ||
			possibleWinnerClassifiedHand.type == ClassifiedHandType::TWO_PAIRS ||
			possibleWinnerClassifiedHand.type == ClassifiedHandType::ONE_PAIR
		) {
			if (possibleWinnerFirstCardComboScore > currentWinnerFirstCardComboScore) {
				overwriteWinner = true;
			} else if (possibleWinnerGreaterCard.value > currentWinnerGreaterCard.value) {
				overwriteWinner = true;
			} else {
				addWinner = true;
			}
		}

		if (possibleWinnerClassifiedHand.type == ClassifiedHandType::FULL_HOUSE) {
			if (possibleWinnerFirstCardComboScore > currentWinnerFirstCardComboScore) {
				overwriteWinner = true;
			} else if (possibleWinnerSecondCardComboScore > currentWinnerSecondCardComboScore) {
				overwriteWinner = true;
			} else if (possibleWinnerGreaterCard.value > currentWinnerGreaterCard.value) {
				overwriteWinner = true;
			} else {
				addWinner = true;
			}
		}

		if (
			possibleWinnerClassifiedHand.type == ClassifiedHandType::STRAIGHT ||
			possibleWinnerClassifiedHand.type == ClassifiedHandType::FLUSH ||
			possibleWinnerClassifiedHand.type == ClassifiedHandType::HIGH_CARD
		) {
			if (possibleWinnerGreaterCard.value > currentWinnerGreaterCard.value) {
				overwriteWinner = true;
			} else {
				addWinner = true;
			}
		}
	} else {
		tieResult = TieResult::NO_TIE_FOUND;
	}

	return tieResult;
};
