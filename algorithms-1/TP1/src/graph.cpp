#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "graph.hpp"

void addEdgeToVertex(Vertex* vertex, Edge *edge) {
    vertex->outboundEdges.push_back(edge);
}

void sortVertexEdges(Vertex* vertex) {
    std::sort(vertex->outboundEdges.begin(), vertex->outboundEdges.end(), [](Edge *e1, Edge *e2) {
        return e1->angle < e2->angle;
    });

    Edge *previousEdge = vertex->outboundEdges.back();

    for (Edge *edge : vertex->outboundEdges) {
        edge->nextEdge = previousEdge;
        previousEdge = edge;
    }
}

void setReverseEdge(Edge *edge1, Edge *edge2) {
    edge1->reverseEdge = edge2;
    edge2->reverseEdge = edge1;
};

Edge *createEdge(Vertex *fromVertex, Vertex *toVertex) {
    return new Edge {
        .fromVertex = fromVertex,
        .toVertex = toVertex,
        .angle = atan2(toVertex->y - fromVertex->y, toVertex->x - fromVertex->x),
        .visited = false,
        .nextEdge = nullptr,
        .reverseEdge = nullptr
    };
};
