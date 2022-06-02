#include <iomanip>
#include <iostream>
#include <string.h>
#include <algorithm>

#include "poker-face.h"
#include "msgassert.h"
#include "arrangement-list.h"

int getBalanceSortingParam (Balance balance) {
	return balance.money;
};

int getCardComboSortingParam (CardCombo cardCombo) {
	return cardCombo.totalCards;
};

int getCardSortingParam (Card card) {
	return card.value;
};

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

		ClassifiedHand classifiedHand = this->classifyHand(currentPlay.hand);

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
			ClassifiedHand possibleWinnerClassifiedHand = this->classifyHand(possibleWinnerPlay.hand);

			bool isTie = possibleWinnerClassifiedHand.score == currentWinner.classifiedHand.score;

			if (isTie) {
				Card currentWinnerGreaterCard = this->getGreaterCard(currentWinner.play.hand);
				GroupedCardCombo currentWinnerGroupedCardCombo = this->groupCardsWithEqualValues(currentWinner.play.hand);

				Card possibleWinnerGreaterCard = this->getGreaterCard(possibleWinnerPlay.hand);
				GroupedCardCombo possibleWinnerGroupedCardCombo = this->groupCardsWithEqualValues(possibleWinnerPlay.hand);

				RoundWinner roundWinner;
				roundWinner.classifiedHand = possibleWinnerClassifiedHand;
				roundWinner.play = possibleWinnerPlay;
				roundWinner.participantIndex = participantIndex;

				bool overwriteWinner = false;
				bool addWinner = false;

				int possibleWinnerFirstCardComboScore = this->getCardComboScore(currentWinnerGroupedCardCombo.group1);
				int currentWinnerFirstCardComboScore = this->getCardComboScore(currentWinnerGroupedCardCombo.group1);
				int possibleWinnerSecondCardComboScore = this->getCardComboScore(currentWinnerGroupedCardCombo.group2);
				int currentWinnerSecondCardComboScore = this->getCardComboScore(currentWinnerGroupedCardCombo.group2);

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

ClassifiedHand PokerFace::classifyHand (Hand hand) {
	ClassifiedHand classifiedHand;

	for (int cardIndex = 0; cardIndex < MAX_HAND_SIZE; cardIndex++) {
		classifiedHand.hand[cardIndex] = hand[cardIndex];
	}

	if (this->handHasClassificationType(hand, ClassifiedHandType::ROYAL_STRAIGHT_FLUSH)) {
		classifiedHand.type = ClassifiedHandType::ROYAL_STRAIGHT_FLUSH;
		classifiedHand.slug = "RSF";
		classifiedHand.score = 10;
	} else if (this->handHasClassificationType(hand, ClassifiedHandType::STRAIGHT_FLUSH)) {
		classifiedHand.type = ClassifiedHandType::STRAIGHT_FLUSH;
		classifiedHand.slug = "SF";
		classifiedHand.score = 9;
	} else if (this->handHasClassificationType(hand, ClassifiedHandType::FOUR_OF_A_KIND)) {
		classifiedHand.type = ClassifiedHandType::FOUR_OF_A_KIND;
		classifiedHand.slug = "FK";
		classifiedHand.score = 8;
	} else if (this->handHasClassificationType(hand, ClassifiedHandType::FULL_HOUSE)) {
		classifiedHand.type = ClassifiedHandType::FULL_HOUSE;
		classifiedHand.slug = "FH";
		classifiedHand.score = 7;
	} else if (this->handHasClassificationType(hand, ClassifiedHandType::FLUSH)) {
		classifiedHand.type = ClassifiedHandType::FLUSH;
		classifiedHand.slug = "F";
		classifiedHand.score = 6;
	} else if (this->handHasClassificationType(hand, ClassifiedHandType::STRAIGHT)) {
		classifiedHand.type = ClassifiedHandType::STRAIGHT;
		classifiedHand.slug = "S";
		classifiedHand.score = 5;
	} else if (this->handHasClassificationType(hand, ClassifiedHandType::THREE_OF_A_KIND)) {
		classifiedHand.type = ClassifiedHandType::THREE_OF_A_KIND;
		classifiedHand.slug = "TK";
		classifiedHand.score = 4;
	} else if (this->handHasClassificationType(hand, ClassifiedHandType::TWO_PAIRS)) {
		classifiedHand.type = ClassifiedHandType::TWO_PAIRS;
		classifiedHand.slug = "TP";
		classifiedHand.score = 3;
	} else if (this->handHasClassificationType(hand, ClassifiedHandType::ONE_PAIR)) {
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

bool PokerFace::handHasSingleSuit (Hand hand) {
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

bool PokerFace::handHasSequentialCombination (Hand hand) {
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
}

GroupedCardCombo PokerFace::groupCardsWithEqualValues (Hand hand) {
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

		cardComboGroups->save(i, cardCombo);
	}

	/**
	 * Orders cards in descending ordering by amount of equal cards, in order to
	 * handle easily some business rules later.
	 */
	cardComboGroups->sort(SortingType::DESC, &getCardComboSortingParam);

	groupedCardCombo.group1 = cardComboGroups->findByIndex(0);
	groupedCardCombo.group2 = cardComboGroups->findByIndex(1);
	groupedCardCombo.group3 = cardComboGroups->findByIndex(2);
	groupedCardCombo.group4 = cardComboGroups->findByIndex(3);
	groupedCardCombo.group5 = cardComboGroups->findByIndex(4);

	return groupedCardCombo;
}

bool PokerFace::handHasCardsWithEqualValues (Hand hand, int group1 = 1, int group2 = 1, int group3 = 1, int group4 = 1, int group5 = 1) {
	GroupedCardCombo groupedCardWithEqualValues = this->groupCardsWithEqualValues(hand);

	return (
		groupedCardWithEqualValues.group1.totalCards == group1 &&
		groupedCardWithEqualValues.group2.totalCards == group2 &&
		groupedCardWithEqualValues.group3.totalCards == group3 &&
		groupedCardWithEqualValues.group4.totalCards == group4 &&
		groupedCardWithEqualValues.group5.totalCards == group5
	);
}

bool PokerFace::handHasClassificationType (Hand hand, ClassifiedHandType classifiedHandType) {
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

int PokerFace::getCardComboScore (CardCombo cardCombo) {
	int score = 0;

	for (int i = 0; i < cardCombo.totalCards; i++) {
		score += cardCombo.cards[i].value;
	}

	return score;
};

Card PokerFace::getGreaterCard (Hand hand) {
	return hand[MAX_HAND_SIZE - 1];
};
