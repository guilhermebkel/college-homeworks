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

void PokerFace::readPlay (char playerName[50], int betAmount, char hand[2][MAX_HAND_SIZE]) {
	Play play;

	strcpy(play.playerName, playerName);
	play.betAmount = betAmount;
};

void PokerFace::getResult() {

};
