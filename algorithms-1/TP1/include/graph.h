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

void lookupInnerGraphFace (std::vector<Vertice> vertices, Face *face, int currentVerticeId);
bool canComputeGraphFace (std::vector<Face> faces, Face face);

#endif
