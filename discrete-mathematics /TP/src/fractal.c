#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "fractal.h"
#include "fractal-file.h"
#include "shared-utils.h"
#include <SDL2/SDL.h>

void expandFractal (char* name, FractalAxiom axiom, FractalRule rules[], FractalStage stages) {
	generateInitialFractalStageFile(name, axiom);

	char* finalFractalStageFilePath = processFractalStagesOnDemand(name, axiom, rules, stages);

	char* finalFractalFilePath = processFinalFractal(name, finalFractalStageFilePath);

	showFractal(name, finalFractalFilePath);
}

void generateInitialFractalStageFile (char* name, FractalAxiom axiom) {
	char* initialFractalStageFilePath = mountFractalStageFilePath(name, 0);
	FILE* initialFractalStageFile = mountFile(initialFractalStageFilePath, "w");

	fprintf(initialFractalStageFile, "%s", axiom);

	fclose(initialFractalStageFile);
}

char* processFractalStagesOnDemand (char* name, FractalAxiom axiom, FractalRule rules[], FractalStage stages) {
	for (int stage = 0; stage < stages; stage++) {
		char* lastFractalStageFilePath = mountFractalStageFilePath(name, stage);
		FILE* lastFractalStageFile = mountFile(lastFractalStageFilePath, "r");

		char* currentFractalStageFilePath = mountFractalStageFilePath(name, stage + 1);
		FILE* currentFractalStageFile = mountFile(currentFractalStageFilePath, "w");

		char axiomCharacter;

		while ((axiomCharacter = fgetc(lastFractalStageFile)) != EOF) {
			char* rule = getCharacterRule(axiomCharacter, rules);
			if (isValidString(rule)) {
				fprintf(currentFractalStageFile, "%s", rule);
			} else {
				fprintf(currentFractalStageFile, "%c", axiomCharacter);
			}
		}

		fclose(lastFractalStageFile);
		fclose(currentFractalStageFile);
	}

	char* finalFractalStageFilePath = mountFractalStageFilePath(name, stages - 1);

	return finalFractalStageFilePath;
}

char* processFinalFractal (char* name, char* finalFractalStageFilePath) {
	FILE* finalFractalStageFile = mountFile(finalFractalStageFilePath, "r");

	char* finalFractalFilePath = mountFinalFractalFilePath(name);
	FILE* finalFractalFile = mountFile(finalFractalFilePath, "w");

	char axiomCharacter;

	while ((axiomCharacter = fgetc(finalFractalStageFile)) != EOF) {
		if (axiomCharacter == 'F' || axiomCharacter == '+' || axiomCharacter == '-') {
			fprintf(finalFractalFile, "%c", axiomCharacter);
		}
	}

	fclose(finalFractalStageFile);
	fclose(finalFractalFile);

	return finalFractalFilePath;
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
}

void showFractal (char* name, char* fractalFilePath) {
	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 600;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	float currentX = SCREEN_WIDTH / 2.0f;
	float currentY = SCREEN_HEIGHT / 2.0f;
	float angle = 0.0f;
	float lineLength = 10.0f;

	FILE* finalFractalFile = mountFile(fractalFilePath, "w");
	char axiomCharacter;

	while ((axiomCharacter = fgetc(finalFractalFile)) != EOF) {
		if (axiomCharacter == 'F') {
			float nextX = currentX + lineLength * cos(angle);
			float nextY = currentY - lineLength * sin(angle);

			SDL_RenderDrawLine(renderer, (int)currentX, (int)currentY, (int)nextX, (int)nextY);

			currentX = nextX;
			currentY = nextY;
		} else if (axiomCharacter == '+') {
			angle -= 45.0f;
		} else if (axiomCharacter == '-') {
			angle += 45.0f;
		}
	}

	SDL_RenderPresent(renderer);
	fclose(finalFractalFile);
}
