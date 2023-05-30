#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "fractal.h"
#include "fractal-file.h"
#include "shared-utils.h"

void expandFractal (char* name, FractalAngle angle, FractalAxiom axiom, FractalRule rules[], FractalStage stages) {
	generateInitialFractalStageFile(name, axiom);

	char* finalFractalStageFilePath = processFractalStagesOnDemand(name, axiom, rules, stages);

	char* finalFractalFilePath = processFinalFractal(name, finalFractalStageFilePath);

	renderFractal(name, angle, finalFractalFilePath);
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

void renderFractal (char* name, FractalAngle angle, char* fractalFilePath) {
	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 600;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	float currentX = SCREEN_WIDTH / 2.0f;
	float currentY = SCREEN_HEIGHT / 2.0f;
	float currentAngle = 0.0f;
	float lineLength = 20.0f;

	FILE* finalFractalFile = mountFile(fractalFilePath, "r");
	char axiomCharacter;

	while ((axiomCharacter = fgetc(finalFractalFile)) != EOF) {
		if (axiomCharacter == 'F') {
			float nextX = currentX + lineLength * cos(currentAngle);
			float nextY = currentY - lineLength * sin(currentAngle);

			SDL_RenderDrawLine(renderer, (int)currentX, (int)currentY, (int)nextX, (int)nextY);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			currentX = nextX;
			currentY = nextY;
		} else if (axiomCharacter == '+') {
			currentAngle -= angle;
		} else if (axiomCharacter == '-') {
			currentAngle += angle;
		}
	}

	fclose(finalFractalFile);

	SDL_Surface* surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);

	char* fractalPicturePath = mountFractalPicturePath(name);
	IMG_SavePNG(surface, fractalPicturePath);

	SDL_FreeSurface(surface);
	SDL_Quit();
}
