#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

typedef struct {
    char label;
	int id;
    float x;
    float y;
    int degree;
    std::vector<int> neighborVerticesIds;
} Vertice;

typedef struct {
	int edgesCount;
    std::vector<Vertice> vertices;
} Graph;

typedef struct {
    std::vector<Vertice> vertices;
} Face;

void lookupInnerFace (std::vector<Vertice> vertices, std::vector<Vertice> *face, int currentVerticeId);

#endif
