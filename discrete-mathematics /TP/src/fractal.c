#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fractal.h"
#include "shared-utils.h"

char* expandFractalAxiom (FractalAxiom axiom, FractalRule rules[], FractalStage stages) {
	int axiomLength = strlen(axiom);
	char* finalExpandedFractalAxiom = createEmptyString(axiomLength + 1);
	strcpy(finalExpandedFractalAxiom, axiom);

	for (int stage = 0; stage < stages; stage++) {
		int finalExpandedFractalAxiomLength = strlen(finalExpandedFractalAxiom);
		int stageExpandedFractalAxiomLength = finalExpandedFractalAxiomLength * MAX_RULE_SIZE;
		char* stageExpandedFractalAxiom = createEmptyString(stageExpandedFractalAxiomLength + 1);

		for (int characterIndex = 0; characterIndex < finalExpandedFractalAxiomLength; characterIndex++) {
			char axiomCharacter = finalExpandedFractalAxiom[characterIndex];

			char* rule = getCharacterRule(axiomCharacter, rules);

			if (isValidString(rule)) {
				strcat(stageExpandedFractalAxiom, rule);
			} else {
				strncat(stageExpandedFractalAxiom, &axiomCharacter, 1);
			}
		}

		free(finalExpandedFractalAxiom);
		finalExpandedFractalAxiom = stageExpandedFractalAxiom;
	}

	return finalExpandedFractalAxiom;
}

char* getCharacterRule (char character, FractalRule rules[]) {
	int i = 0;

	while (isValidCharacter(rules[i].key)) {
		char key = rules[i].key;
		char* value = rules[i].value;

		if (key == character) {
			return value;
		}

		i++;
	}

	return "";
};
