#include <iomanip>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "poker-face.h"
#include "msgassert.h"

using namespace std;
 
int main() {
	FILE *inputFile;
  inputFile = fopen("../data/input.txt", "r");
	erroAssert(inputFile != NULL, "Input file was not found.");

	int totalRounds;
	int initialMoneyAmountPerParticipant;

	fscanf(inputFile, "%d ", &totalRounds);
  fscanf(inputFile, "%d ", &initialMoneyAmountPerParticipant);

	PokerFace *pokerFace;
	pokerFace = new PokerFace(totalRounds, initialMoneyAmountPerParticipant);

	for (int roundIndex = 0; roundIndex < totalRounds; roundIndex++) {
		int participantsCount;
		int dropValue;

		fscanf(inputFile, "%d ", &participantsCount);
  	fscanf(inputFile, "%d ", &dropValue);

		pokerFace->startRound(participantsCount, dropValue);

		for (int playerIndex = 0; playerIndex < participantsCount; playerIndex++) {
			PlayerName playerName;
			int betAmount;
			Hand hand;

			fscanf(inputFile, "%s ", playerName);
  		fscanf(inputFile, "%d ", &betAmount);

			for (int playerHandIndex = 0; playerHandIndex < MAX_HAND_SIZE; playerHandIndex++) {
				Card card;

				fscanf(inputFile, "%d%s ", &card.value, card.suit);

				hand[playerHandIndex] = card;
			}

			pokerFace->readPlay(playerName, betAmount, hand);
		}
	}

	fclose(inputFile);

	Result result = pokerFace->finish();

	for (int roundIndex = 0; roundIndex < result.totalRounds; roundIndex++) {
		RoundResult roundResult = result.roundResults[roundIndex];

		cout << roundResult.winnersCount << " " << roundResult.moneyPerWinner << " " << roundResult.classifiedHandType << endl;

		for (int winnerIndex = 0; winnerIndex < roundResult.winnersCount; winnerIndex++) {
			cout << roundResult.winners[winnerIndex];
		}

		cout << endl;
	}

	cout << "####" << endl;
	
	return 0;
}