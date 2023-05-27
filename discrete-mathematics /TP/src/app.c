#include <stdio.h>
#include "fractal.h"

int main () {
	/**
	 * (I) Floco de neve onda senoidal 2 de von Koch
	 */
	FractalStage firstFractalStages = 4;
	FractalAxiom firstFractalAxiom = "F";
	FractalRule firstFractalRules[] = {{'F', "F-F+F+FF-F-F+F"}};
	expandFractal("fractal-1", firstFractalAxiom, firstFractalRules, firstFractalStages);

	/**
	 * (II) Preenchimento de espaço de Peano
	 */
	FractalStage secondFractalStages = 4;
	FractalAxiom secondFractalAxiom = "X";
	FractalRule secondFractalRules[] = {{'X', "XFYFX+F+YFXFY-F-XFYFX"}, {'Y', "YFXFY-F-XFYFX+F+YFXFY"}};
	expandFractal("fractal-2", secondFractalAxiom, secondFractalRules, secondFractalStages);

	/**
	 * (III) Fractal de criação própria
	 */
	FractalStage ThirdFractalStages = 4;
	FractalAxiom ThirdFractalAxiom = "X";
	FractalRule ThirdFractalRules[] = {{'X', "+FXFX-YF"}, {'Y', "-FYFY+XF++"}};
	expandFractal("fractal-3", ThirdFractalAxiom, ThirdFractalRules, ThirdFractalStages);

	return 0;
}
