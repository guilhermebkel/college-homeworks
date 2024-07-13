#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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

struct Input {
    std::vector<Vertex> vertices;
    std::vector<std::pair<int, int>> edgesByVertices;
};

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

void printResult(std::vector<std::vector<Edge*>> faces) {
    std::cout << faces.size() << std::endl;

    for (auto& face : faces) {
        std::cout << face.size() + 1 << " ";

        for (Edge *edge : face) {
            std::cout << edge->fromVertex->id << " ";
        }

        std::cout << face.back()->toVertex->id << std::endl;
    }
}

Input readInput () {
    Input input;

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
                input.edgesByVertices.push_back(std::make_pair(vertexId, neighborVertexId));
            }
        }

        input.vertices.push_back(vertex);
    }

    return input;
}

int main() {
    Input input = readInput();

    std::vector<Vertex*> vertices;
    std::vector<std::pair<int, int>> edgesByVertices = input.edgesByVertices;

    for (auto& vertex : input.vertices) {
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

    printResult(faces);

    return 0;
}
