#include <stdio.h>
#include "fractal.h"

int main () {
	char* expandedFractal = expandFractal("F", "F-F++F-F", 3);

	printf("EXPANDED FRACTAL:: %s", expandedFractal);

	return 0;
}
