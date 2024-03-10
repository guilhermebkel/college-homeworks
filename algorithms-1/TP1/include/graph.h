#ifndef GRAPHH
#define GRAPHH

#include <stdio.h>

typedef struct {
	int id;
    int x;
    int y;
    int degree;
    int neighborVerticesIds[];
} VerticeDefinition;

typedef struct {
	int verticesCount;
	int edgesCount;
    VerticeDefinition vertices[];
} GraphDefinition;

#endif
