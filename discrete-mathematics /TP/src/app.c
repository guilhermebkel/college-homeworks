#include <stdio.h>
#include "fractal.h"

int main () {
	/**
	 * (I) Floco de neve onda senoidal 2 de von Koch
	 */
	FractalAngle firstFractalAngle = 60.0f;
	FractalStage firstFractalStages = 4;
	FractalAxiom firstFractalAxiom = "F";
	FractalRule firstFractalRules[] = {{'F', "F-F+F+FF-F-F+F"}};
	expandFractal("fractal-1", firstFractalAngle, firstFractalAxiom, firstFractalRules, firstFractalStages);

	/**
	 * (II) Preenchimento de espaço de Peano
	 */
	FractalAngle secondFractalAngle = 90.0f;
	FractalStage secondFractalStages = 4;
	FractalAxiom secondFractalAxiom = "X";
	FractalRule secondFractalRules[] = {{'X', "XFYFX+F+YFXFY-F-XFYFX"}, {'Y', "YFXFY-F-XFYFX+F+YFXFY"}};
	expandFractal("fractal-2", secondFractalAngle, secondFractalAxiom, secondFractalRules, secondFractalStages);

	/**
	 * (III) Fractal de criação própria
	 */
	FractalAngle thirdFractalAngle = 90.0f;
	FractalStage thirdFractalStages = 4;
	FractalAxiom thirdFractalAxiom = "X";
	FractalRule thirdFractalRules[] = {{'X', "F+FY+X"}, {'Y', "-F+FY"}};
	expandFractal("fractal-3", thirdFractalAngle, thirdFractalAxiom, thirdFractalRules, thirdFractalStages);

	return 0;
}
