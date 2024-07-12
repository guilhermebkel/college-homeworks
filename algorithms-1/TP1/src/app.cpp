#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Vertex; // Forward declaration

class Edge {
public:
    Vertex *from;
    Vertex *to;
    double angle;
    bool visited;
    Edge *next;
    Edge *reverse;

    Edge(Vertex *from, Vertex *to);

    void setReverseEdge(Edge *edge);

    friend class Vertex; // Allow Vertex to access private members
};

class Vertex {
public:
    int index;
    struct Point2D {
        double x, y;
        Point2D(double x, double y) : x(x), y(y) {}
    };
    Point2D point;
    std::vector<Edge*> outboundEdges;

    Vertex(int index, double x, double y) : index(index), point(x, y) {}

    void addEdge(Edge *edge) {
        outboundEdges.push_back(edge);
    }

    void sortEdges() {
        std::sort(outboundEdges.begin(), outboundEdges.end(), [](Edge *e1, Edge *e2) {
            return e1->angle < e2->angle;
        });

        Edge *prev = outboundEdges.back();
        for (Edge *edge : outboundEdges) {
            edge->next = prev;
            prev = edge;
        }
    }
};

Edge::Edge(Vertex *from, Vertex *to) : from(from), to(to), visited(false), next(nullptr), reverse(nullptr) {
    angle = atan2(to->point.y - from->point.y, to->point.x - from->point.x);
    from->addEdge(this);
}

void Edge::setReverseEdge(Edge *edge) {
    reverse = edge;
    edge->reverse = this;
}

void printFace(std::vector<Edge*>& face) {
    for (Edge *edge : face) {
        std::cout << edge->from->index << " -> ";
    }
    std::cout << face.back()->to->index << std::endl;
}

int main() {
//    std::map<int, Vertice> vertices = {
//		{ 1, { .label = 'a', .id = 1, .x = 0, .y = 0, .degree = 2, .neighborVerticesIds = {2, 3}}},
//		{ 2, { .label = 'b', .id = 2, .x = 1, .y = 1, .degree = 4, .neighborVerticesIds = {1, 4, 5, 7}}},
//		{ 3, { .label = 'c', .id = 3, .x = 1, .y = -1, .degree = 5, .neighborVerticesIds = {1, 4, 5, 6, 7}}},
//		{ 4, { .label = 'd', .id = 4, .x = 2, .y = 0, .degree = 2, .neighborVerticesIds = {2, 3}}},
//		{ 5, { .label = 'e', .id = 5, .x = 4, .y = 0, .degree = 3, .neighborVerticesIds = {2, 3, 6}}},
//		{ 6, { .label = 'f', .id = 6, .x = 4, .y = -1.5, .degree = 2, .neighborVerticesIds = {3, 5}}},
//		{ 7, { .label = 'g', .id = 7, .x = -3, .y = 0, .degree = 3, .neighborVerticesIds = {2, 3, 8}}},
//		{ 8, { .label = 'h', .id = 8, .x = -2, .y = 0, .degree = 1, .neighborVerticesIds = {7}}}
//	};

    std::vector<Vertex*> vertices = {
        new Vertex(1, 0, 0),
        new Vertex(2, 1, 1),
        new Vertex(3, 1, -1),
        new Vertex(4, 2, 0),
        new Vertex(5, 4, 0),
        new Vertex(6, 4, -1.5),
        new Vertex(7, -3, 0),
        new Vertex(8, -2, 0)
    };

    std::vector<std::pair<int, int>> graph = {
        {1, 2}, {1, 3},
        {2, 4}, {2, 5}, {2, 7},
        {3, 4}, {3, 5}, {3, 6}, {3, 7},
        {5, 6},
        {7, 8}
    };

    std::vector<Edge*> edges;

    for (auto& edge : graph) {
        Vertex *from = vertices[edge.first - 1];
        Vertex *to = vertices[edge.second - 1];
        edges.push_back(new Edge(from, to));
        edges.push_back(new Edge(to, from));

        edges[edges.size() - 2]->setReverseEdge(edges.back());
    }

    for (auto& vertex : vertices) {
        vertex->sortEdges();
    }

    std::vector<std::vector<Edge*>> faces;

    for (auto& edge : edges) {
        if (edge->visited) {
            continue;
        }

        std::vector<Edge*> face;
        faces.push_back(face);

        Edge *e = edge;
        do {
            face.push_back(e);
            e->visited = true;
            e = e->reverse->next;
        } while (e != edge);

        printFace(face);
    }

    // Limpeza de memória
    for (auto& vertex : vertices) {
        delete vertex;
    }

    for (auto& edge : edges) {
        delete edge;
    }

    return 0;
}
