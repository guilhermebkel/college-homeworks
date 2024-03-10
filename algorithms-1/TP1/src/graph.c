#include <math.h>
#include "graph.h"

// Distância euclidiana de a para b.
double calculateEuclideanDistance (Vertice a, Vertice b) {
    double x = (a.x - b.x);
    double y = (a.y - b.y);

    return sqrt(x*x + y*y);
}

// Coeficiente da reta que passa na origem e p.
double calculateInclination(Vertice p) {
    return atan2(p.y, p.x);
}

// Coeficiente da reta orientada de p para q.
double calculateRelativeInclination(Vertice p, Vertice q) {
    return atan2(q.y - p.y, q.x - p.x);
}

// Determina se ao caminhar de a para b e depois de b para c
int getCurveType(Vertice a, Vertice b, Vertice c) {
    double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);

    if (v < 0) {
        return -1; // left
    }

    if (v > 0) {
        return +1; // right
    }
    
    return 0; // straight
}
