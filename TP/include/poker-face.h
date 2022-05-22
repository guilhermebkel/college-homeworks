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

#ifndef HAND_COMBINATION_SIZE 
#define HAND_COMBINATION_SIZE 2
#endif

typedef struct Play {
	char playerName[MAX_PLAYER_NAME_SIZE];
	int betAmount;
	char hand[MAX_HAND_SIZE][HAND_COMBINATION_SIZE];
} Play;

typedef struct Round {
	int participantsCount;
	int dropValue;
	Play plays[MAX_PLAYERS_COUNT];
} Round;

class PokerFace {
  public:
    PokerFace(int totalRounds, int initialMoneyAmountPerParticipant);
		void startRound(int participantsCount, int dropValue);
    void readPlay(char playerName[MAX_PLAYER_NAME_SIZE], int betAmount, char hand[MAX_HAND_SIZE][HAND_COMBINATION_SIZE]);
    void getResult();

	private:
    int totalRounds;
    int initialMoneyAmountPerParticipant;
		int currentRoundIndex;
		Round rounds[1000];
};

#endif