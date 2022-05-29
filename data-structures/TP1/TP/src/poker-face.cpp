#include <iomanip>
#include <string.h>
#include <algorithm>

#include "poker-face.h"
#include "msgassert.h"

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

	Round currentRound = rounds[currentRoundIndex];

	erroAssert(betAmount >= currentRound.dropValue, "Bet amount must be greater than round drop value.");

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

	this->rounds[currentRoundIndex].plays[currentRound.currentPlayIndex] = play;
	this->rounds[currentRoundIndex].currentPlayIndex++;
};

RoundResult PokerFace::getRoundResult(Round round) {
	RoundResult roundResult;

	std::string roundClassifiedHandSlug;
	int roundClassifiedHandType;
	int totalRoundMoney = 0;

	RoundWinner roundWinners[round.participantsCount];
	int winnersCount = 1;

	int greatestHandScore = 0;

	for (int participantIndex = 0; participantIndex < round.participantsCount; participantIndex++) {
		Play currentPlay = round.plays[participantIndex];

		ClassifiedHand classifiedHand = this->classifyHand(currentPlay.hand);

		if (classifiedHand.score > greatestHandScore) {
			roundClassifiedHandSlug = classifiedHand.slug;
			roundClassifiedHandType = classifiedHand.type;
			
			RoundWinner roundWinner;
			roundWinner.classifiedHand = classifiedHand;
			roundWinner.play = currentPlay;
			roundWinner.participantIndex = participantIndex;

			roundWinners[0] = roundWinner;

			greatestHandScore = classifiedHand.score;
		}

		totalRoundMoney += currentPlay.betAmount;
	}

	for (int participantIndex = 0; participantIndex < round.participantsCount; participantIndex++) {
		RoundWinner currentWinner = roundWinners[0];

		if (currentWinner.participantIndex != participantIndex) {
			Play possibleWinnerPlay = round.plays[participantIndex];
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
					winnersCount++;
					roundWinners[winnersCount - 1] = roundWinner;
				}
			}
		}
	}

	for (int winnerIndex = 0; winnerIndex < winnersCount; winnerIndex++) {
		strcpy(roundResult.winners[winnerIndex], roundWinners[winnerIndex].play.playerName);
	}

	roundResult.round = round;
	roundResult.classifiedHandSlug = roundClassifiedHandSlug;
	roundResult.classifiedHandType = roundClassifiedHandType;
	roundResult.winnersCount = winnersCount;
	roundResult.moneyPerWinner = totalRoundMoney/winnersCount;

	return roundResult;
};

Result PokerFace::finish() {
	Result result;

	for (int roundIndex = 0; roundIndex < this->totalRounds; roundIndex++) {
		Round round = rounds[roundIndex];

		RoundResult roundResult = this->getRoundResult(round);
		result.roundResults[roundIndex] = roundResult;

		result.totalRounds = this->totalRounds;
	}

	return result;
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

	CardCombo cardComboGroups[MAX_HAND_SIZE];

	for (int i = 0; i < MAX_HAND_SIZE; i++) {
		cardComboGroups[i].totalCards = 1;
		cardComboGroups[i].cards[0] = hand[i];

		for (int j = i + 1; j < MAX_HAND_SIZE; j++) {
			Card currentCard = hand[i];
			Card comparedCard = hand[j];

			if (currentCard.value == comparedCard.value) {
				cardComboGroups[i].totalCards++;
				cardComboGroups[i].cards[cardComboGroups[i].totalCards] = hand[j];
			}
		}
	}

	/**
	 * Orders cards in descending ordering by amount of equal cards, in order to
	 * handle easily some business rules later.
	 */
	for (int i = 0; i < MAX_HAND_SIZE; i++) {
		for (int j = i + 1; j < MAX_HAND_SIZE; j++) {
			if (cardComboGroups[i].totalCards < cardComboGroups[j].totalCards) {
				CardCombo equalCardValue = cardComboGroups[i];

				cardComboGroups[i] = cardComboGroups[j];
				cardComboGroups[j] = equalCardValue;
			}
		}
	}

	groupedCardCombo.group1 = cardComboGroups[0];
	groupedCardCombo.group2 = cardComboGroups[1];
	groupedCardCombo.group3 = cardComboGroups[2];
	groupedCardCombo.group4 = cardComboGroups[3];
	groupedCardCombo.group5 = cardComboGroups[4];

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
