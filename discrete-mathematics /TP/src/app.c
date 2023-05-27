#include <stdio.h>
#include "fractal.h"

int main () {
	FractalStage stages = 2;
	FractalAxiom axiom = "F";
	FractalRule rules[] = {
		{'F', "F-F++F-F"}
	};

	expandFractal("hahahah", axiom, rules, stages);

	return 0;
}
