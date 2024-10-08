#include <iostream>
#include <string.h>

#include "poker-face.h"
#include "poker-face-validation.h"
#include "poker-face-util.h"
#include "msgassert.h"
#include "arrangement-list.h"

PokerFace::PokerFace (int totalRounds, int initialMoneyAmountPerParticipant) {
	this->currentRoundIndex = -1;

	this->totalRounds = totalRounds;
	this->initialMoneyAmountPerParticipant = initialMoneyAmountPerParticipant;
	this->finished = false;

	this->rounds = new ArrangementList<Round>();
	this->balances = new ArrangementList<Balance>();
};

void PokerFace::startRound (int participantsCount, int dropValue) {
	erroAssert(!finished, "Game already ended.");

	Round round;

	round.participantsCount = participantsCount;
	round.dropValue = dropValue;
	round.currentPlayIndex = 0;
	round.plays = new ArrangementList<Play>();
	
	this->currentRoundIndex++;
	this->rounds->create(currentRoundIndex, round);
};

void PokerFace::readPlay (PlayerName playerName, int betAmount, Hand hand) {
	erroAssert(!finished, "Game already ended.");

	Play play;

	Item<Round> currentRound = this->rounds->findByKey(currentRoundIndex);

	strcpy(play.playerName, playerName);
	play.betAmount = betAmount;

	ArrangementList<Card> *cards = new ArrangementList<Card>();

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		cards->create(cardIndex, hand[cardIndex]);
	}

	/**
	 * Orders cards in ascending ordering by its value, in order to
	 * handle easily some business rules later.
	 */
	cards->sort(SortingType::ASC, &getCardSortingParam);

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		play.hand[cardIndex] = cards->findByIndex(cardIndex).model;
	}

	currentRound.model.plays->create(playerName, play);
	currentRound.model.currentPlayIndex++;

	if (!this->balances->existsByKey(playerName)) {
		Balance balance;
		balance.money = INITIAL_PLAYER_MONEY;
		strcpy(balance.playerName, playerName);

		this->balances->create(playerName, balance);
	}

	this->rounds->update(currentRound.key, currentRound.model);
};

RoundResult PokerFace::consolidateRoundResult(Round round) {
	RoundResult roundResult;

	int totalRoundMoney = 0;

	RoundWinner roundWinners[round.participantsCount];
	roundResult.winnersCount = 0;
	roundResult.moneyPerWinner = 0;
	roundResult.round = round;

	int greatestHandScore = 0;

	if (isInvalidPlay(round, this->balances)) {
		roundResult.classifiedHandSlug = "I";

		return roundResult;
	}

	for (int balanceIndex = 0; balanceIndex < this->balances->getSize(); balanceIndex++) {
		totalRoundMoney += round.dropValue;

		Item<Balance> playerBalance = this->balances->findByIndex(balanceIndex);
		playerBalance.model.money -= round.dropValue;

		this->balances->update(playerBalance.key, playerBalance.model);
	}

	for (int participantIndex = 0; participantIndex < round.participantsCount; participantIndex++) {
		Item<Play> currentPlay = round.plays->findByIndex(participantIndex);

		ClassifiedHand classifiedHand = classifyHand(currentPlay.model.hand);

		if (classifiedHand.score > greatestHandScore) {
			roundResult.classifiedHandSlug = classifiedHand.slug;
			
			RoundWinner roundWinner;
			roundWinner.classifiedHand = classifiedHand;
			roundWinner.play = currentPlay.model;
			roundWinner.participantIndex = participantIndex;

			roundWinners[0] = roundWinner;

			greatestHandScore = classifiedHand.score;
		}

		totalRoundMoney += currentPlay.model.betAmount;

		Item<Balance> playerBalance = this->balances->findByKey(currentPlay.model.playerName);
		playerBalance.model.money -= currentPlay.model.betAmount;

		this->balances->update(playerBalance.key, playerBalance.model);
	}

	roundResult.winnersCount++;

	for (int participantIndex = 0; participantIndex < round.participantsCount; participantIndex++) {
		RoundWinner currentWinner = roundWinners[0];

		if (currentWinner.participantIndex != participantIndex) {
			Item<Play> possibleWinnerPlay = round.plays->findByIndex(participantIndex);
			ClassifiedHand possibleWinnerClassifiedHand = classifyHand(possibleWinnerPlay.model.hand);

			TieResult tieResult = assertTie(currentWinner, possibleWinnerPlay.model);

			if (tieResult != TieResult::NO_TIE_FOUND) {
				RoundWinner roundWinner;
				roundWinner.classifiedHand = possibleWinnerClassifiedHand;
				roundWinner.play = possibleWinnerPlay.model;
				roundWinner.participantIndex = participantIndex;

				if (tieResult == TieResult::OVERWRITE_WINNER) {
					roundWinners[0] = roundWinner;
				}

				if (tieResult == TieResult::ADD_WINNER) {
					roundResult.winnersCount++;
					roundWinners[roundResult.winnersCount - 1] = roundWinner;
				}
			}
		}
	}

	for (int winnerIndex = 0; winnerIndex < roundResult.winnersCount; winnerIndex++) {
		strcpy(roundResult.winners[winnerIndex], roundWinners[winnerIndex].play.playerName);
	}

	bool isThereAnyWinner = roundResult.winnersCount > 0;

	if (isThereAnyWinner) {
		roundResult.moneyPerWinner = totalRoundMoney / roundResult.winnersCount;
		
		for (int winnerIndex = 0; winnerIndex < roundResult.winnersCount; winnerIndex++) {
			PlayerName selectedWinner;
			
			strcpy(selectedWinner, roundResult.winners[winnerIndex]);

			Item<Balance> selectedWinnerBalance = this->balances->findByKey(selectedWinner);
			selectedWinnerBalance.model.money += roundResult.moneyPerWinner;

			this->balances->update(selectedWinnerBalance.key, selectedWinnerBalance.model);
		}
	}

	return roundResult;
};

Result PokerFace::finish() {
	if (finished) {
		return this->result;
	}

	this->result.roundResults = new ArrangementList<RoundResult>();
	this->result.balanceResults = this->balances;

	for (int roundIndex = 0; roundIndex < this->rounds->getSize(); roundIndex++) {
		Item<Round> round = this->rounds->findByKey(roundIndex);

		RoundResult roundResult = this->consolidateRoundResult(round.model);
		this->result.roundResults->create(roundIndex, roundResult);

		this->result.totalRounds = this->totalRounds;
	}

	this->result.balanceResults->sort(SortingType::DESC, &getBalanceSortingParam);

	this->finished = true;

	return this->result;
};
