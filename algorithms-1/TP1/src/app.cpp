#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

typedef struct {
    char label;
    int id;
    float x;
    float y;
    int degree;
    std::vector<int> neighborVerticesIds;
} Vertice;

int64_t cross(const Vertice &p1, const Vertice &p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

int64_t cross(const Vertice &p, const Vertice &q, const Vertice &r) {
    return (p.x - q.x) * (r.y - q.y) - (p.y - q.y) * (r.x - q.x);
}

int half(const Vertice &p) {
    return int(p.y < 0 || (p.y == 0 && p.x < 0));
}

// Função para encontrar faces
std::vector<std::vector<size_t>> find_faces(std::vector<Vertice> vertices, std::map<int, std::vector<int>> adjacencyList) {
    size_t n = vertices.size();
    std::vector<std::vector<char>> used(n);
    for (size_t i = 0; i < n; i++) {
        used[i].resize(adjacencyList[i].size());
        used[i].assign(adjacencyList[i].size(), 0);
        auto compare = [&](size_t l, size_t r) {
            Vertice pl = { .x = vertices[l].x - vertices[i].x, .y = vertices[l].y - vertices[i].y };
            Vertice pr = { .x = vertices[r].x - vertices[i].x, .y = vertices[r].y - vertices[i].y };
            if (half(pl) != half(pr))
                return half(pl) < half(pr);
            return cross(pl, pr) > 0;
        };
        std::sort(adjacencyList[i].begin(), adjacencyList[i].end(), compare);
    }
    std::vector<std::vector<size_t>> faces;
    for (size_t i = 0; i < n; i++) {
        for (size_t edge_id = 0; edge_id < adjacencyList[i].size(); edge_id++) {
            if (used[i][edge_id]) {
                continue;
            }
            std::vector<size_t> face;
            size_t v = i;
            size_t e = edge_id;
            while (!used[v][e]) {
                used[v][e] = true;
                face.push_back(v);
                size_t u = adjacencyList[v][e];
                size_t e1 = std::lower_bound(adjacencyList[u].begin(), adjacencyList[u].end(), v, [&](size_t l, size_t r) {
					Vertice pl = { .x = vertices[l].x - vertices[u].x, .y = vertices[l].y - vertices[u].y };
            		Vertice pr = { .x = vertices[r].x - vertices[u].x, .y = vertices[r].y - vertices[u].y };
                    if (half(pl) != half(pr))
                        return half(pl) < half(pr);
                    return cross(pl, pr) > 0;
                }) - adjacencyList[u].begin() + 1;
                if (e1 == adjacencyList[u].size()) {
                    e1 = 0;
                }
                v = u;
                e = e1;
            }
            std::reverse(face.begin(), face.end());
            int sign = 0;
            for (size_t j = 0; j < face.size(); j++) {
                size_t j1 = (j + 1) % face.size();
                size_t j2 = (j + 2) % face.size();
                int64_t val = cross(vertices[face[j]], vertices[face[j1]], vertices[face[j2]]);
                if (val > 0) {
                    sign = 1;
                    break;
                } else if (val < 0) {
                    sign = -1;
                    break;
                }
            }
            if (sign <= 0) {
                faces.insert(faces.begin(), face);
            } else {
                faces.emplace_back(face);
            }
        }
    }
    return faces;
}

int main() {
    // Convertendo o mapa de vértices para um vetor de pontos e vetor de adjacências
	std::vector<Vertice> vertices = {
		{ .label = 'a', .id = 0, .x = 0, .y = 0, .degree = 2, .neighborVerticesIds = {1, 2}},
		{ .label = 'b', .id = 1, .x = 1, .y = 1, .degree = 4, .neighborVerticesIds = {0, 3, 4, 6}},
		{ .label = 'c', .id = 2, .x = 1, .y = -1, .degree = 5, .neighborVerticesIds = {0, 3, 4, 5, 6}},
		{ .label = 'd', .id = 3, .x = 2, .y = 0, .degree = 2, .neighborVerticesIds = {1, 2}},
		{ .label = 'e', .id = 4, .x = 4, .y = 0, .degree = 3, .neighborVerticesIds = {1, 2, 5}},
		{ .label = 'f', .id = 5, .x = 4, .y = -1.5, .degree = 2, .neighborVerticesIds = {2, 4}},
		{ .label = 'g', .id = 6, .x = -3, .y = 0, .degree = 3, .neighborVerticesIds = {1, 2, 7}},
		{ .label = 'h', .id = 7, .x = -2, .y = 0, .degree = 1, .neighborVerticesIds = {6}}
	};

	std::vector<Vertice> vertices2 = {
		{ .label = 'a', .id = 0, .x = -3, .y = 1, .degree = 2, .neighborVerticesIds = {1, 7}},
		{ .label = 'b', .id = 1, .x = -1, .y = 2, .degree = 5, .neighborVerticesIds = {0, 2, 4, 6, 7}},
		{ .label = 'c', .id = 2, .x = 0.5, .y = 3, .degree = 3, .neighborVerticesIds = {1, 4, 3}},
		{ .label = 'd', .id = 3, .x = 2.5, .y = 1.65, .degree = 3, .neighborVerticesIds = {2, 4, 5}},
		{ .label = 'e', .id = 4, .x = 0.5, .y = 1.65, .degree = 5, .neighborVerticesIds = {1, 2, 3, 5, 6}},
		{ .label = 'f', .id = 5, .x = 2, .y = 0.15, .degree = 4, .neighborVerticesIds = {3, 4, 6, 9}},
		{ .label = 'g', .id = 6, .x = 0, .y = 0.5, .degree = 6, .neighborVerticesIds = {1, 4, 5, 7, 8, 9}},
		{ .label = 'h', .id = 7, .x = -1.5, .y = 0.5, .degree = 4, .neighborVerticesIds = {0, 1, 6, 8}},
		{ .label = 'i', .id = 8, .x = -0.75, .y = -1.5, .degree = 4, .neighborVerticesIds = {6, 7, 9, 10}},
		{ .label = 'j', .id = 9, .x = 1.75, .y = -1.4, .degree = 5, .neighborVerticesIds = {5, 6, 8, 10, 11}},
		{ .label = 'k', .id = 10, .x = 0.25, .y = -3, .degree = 3, .neighborVerticesIds = {8, 9, 11}},
		{ .label = 'l', .id = 11, .x = 2.9, .y = -2.85, .degree = 2, .neighborVerticesIds = {9, 10}}
	};

    std::map<int, std::vector<int>> adjacencyList;

	for (size_t i = 0; i < vertices.size(); i++) {
		adjacencyList[i] = vertices[i].neighborVerticesIds;
	}

    std::vector<std::vector<size_t>> faces = find_faces(vertices, adjacencyList);

    std::cout << "Faces encontradas:" << std::endl;
    for (const auto& face : faces) {
        for (size_t vertex_id : face) {
			Vertice vertice = vertices[vertex_id];
            std::cout << vertice.label << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
