#ifndef POKER_FACE_H
#define POKER_FACE_H

#include <iostream>
#include <string>

#ifndef MAX_HAND_SIZE 
#define MAX_HAND_SIZE 5
#endif

#ifndef MAX_PLAYERS_COUNT 
#define MAX_PLAYERS_COUNT 8
#endif

#ifndef MAX_PLAYER_NAME_SIZE 
#define MAX_PLAYER_NAME_SIZE 50
#endif

typedef struct Card {
	int value;
	char suit[1];
} Card;

typedef Card Hand[MAX_HAND_SIZE];

typedef char PlayerName[MAX_PLAYER_NAME_SIZE];

enum ClassifiedHandType {
	ROYAL_STRAIGHT_FLUSH = 10,
	STRAIGHT_FLUSH = 9,
	FOUR_OF_A_KIND = 8,
	FULL_HOUSE = 7,
	FLUSH = 6,
	STRAIGHT = 5,
	THREE_OF_A_KIND = 4,
	TWO_PAIRS = 3,
	ONE_PAIR = 2,
	HIGH_CARD = 1
};

typedef struct ClassifiedHand {
	int score;
	int type;
	std::string slug;
	Hand hand;
} ClassifiedHand;

typedef struct Play {
	PlayerName playerName;
	int betAmount;
	Hand hand;
} Play;

typedef struct Round {
	int participantsCount;
	int dropValue;
	Play plays[MAX_PLAYERS_COUNT];
	int currentPlayIndex;
} Round;

typedef struct RoundWinner {
	ClassifiedHand classifiedHand;
	Play play;
	int participantIndex;
} RoundWinner;

typedef struct RoundResult {
	Round round;
	PlayerName winners[MAX_PLAYERS_COUNT];
	int winnersCount;
	std::string classifiedHandSlug;
	int classifiedHandType;
	int moneyPerWinner;
} RoundResult;

typedef struct Balance {
	PlayerName playerName;
	int money;
} Balance;

typedef struct Result {
	RoundResult roundResults[1000];
	Balance balanceResults[MAX_PLAYERS_COUNT];
	int totalRounds;
} Result;

typedef struct CardCombo {
	Hand cards;
	int totalCards;
} CardCombo;

typedef struct GroupedCardCombo {
	CardCombo group1;
	CardCombo group2;
	CardCombo group3;
	CardCombo group4;
	CardCombo group5;
} GroupedCardCombo;

class PokerFace {
  public:
    PokerFace(int totalRounds, int initialMoneyAmountPerParticipant);
		void startRound(int participantsCount, int dropValue);
    void readPlay(PlayerName playerName, int betAmount, Hand hand);
    Result finish();

	private:
		ClassifiedHand classifyHand (Hand hand);
		RoundResult getRoundResult (Round round);
		bool handHasSingleSuit (Hand hand);
		GroupedCardCombo groupCardsWithEqualValues (Hand hand);
		bool handHasCardsWithEqualValues (Hand hand, int group1, int group2, int group3, int group4, int group5);
		bool handHasSequentialCombination (Hand hand);
		bool isClassifiedHand (Hand hand, ClassifiedHandType classifiedHandType);
    int totalRounds;
    int initialMoneyAmountPerParticipant;
		int currentRoundIndex;
		Round rounds[1000];
};

#endif