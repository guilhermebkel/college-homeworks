#include <iomanip>
#include <string>

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

void PokerFace::readPlay (std::string playerName, int betAmount, std::string hand[MAX_HAND_SIZE]) {
	Play play;

	play.playerName = playerName;
	play.betAmount = betAmount;
};

void PokerFace::getResult() {

};
