#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
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
    std::string path;
    int uniqueId;
} Face;

enum CurveType {
    straight = 1,
    left = 2,
    right = 3
};

void lookupInnerGraphFace (std::map<int, Vertice> vertices, Face *face, int currentVerticeId);
void addVerticeToFace (Face *face, Vertice vertice);
bool canComputeGraphFace (std::map<int, Vertice> vertices, std::vector<Face> faces, Face face);
void addExternalFace(std::map<int, Vertice>& vertices);

#endif
