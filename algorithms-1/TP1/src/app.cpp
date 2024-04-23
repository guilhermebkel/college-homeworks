#include <iostream>
#include <algorithm>
#include <vector>

#include "graph.hpp"

int main () {
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

	std::vector<Face> faces;

	for (size_t i = 0; i < vertices.size(); i++) {
		int initialVerticeId = vertices[i].id;
		std::vector<int> neighborVerticesIds = vertices[i].neighborVerticesIds;

		for (size_t neighborVerticeIndex = 0; neighborVerticeIndex < neighborVerticesIds.size(); neighborVerticeIndex++) {
			int neighborVerticeId = neighborVerticesIds[neighborVerticeIndex];

			Face face;

			addVerticeToFace(&face, vertices[initialVerticeId]);

			lookupInnerGraphFace(vertices, &face, neighborVerticeId);

			if (canComputeGraphFace(vertices, faces, face)) {
				faces.push_back(face);
			}
		}
	}

	for (size_t i = 0; i < faces.size(); ++i) {
        std::cout << "Face " << i + 1 << ": ";
        
		for (size_t j = 0; j < faces[i].vertices.size(); ++j) {
            std::cout << faces[i].vertices[j].label << " ";
        }

		std::cout << std::endl;
    }

	return 0;
}
