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
    std::vector<Vertice> vertices;
    int uniqueId;
} Face;

void lookupInnerFace (std::vector<Vertice> vertices, Face *face, int currentVerticeId);

#endif
