#include <stdio.h>
#include <math.h>
#include "fractal.h"

int main () {
	/**
	 * (I) Floco de neve onda senoidal 2 de von Koch
	 */
	FractalAngle firstFractalAngle = M_PI / 3;
	FractalStage firstFractalStages = 4;
	FractalAxiom firstFractalAxiom = "F";
	FractalRule firstFractalRules[] = {{'F', "F-F+F+FF-F-F+F"}};
	expandFractal("fractal-1", firstFractalAngle, firstFractalAxiom, firstFractalRules, firstFractalStages);

	/**
	 * (II) Preenchimento de espaço de Peano
	 */
	FractalAngle secondFractalAngle = M_PI / 2;
	FractalStage secondFractalStages = 4;
	FractalAxiom secondFractalAxiom = "X";
	FractalRule secondFractalRules[] = {{'X', "XFYFX+F+YFXFY-F-XFYFX"}, {'Y', "YFXFY-F-XFYFX+F+YFXFY"}};
	expandFractal("fractal-2", secondFractalAngle, secondFractalAxiom, secondFractalRules, secondFractalStages);

	/**
	 * (III) Fractal de criação própria
	 */
	FractalAngle thirdFractalAngle = M_PI / 2;
	FractalStage thirdFractalStages = 4;
	FractalAxiom thirdFractalAxiom = "X";
	FractalRule thirdFractalRules[] = {{'X', "F+FY+X"}, {'Y', "-F+FY"}};
	expandFractal("fractal-3", thirdFractalAngle, thirdFractalAxiom, thirdFractalRules, thirdFractalStages);

	return 0;
}
