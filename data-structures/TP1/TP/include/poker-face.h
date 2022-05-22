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

typedef struct ClassifiedHand {
	int value;
	std::string type;
	Hand hand;
	Card greaterCard;
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

class PokerFace {
  public:
    PokerFace(int totalRounds, int initialMoneyAmountPerParticipant);
		void startRound(int participantsCount, int dropValue);
    void readPlay(PlayerName playerName, int betAmount, Hand hand);
    void finish();

	private:
		ClassifiedHand classifyHand (Hand hand);
		void getRoundResult (Round round);
		bool handHasSingleSuit (Hand hand);
		bool handHasCardsWithEqualValues (Hand hand, int group1, int group2, int group3, int group4, int group5);
		bool handHasSequentialCombination (Hand hand);
		bool isRoyalStraightFlushHand (Hand hand);
		bool isStraightFlushHand (Hand hand);
		bool isFourOfAKindHand (Hand hand);
		bool isFullHouseHand (Hand hand);
		bool isFlushHand (Hand hand);
		bool isStraightHand (Hand hand);
		bool isThreeOfAKindHand (Hand hand);
		bool isTwoPairsHand (Hand hand);
		bool isOnePairHand (Hand hand);
    int totalRounds;
    int initialMoneyAmountPerParticipant;
		int currentRoundIndex;
		Round rounds[1000];
};

#endif