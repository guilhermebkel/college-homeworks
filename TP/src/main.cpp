#include <iomanip>
#include <stdlib.h>

#include "poker-face.h"

using namespace std;
 
int main() {
	FILE *inputFile;
  inputFile = fopen ("../../inputs/input.txt", "r");

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
			std::string playerName;
			int betAmount;
			std::string hand[MAX_HAND_SIZE];

			fscanf(inputFile, "%s ", &playerName);
  		fscanf(inputFile, "%d ", &betAmount);

			for (int playerHandIndex = 0; playerHandIndex < MAX_HAND_SIZE; playerHandIndex++) {
				fscanf(inputFile, "%s ", &hand[playerHandIndex]);
			}

			pokerFace->readPlay(playerName, betAmount, hand);
		}
	}

	fclose(inputFile);
	
	return 0;
}