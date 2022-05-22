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

typedef struct Play {
	char playerName[50];
	int betAmount;
	char hand[2][MAX_HAND_SIZE];
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
    void readPlay(char playerName[50], int betAmount, char hand[2][MAX_HAND_SIZE]);
    void getResult();

	private:
    int totalRounds;
    int initialMoneyAmountPerParticipant;
		int currentRoundIndex;
		Round rounds[1000];
};

#endif