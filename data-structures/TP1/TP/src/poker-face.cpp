#include <iostream>
#include <string.h>

#include "poker-face.h"
#include "poker-face-util.h"
#include "msgassert.h"
#include "arrangement-list.h"

PokerFaceUtil *pokerFaceUtil = new PokerFaceUtil();

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
	this->rounds->save(currentRoundIndex, round);
};

void PokerFace::readPlay (PlayerName playerName, int betAmount, Hand hand) {
	erroAssert(!finished, "Game already ended.");

	Play play;

	Round currentRound = this->rounds->findByKey(currentRoundIndex);

	strcpy(play.playerName, playerName);
	play.betAmount = betAmount;

	ArrangementList<Card> *cards = new ArrangementList<Card>();
	cards->save(0, hand[0]);
	cards->save(1, hand[1]);
	cards->save(2, hand[2]);
	cards->save(3, hand[3]);
	cards->save(4, hand[4]);

	/**
	 * Orders cards in ascending ordering by its value, in order to
	 * handle easily some business rules later.
	 */
	cards->sort(SortingType::ASC, &getCardSortingParam);

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		play.hand[cardIndex] = cards->findByIndex(cardIndex);
	}

	currentRound.plays->save(playerName, play);
	currentRound.currentPlayIndex++;

	this->rounds->save(currentRoundIndex, currentRound);
};

RoundResult PokerFace::consolidateRoundResult(Round round) {
	RoundResult roundResult;

	int totalRoundMoney = 0;

	RoundWinner roundWinners[round.participantsCount];
	roundResult.winnersCount = 0;
	roundResult.moneyPerWinner = 0;
	roundResult.round = round;

	int greatestHandScore = 0;

	for (int participantIndex = 0; participantIndex < round.participantsCount; participantIndex++) {
		Play currentPlay = round.plays->findByIndex(participantIndex);

		if (!this->balances->existsByKey(currentPlay.playerName)) {
			Balance balance;
			balance.money = INITIAL_PLAYER_MONEY;
			strcpy(balance.playerName, currentPlay.playerName);

			this->balances->save(currentPlay.playerName, balance);
		}
	}

	for (int participantIndex = 0; participantIndex < round.participantsCount; participantIndex++) {
		Play currentPlay = round.plays->findByIndex(participantIndex);

		bool isPlayerTryingToBetAValueBelowDropValue = currentPlay.betAmount < round.dropValue;
		bool isInvalidPlay = isPlayerTryingToBetAValueBelowDropValue;

		if (isInvalidPlay) {
			roundResult.classifiedHandSlug = "I";

			return roundResult;
		}
	}

	for (int participantIndex = 0; participantIndex < round.participantsCount; participantIndex++) {
		Play currentPlay = round.plays->findByIndex(participantIndex);

		ClassifiedHand classifiedHand = pokerFaceUtil->classifyHand(currentPlay.hand);

		if (classifiedHand.score > greatestHandScore) {
			roundResult.classifiedHandSlug = classifiedHand.slug;
			
			RoundWinner roundWinner;
			roundWinner.classifiedHand = classifiedHand;
			roundWinner.play = currentPlay;
			roundWinner.participantIndex = participantIndex;

			roundWinners[0] = roundWinner;

			greatestHandScore = classifiedHand.score;
		}

		totalRoundMoney += currentPlay.betAmount;

		Balance playerBalance = this->balances->findByKey(currentPlay.playerName);
		playerBalance.money -= currentPlay.betAmount;
		this->balances->save(currentPlay.playerName, playerBalance);
	}

	roundResult.winnersCount++;

	for (int participantIndex = 0; participantIndex < round.participantsCount; participantIndex++) {
		RoundWinner currentWinner = roundWinners[0];

		if (currentWinner.participantIndex != participantIndex) {
			Play possibleWinnerPlay = round.plays->findByIndex(participantIndex);
			ClassifiedHand possibleWinnerClassifiedHand = pokerFaceUtil->classifyHand(possibleWinnerPlay.hand);

			bool isTie = possibleWinnerClassifiedHand.score == currentWinner.classifiedHand.score;

			if (isTie) {
				Card currentWinnerGreaterCard = pokerFaceUtil->getGreaterCard(currentWinner.play.hand);
				GroupedCardCombo currentWinnerGroupedCardCombo = pokerFaceUtil->groupCardsWithEqualValues(currentWinner.play.hand);

				Card possibleWinnerGreaterCard = pokerFaceUtil->getGreaterCard(possibleWinnerPlay.hand);
				GroupedCardCombo possibleWinnerGroupedCardCombo = pokerFaceUtil->groupCardsWithEqualValues(possibleWinnerPlay.hand);

				RoundWinner roundWinner;
				roundWinner.classifiedHand = possibleWinnerClassifiedHand;
				roundWinner.play = possibleWinnerPlay;
				roundWinner.participantIndex = participantIndex;

				bool overwriteWinner = false;
				bool addWinner = false;

				int possibleWinnerFirstCardComboScore = pokerFaceUtil->getCardComboScore(currentWinnerGroupedCardCombo.group1);
				int currentWinnerFirstCardComboScore = pokerFaceUtil->getCardComboScore(currentWinnerGroupedCardCombo.group1);
				int possibleWinnerSecondCardComboScore = pokerFaceUtil->getCardComboScore(currentWinnerGroupedCardCombo.group2);
				int currentWinnerSecondCardComboScore = pokerFaceUtil->getCardComboScore(currentWinnerGroupedCardCombo.group2);

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

				if (overwriteWinner) {
					roundWinners[0] = roundWinner;
				}

				if (addWinner) {
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

			Balance selectedWinnerBalance = this->balances->findByKey(selectedWinner);
			selectedWinnerBalance.money += roundResult.moneyPerWinner;

			this->balances->save(selectedWinner, selectedWinnerBalance);
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
		Round round = this->rounds->findByKey(roundIndex);

		RoundResult roundResult = this->consolidateRoundResult(round);
		this->result.roundResults->save(roundIndex, roundResult);

		this->result.totalRounds = this->totalRounds;
	}

	this->result.balanceResults->sort(SortingType::DESC, &getBalanceSortingParam);

	this->finished = true;

	return this->result;
};
