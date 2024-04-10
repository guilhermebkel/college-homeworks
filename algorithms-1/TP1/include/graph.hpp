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
    std::string path;
} Face;

enum CurveType {
    straight = 1,
    left = 2,
    right = 3
};

void lookupInnerGraphFace (std::vector<Vertice> vertices, Face *face, int currentVerticeId);
bool canComputeGraphFace (std::vector<Vertice> vertices, std::vector<Face> faces, Face face);

#endif
