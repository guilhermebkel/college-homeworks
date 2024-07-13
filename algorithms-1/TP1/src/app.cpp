#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "graph.hpp"

struct AppInput {
    std::vector<Vertex> vertices;
    std::vector<std::pair<int, int>> edgesByVertices;
};

void printFace(std::vector<Edge*>& face) {
    for (Edge *edge : face) {
        std::cout << edge->fromVertex->id << " -> ";
    }

    std::cout << face.back()->toVertex->id << std::endl;
}

AppInput readAppInput () {
    AppInput appInput;

    int verticesCount, edgesCount;
    std::cin >> verticesCount >> edgesCount;

    for (int i = 0; i < verticesCount; i++) {
        int vertexId = i + 1;

        Vertex vertex;
        vertex.id = vertexId;

        std::cin >> vertex.x >> vertex.y >> vertex.degree;

        for (int j = 0; j < vertex.degree; j++) {
            int neighborVertexId;

            std::cin >> neighborVertexId;

            vertex.neighborVerticesIds.push_back(neighborVertexId);

            if (vertexId < neighborVertexId) {
                appInput.edgesByVertices.push_back(std::make_pair(vertexId, neighborVertexId));
            }
        }

        appInput.vertices.push_back(vertex);
    }

    return appInput;
}

int main() {
    AppInput appInput = readAppInput();

    std::vector<Vertex*> vertices;
    std::vector<std::pair<int, int>> edgesByVertices = appInput.edgesByVertices;

    for (auto& vertex : appInput.vertices) {
        vertices.push_back(&vertex);
    }

    std::vector<Edge*> edges;

    for (auto& edgeByVertice : edgesByVertices) {
        Vertex *toVertex = vertices[edgeByVertice.second - 1];
        Vertex *fromVertex = vertices[edgeByVertice.first - 1];

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
