#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fractal.h"

char* expandFractal(char axiom[], char rule[], int stages) {
	int axiomLength = strlen(axiom);
	int ruleLength = strlen(rule);

	char* finalExpandedFractal = (char*) malloc((axiomLength + 1) * sizeof(char));
	strcpy(finalExpandedFractal, axiom);

	for (int stage = 0; stage < stages; stage++) {
		int finalExpandedFractalLength = strlen(finalExpandedFractal);
		int stageExpandedFractalLength = finalExpandedFractalLength * ruleLength;

		char* stageExpandedFractal = (char*) malloc((stageExpandedFractalLength + 1) * sizeof(char));
		stageExpandedFractal[0] = '\0';

		for (int characterIndex = 0; characterIndex < finalExpandedFractalLength; characterIndex++) {
			char axiomCharacter = finalExpandedFractal[characterIndex];

			if (axiomCharacter == 'F') {
				strcat(stageExpandedFractal, rule);
			} else {
				strncat(stageExpandedFractal, &axiomCharacter, 1);
			}
		}

		free(finalExpandedFractal);
		finalExpandedFractal = stageExpandedFractal;
	}

	return finalExpandedFractal;
}
