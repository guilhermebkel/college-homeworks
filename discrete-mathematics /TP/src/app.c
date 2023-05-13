#include <stdio.h>
#include "fractal.h"

int main () {
	FractalStage stages = 1;
	FractalAxiom axiom = "X";
	FractalRule rules[] = {
		{'X', "-YF+XFX+FY"},
		{'Y', "+XF-YFY-FX+"}
	};

	char* expandedFractal = expandFractal(axiom, rules, stages);

	printf("EXPANDED FRACTAL:: %s", expandedFractal);

	return 0;
}
