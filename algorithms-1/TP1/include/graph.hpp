#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

struct Vertex;

struct Edge {
    Vertex *fromVertex;
    Vertex *toVertex;
    double angle;
    bool visited;
    Edge *nextEdge;
    Edge *reverseEdge;
};

struct Vertex {
    int id;
    int degree;
    std::vector<int> neighborVerticesIds;
    double x, y;
    std::vector<Edge*> outboundEdges;
};

void addEdgeToVertex(Vertex* vertex, Edge *edge);
void sortVertexEdges(Vertex* vertex);
void setReverseEdge(Edge *edge1, Edge *edge2);
Edge *createEdge(Vertex *fromVertex, Vertex *toVertex);

#endif
