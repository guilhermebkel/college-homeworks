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

	for (int handIndex = 0; handIndex < MAX_HAND_SIZE; handIndex++) {
		play.hand[handIndex] = hand[handIndex];
	}

	Round currentRound = rounds[currentRoundIndex];

	this->rounds[currentRoundIndex].plays[currentRound.currentPlayIndex] = play;
	this->rounds[currentRoundIndex].currentPlayIndex++;
};

void PokerFace::getResult() {
	Round round = rounds[0];

	for (int i = 0; i < round.participantsCount; i++) {
		Play currentPlay = round.plays[i];

		this->classifyHand(currentPlay.hand);
	}
};

ClassifiedHand PokerFace::classifyHand (Hand hand) {
	ClassifiedHand classifiedHand;

	bool isRoyalStraightFlushHand = this->isRoyalStraightFlushHand(hand);

	return classifiedHand;
};

bool PokerFace::handHasSingleSuit (Hand hand) {
	return (hand[0].suit == hand[1].suit) && (hand[1].suit == hand[2].suit) && (hand[2].suit == hand[3].suit) && (hand[3].suit == hand[4].suit) && (hand[4].suit == hand[5].suit);
}

bool PokerFace::isStraightFlushHand (Hand hand) {
	bool hasSameSuit = handHasSingleSuit(hand);

	for (int i = 0; i < MAX_HAND_SIZE; i++) {
		for (int j = i + 1; j < MAX_HAND_SIZE; j++) {
			if (hand[i].value > hand[j].value) {
				Card auxCard = hand[i];

				hand[i] = hand[j];

				hand[j] = auxCard;
			}
		}
	}

	bool isSequentialCombination = true;

	for (int i = 0; i < MAX_HAND_SIZE; i++) {
		if (hand[i].value - hand[i + 1].value > 1) {
			isSequentialCombination = false;
		}
	}

	bool result = hasSameSuit && isSequentialCombination;

	return result;
};

bool PokerFace::isRoyalStraightFlushHand (Hand hand) {
	bool hasSameSuit = handHasSingleSuit(hand);

	for (int i = 0; i < MAX_HAND_SIZE; i++) {
		for (int j = i + 1; j < MAX_HAND_SIZE; j++) {
			if (hand[i].value > hand[j].value) {
				Card auxCard = hand[i];

				hand[i] = hand[j];

				hand[j] = auxCard;
			}
		}
	}

	bool hasCorrectCombination = (hand[0].value == 1) && (hand[1].value == 10) && (hand[2].value == 11) && (hand[3].value == 12) && (hand[4].value == 13);

	bool result = hasSameSuit && hasCorrectCombination;

	return result;
};
