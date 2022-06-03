#include <iomanip>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "poker-face.h"
#include "arrangement-list.h"
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

	PokerFace *pokerFace = new PokerFace(totalRounds, initialMoneyAmountPerParticipant);

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

	FILE *outputFile;
  outputFile = fopen("../data/output.txt", "wt");
	erroAssert(outputFile != NULL, "Failed to create output file.");

	Result result = pokerFace->finish();

	for (int roundIndex = 0; roundIndex < result.totalRounds; roundIndex++) {
		Item<RoundResult> roundResult = result.roundResults->findByKey(roundIndex);

		fprintf(outputFile, "%d %d %s\n", roundResult.model.winnersCount, roundResult.model.moneyPerWinner, roundResult.model.classifiedHandSlug.c_str());

		if (roundResult.model.winnersCount > 0) {
			for (int winnerIndex = 0; winnerIndex < roundResult.model.winnersCount; winnerIndex++) {
				fprintf(outputFile, "%s ", roundResult.model.winners[winnerIndex]);
			}

			fprintf(outputFile, "\n");
		}
	}

	fprintf(outputFile, "####\n");

	for (int balanceIndex = 0; balanceIndex < result.balanceResults->getSize(); balanceIndex++) {
		Item<Balance> balance = result.balanceResults->findByIndex(balanceIndex);

		fprintf(outputFile, "%s %d\n", balance.model.playerName, balance.model.money);
	}

	fclose(outputFile);
	
	return 0;
}