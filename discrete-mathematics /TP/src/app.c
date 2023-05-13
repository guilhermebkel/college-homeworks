#include <stdio.h>
#include "fractal.h"

int main () {
	FractalStage stages = 1;
	FractalAxiom axiom = "F";
	FractalRule rules[] = {
		{'F', "F-F++F-F"}
	};

	char* expandedFractalAxiom = expandFractalAxiom(axiom, rules, stages);

	generateFractalAxiomPlotDescription(expandedFractalAxiom, "./output/fractal_axiom_plot_description.gp");

	return 0;
}
