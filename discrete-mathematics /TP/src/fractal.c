#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fractal.h"

char* expandFractalAxiom(FractalAxiom axiom, FractalRule rules[], FractalStage stages) {
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

void generateFractalAxiomPlotDescription(FractalAxiom axiom) {
	FILE* outputFile = fopen("./output/fractal_axiom_plot_description.gp", "w");

	fprintf(outputFile, "set terminal png\n");
	fprintf(outputFile, "set output './output/fractal.png'\n");
	fprintf(outputFile, "set xrange [-10:10]\n");
	fprintf(outputFile, "set yrange [-10:10]\n");
	fprintf(outputFile, "unset key\n");

	double x = 0.0;
	double y = 0.0;
	double angle = 0.0;
	double stepSize = 1.0;

	for (int i = 0; axiom[i] != '\0'; i++) {
		char character = axiom[i];

		if (character == 'F') {
			double xDest = x + stepSize * cos(angle);
			double yDest = y + stepSize * sin(angle);

			double a = (y / x) || 0;
			double b = y - (a * x);

			fprintf(outputFile, "plot [%lf:%lf] [%lf:%lf] %lf*x + %lf\n", x, xDest, y, yDest, a, b);

			x = xDest;
			y = yDest;
		} else if (character == '+') {
			angle += M_PI / 3.0;
		} else if (character == '-') {
			angle -= M_PI / 3.0;
		}
	}

	fclose(outputFile);
};
