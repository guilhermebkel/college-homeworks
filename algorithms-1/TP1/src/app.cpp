#include <iostream>
#include <algorithm>
#include <vector>

#include "graph.h"

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

	std::vector<Face> faces;

	for (size_t i = 0; i < vertices.size(); i++) {
		int initialVerticeId = vertices[i].id;
		std::vector<int> neighborVerticesIds = vertices[i].neighborVerticesIds;

		for (size_t neighborVerticeIndex = 0; neighborVerticeIndex < neighborVerticesIds.size(); neighborVerticeIndex++) {
			int neighborVerticeId = neighborVerticesIds[neighborVerticeIndex];

			Face face;
			face.vertices.push_back(vertices[initialVerticeId]);

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
