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
	int edgesCount;
    Vertice vertices[10];
} Graph;

typedef struct {
    Vertice vertices[10];
} Face;

#endif
