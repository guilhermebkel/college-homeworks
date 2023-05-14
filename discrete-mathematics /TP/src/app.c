#include <stdio.h>
#include "fractal.h"

int main () {
	FractalStage stages = 2;
	FractalAxiom axiom = "F";
	FractalRule rules[] = {
		{'F', "F-F++F-F"}
	};

	char* expandedFractalAxiom = expandFractalAxiom(axiom, rules, stages);

	printf("%s", expandedFractalAxiom);

	return 0;
}
