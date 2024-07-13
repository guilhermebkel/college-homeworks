#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "graph.hpp"

void printFace(std::vector<Edge*>& face) {
    for (Edge *edge : face) {
        std::cout << edge->fromVertex->label << " -> ";
    }

    std::cout << face.back()->toVertex->label << std::endl;
}

int main() {
    std::vector<Vertex*> vertices = {
        new Vertex { .label = 'a', .x = -3, .y = 1 },
        new Vertex { .label = 'b', .x = -1, .y = 2 },
        new Vertex { .label = 'c', .x = 0.5, .y = 3 },
        new Vertex { .label = 'd', .x = 2.5, .y = 1.65 },
        new Vertex { .label = 'e', .x = 0.5, .y = 1.65 },
        new Vertex { .label = 'f', .x = 2, .y = 0.15 },
        new Vertex { .label = 'g', .x = 0, .y = 0.5 },
        new Vertex { .label = 'h', .x = -1.5, .y = 0.5 },
        new Vertex { .label = 'i', .x = -0.75, .y = -1.5 },
        new Vertex { .label = 'j', .x = 1.75, .y = -1.4 },
        new Vertex { .label = 'k', .x = 0.25, .y = -3 },
        new Vertex { .label = 'l', .x = 2.9, .y = -2.85 }
    };

    std::vector<std::pair<int, int>> graphUniqueEdges = {
        {1, 2}, {1, 8},
        {2, 3}, {2, 5}, {2, 7}, {2, 8},
        {3, 5}, {3, 4},
        {4, 5}, {4, 6},
        {5, 6}, {5, 7},
        {6, 7}, {6, 10},
        {7, 8}, {7, 9}, {7, 10},
        {8, 9},
        {9, 10}, {9, 11},
        {10, 11}, {10, 12},
        {11, 12}
    };

    std::vector<Vertex*> vertices2 = {
        new Vertex { .label = 'a', .x = 0, .y = 0 },
        new Vertex { .label = 'b', .x = 1, .y = 1 },
        new Vertex { .label = 'c', .x = 1, .y = -1 },
        new Vertex { .label = 'd', .x = 2, .y = 0 },
        new Vertex { .label = 'e', .x = 4, .y = 0 },
        new Vertex { .label = 'f', .x = 4, .y = -1.5 },
        new Vertex { .label = 'g', .x = -3, .y =  0 },
        new Vertex { .label = 'h', .x = -2, .y =  0 }
    };

    std::vector<std::pair<int, int>> graphUniqueEdges2 = {
        {1, 2}, {1, 3},
        {2, 4}, {2, 5}, {2, 7},
        {3, 4}, {3, 5}, {3, 6}, {3, 7},
        {5, 6},
        {7, 8}
    };

    std::vector<Edge*> edges;

    for (auto& edge : graphUniqueEdges) {
        Vertex *toVertex = vertices[edge.second - 1];
        Vertex *fromVertex = vertices[edge.first - 1];

        Edge *toEdge = createEdge(toVertex, fromVertex);
        Edge *fromEdge = createEdge(fromVertex, toVertex);

        edges.push_back(toEdge);
        edges.push_back(fromEdge);

        setReverseEdge(toEdge, fromEdge);

        addEdgeToVertex(toVertex, toEdge);
        addEdgeToVertex(fromVertex, fromEdge);
    }

    for (auto& vertex : vertices) {
        sortVertexEdges(vertex);
    }

    std::vector<std::vector<Edge*>> faces;

    for (auto& edge : edges) {
        if (edge->visited) {
            continue;
        }

        std::vector<Edge*> face;

        Edge *computedEdge = edge;

        do {
            face.push_back(computedEdge);
            computedEdge->visited = true;
            computedEdge = computedEdge->reverseEdge->nextEdge;
        } while (computedEdge != edge);

        faces.push_back(face);
    }

    for (auto& face : faces) {
        printFace(face);
    }

    return 0;
}
