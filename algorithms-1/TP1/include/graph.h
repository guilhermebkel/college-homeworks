#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

typedef struct {
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

double getEuclideanDistance (Vertice a, Vertice b);
double getRelativeInclination (Vertice p, Vertice q);
float getCurveAngle (Vertice a, Vertice b, Vertice c);
void buildFace (std::vector<Vertice> vertices, std::vector<Vertice> *face, int currentVerticeId);

#endif
