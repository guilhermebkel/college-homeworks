#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fractal.h"

char* expandFractal(FractalAxiom axiom, FractalRule rules[], int stages) {
	int axiomLength = strlen(axiom);

	char* finalExpandedFractal = (char*) malloc((axiomLength + 1) * sizeof(char));
	strcpy(finalExpandedFractal, axiom);

	for (int stage = 0; stage < stages; stage++) {
		int finalExpandedFractalLength = strlen(finalExpandedFractal);
		int stageExpandedFractalLength = finalExpandedFractalLength * MAX_RULE_SIZE;

		char* stageExpandedFractal = (char*) malloc((stageExpandedFractalLength + 1) * sizeof(char));
		stageExpandedFractal[0] = '\0';

		for (int characterIndex = 0; characterIndex < finalExpandedFractalLength; characterIndex++) {
			char axiomCharacter = finalExpandedFractal[characterIndex];

			char* rule = getRuleByCharacter(axiomCharacter, rules);

			if (strlen(rule) > 0) {
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

char* getRuleByCharacter (char character, FractalRule rules[]) {
	int i = 0;

	while (rules[i].key != '\0') {
		char key = rules[i].key;
		char* value = rules[i].value;

		if (key == character) {
				return value;
		}

		i++;
	}

	return "";
};
