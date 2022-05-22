#include <iomanip>
#include <string.h>

#include "poker-face.h"

PokerFace::PokerFace (int totalRounds, int initialMoneyAmountPerParticipant) {
	currentRoundIndex = -1;

	this->totalRounds = totalRounds;
	this->initialMoneyAmountPerParticipant = initialMoneyAmountPerParticipant;
};

void PokerFace::startRound (int participantsCount, int dropValue) {
	Round round;

	round.participantsCount = participantsCount;
	round.dropValue = dropValue;
	
	currentRoundIndex++;

	rounds[currentRoundIndex] = round;
};

void PokerFace::readPlay (char playerName[MAX_PLAYER_NAME_SIZE], int betAmount, char hand[MAX_HAND_SIZE][CARD_NAME_SIZE]) {
	Play play;

	strcpy(play.playerName, playerName);
	play.betAmount = betAmount;
	
	for (int handIndex = 0; handIndex < MAX_HAND_SIZE; handIndex++) {
		strcpy(play.hand[handIndex], hand[handIndex]);
	}
};

void PokerFace::getResult() {

};
