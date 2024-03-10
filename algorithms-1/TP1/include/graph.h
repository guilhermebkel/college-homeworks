#ifndef GRAPHH
#define GRAPHH

#include <stdio.h>

typedef struct {
	int id;
    int x;
    int y;
    int degree;
    int neighborVerticesIds[10];
} VerticeDefinition;

typedef struct {
	int verticesCount;
	int edgesCount;
    VerticeDefinition vertices[10];
} GraphDefinition;

#endif
