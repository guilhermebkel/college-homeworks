#ifndef GRAPHH
#define GRAPHH

#include <stdio.h>

typedef struct {
	int id;
    int x;
    int y;
    int degree;
    int neighborVerticesIds[10];
} Vertice;

typedef struct {
	int verticesCount;
	int edgesCount;
    Vertice vertices[10];
} Graph;

#endif
