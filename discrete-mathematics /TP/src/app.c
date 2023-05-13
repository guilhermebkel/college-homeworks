#include <stdio.h>
#include "fractal.h"

int main () {
	FractalStage stages = 1;
	FractalAxiom axiom = "F";
	FractalRule rules[] = {
		{'F', "F-F++F-F"}
	};

	char* expandedFractalAxiom = expandFractalAxiom(axiom, rules, stages);

	generateFractalAxiomPlotDescription(expandedFractalAxiom);

	return 0;
}
