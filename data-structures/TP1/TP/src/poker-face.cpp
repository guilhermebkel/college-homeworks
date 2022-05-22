#include <iomanip>
#include <string.h>

#include "poker-face.h"

PokerFace::PokerFace (int totalRounds, int initialMoneyAmountPerParticipant) {
	this->currentRoundIndex = -1;

	this->totalRounds = totalRounds;
	this->initialMoneyAmountPerParticipant = initialMoneyAmountPerParticipant;
};

void PokerFace::startRound (int participantsCount, int dropValue) {
	Round round;

	round.participantsCount = participantsCount;
	round.dropValue = dropValue;
	round.currentPlayIndex = 0;
	
	this->currentRoundIndex++;
	this->rounds[currentRoundIndex] = round;
};

void PokerFace::readPlay (PlayerName playerName, int betAmount, Hand hand) {
	Play play;

	strcpy(play.playerName, playerName);
	play.betAmount = betAmount;

	/**
	 * Orders cards in ascending ordering by its value, in order to
	 * handle easily some business rules later.
	 */
	for (int i = 0; i < MAX_HAND_SIZE; i++) {
		for (int j = i + 1; j < MAX_HAND_SIZE; j++) {
			if (hand[i].value > hand[j].value) {
				Card auxCard = hand[i];

				hand[i] = hand[j];

				hand[j] = auxCard;
			}
		}
	}

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		play.hand[cardIndex] = hand[cardIndex];
	}

	Round currentRound = rounds[currentRoundIndex];

	this->rounds[currentRoundIndex].plays[currentRound.currentPlayIndex] = play;
	this->rounds[currentRoundIndex].currentPlayIndex++;
};

void PokerFace::getRoundResult(Round round) {
	for (int i = 0; i < round.participantsCount; i++) {
		Play currentPlay = round.plays[i];

		this->classifyHand(currentPlay.hand);
	}
};

void PokerFace::finish() {
	for (int roundIndex = 0; roundIndex < this->totalRounds; roundIndex++) {
		Round round = rounds[roundIndex];

		this->getRoundResult(round);
	}
};

ClassifiedHand PokerFace::classifyHand (Hand hand) {
	ClassifiedHand classifiedHand;

	classifiedHand.greaterCard = hand[MAX_HAND_SIZE - 1];

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		classifiedHand.hand[cardIndex] = hand[cardIndex];
	}

	if (this->isRoyalStraightFlushHand(hand)) {
		classifiedHand.type = "RSF";
		classifiedHand.value = 10;
	} else if (this->isStraightFlushHand(hand)) {
		classifiedHand.type = "SF";
		classifiedHand.value = 9;
	} else if (this->isFourOfAKindHand(hand)) {
		classifiedHand.type = "FK";
		classifiedHand.value = 8;
	} else if (this->isFullHouseHand(hand)) {
		classifiedHand.type = "FH";
		classifiedHand.value = 7;
	} else if (this->isFlushHand(hand)) {
		classifiedHand.type = "F";
		classifiedHand.value = 6;
	} else if (this->isStraightHand(hand)) {
		classifiedHand.type = "S";
		classifiedHand.value = 5;
	} else if (this->isThreeOfAKindHand(hand)) {
		classifiedHand.type = "TK";
		classifiedHand.value = 4;
	} else if (this->isTwoPairsHand(hand)) {
		classifiedHand.type = "TP";
		classifiedHand.value = 3;
	} else if (this->isOnePairHand(hand)) {
		classifiedHand.type = "OP";
		classifiedHand.value = 2;
	} else {
		classifiedHand.type = "HC";
		classifiedHand.value = 1;
	}

	return classifiedHand;
};

bool PokerFace::handHasSingleSuit (Hand hand) {
	bool handHasSingleSuit = true;

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		Card currentCard = hand[cardIndex];

		int nextCardIndex = cardIndex + 1;
		Card nextCard = hand[nextCardIndex];

		bool isValidNextCard = nextCardIndex < MAX_HAND_SIZE;
		bool cardsHaveSameSuit = nextCard.suit == currentCard.suit;

		if (isValidNextCard && !cardsHaveSameSuit) {
			handHasSingleSuit = false;
		}
	}

	return handHasSingleSuit;
};

bool PokerFace::isStraightFlushHand (Hand hand) {
	bool hasSameSuit = handHasSingleSuit(hand);

	bool isSequentialCombination = true;

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		Card currentCard = hand[cardIndex];

		int nextCardIndex = cardIndex + 1;
		Card nextCard = hand[nextCardIndex];

		bool isValidNextCard = nextCardIndex < MAX_HAND_SIZE;
		bool areSequentialCards = currentCard.value - nextCard.value == 1;

		if (isValidNextCard && !areSequentialCards) {
			isSequentialCombination = false;
		}
	}

	bool result = hasSameSuit && isSequentialCombination;

	return result;
};

bool PokerFace::isRoyalStraightFlushHand (Hand hand) {
	bool hasSameSuit = handHasSingleSuit(hand);

	bool hasCorrectCombination = (hand[0].value == 1) && (hand[1].value == 10) && (hand[2].value == 11) && (hand[3].value == 12) && (hand[4].value == 13);

	bool result = hasSameSuit && hasCorrectCombination;

	return result;
};

bool PokerFace::isFourOfAKindHand (Hand hand) {
	int cardsWithSameValue = 0;

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		Card currentCard = hand[cardIndex];

		int nextCardIndex = cardIndex + 1;
		Card nextCard = hand[nextCardIndex];

		bool isValidNextCard = nextCardIndex < MAX_HAND_SIZE;
		bool cardsHasSameValue = currentCard.value == nextCard.value;

		if (isValidNextCard && cardsHasSameValue) {
			cardsWithSameValue++;
		}
	}

	bool result = cardsWithSameValue == 4;

	return result;
};

bool PokerFace::isFullHouseHand (Hand hand) {
	return false;
};

bool PokerFace::isFlushHand (Hand hand) {
	return false;
};

bool PokerFace::isStraightHand (Hand hand) {
	return false;
};

bool PokerFace::isThreeOfAKindHand (Hand hand) {
	return false;
};

bool PokerFace::isTwoPairsHand (Hand hand) {
	return false;
};

bool PokerFace::isOnePairHand (Hand hand) {
	return false;
};

bool PokerFace::isHighCardHand (Hand hand) {
	return false;
};
