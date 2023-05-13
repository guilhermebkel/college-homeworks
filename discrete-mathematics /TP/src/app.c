#include <stdio.h>
#include "fractal.h"

int main () {
	FractalAxiom axiom = "X";
	FractalRule rules[] = {
		{'X', "-YF+XFX+FY"},
		{'Y', "+XF-YFY-FX+"}
	};

	char* expandedFractal = expandFractal(axiom, rules, 1);

	printf("EXPANDED FRACTAL:: %s", expandedFractal);

	return 0;
}
