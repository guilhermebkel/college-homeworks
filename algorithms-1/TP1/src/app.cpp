#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include "graph.hpp"

int main () {
	std::map<int, Vertice> vertices2 = {
		{ 0, { .label = 'a', .id = 0, .x = 0, .y = 0, .degree = 2, .neighborVerticesIds = {1, 2}}},
		{ 1, { .label = 'b', .id = 1, .x = 1, .y = 1, .degree = 4, .neighborVerticesIds = {0, 3, 4, 6}}},
		{ 2, { .label = 'c', .id = 2, .x = 1, .y = -1, .degree = 5, .neighborVerticesIds = {0, 3, 4, 5, 6}}},
		{ 3, { .label = 'd', .id = 3, .x = 2, .y = 0, .degree = 2, .neighborVerticesIds = {1, 2}}},
		{ 4, { .label = 'e', .id = 4, .x = 4, .y = 0, .degree = 3, .neighborVerticesIds = {1, 2, 5}}},
		{ 5, { .label = 'f', .id = 5, .x = 4, .y = -1.5, .degree = 2, .neighborVerticesIds = {2, 4}}},
		{ 6, { .label = 'g', .id = 6, .x = -3, .y = 0, .degree = 3, .neighborVerticesIds = {1, 2, 7}}},
		{ 7, { .label = 'h', .id = 7, .x = -2, .y = 0, .degree = 1, .neighborVerticesIds = {6}}}
	};

	std::map<int, Vertice> vertices = {
		{ 0, { .label = 'a', .id = 0, .x = -3, .y = 1, .degree = 2, .neighborVerticesIds = {1, 7}}},
		{ 1, { .label = 'b', .id = 1, .x = -1, .y = 2, .degree = 5, .neighborVerticesIds = {0, 2, 4, 6, 7}}},
		{ 2, { .label = 'c', .id = 2, .x = 0.5, .y = 3, .degree = 3, .neighborVerticesIds = {1, 4, 3}}},
		{ 3, { .label = 'd', .id = 3, .x = 2.5, .y = 1.65, .degree = 3, .neighborVerticesIds = {2, 4, 5}}},
		{ 4, { .label = 'e', .id = 4, .x = 0.5, .y = 1.65, .degree = 5, .neighborVerticesIds = {1, 2, 3, 5, 6}}},
		{ 5, { .label = 'f', .id = 5, .x = 2, .y = 0.15, .degree = 4, .neighborVerticesIds = {3, 4, 6, 9}}},
		{ 6, { .label = 'g', .id = 6, .x = 0, .y = 0.5, .degree = 6, .neighborVerticesIds = {1, 4, 5, 7, 8, 9}}},
		{ 7, { .label = 'h', .id = 7, .x = -1.5, .y = 0.5, .degree = 4, .neighborVerticesIds = {0, 1, 6, 8}}},
		{ 8, { .label = 'i', .id = 8, .x = -0.75, .y = -1.5, .degree = 4, .neighborVerticesIds = {6, 7, 9, 10}}},
		{ 9, { .label = 'j', .id = 9, .x = 1.75, .y = -1.4, .degree = 5, .neighborVerticesIds = {5, 6, 8, 10, 11}}},
		{ 10, { .label = 'k', .id = 10, .x = 0.25, .y = -3, .degree = 3, .neighborVerticesIds = {8, 9, 11}}},
		{ 11, { .label = 'l', .id = 11, .x = 2.9, .y = -2.85, .degree = 2, .neighborVerticesIds = {9, 10}}}
	};

	std::vector<Face> faces;

	for (auto data = vertices.begin(); data != vertices.end(); ++data) {
		Vertice initialVertice = data->second;

		int initialVerticeId = initialVertice.id;
		std::vector<int> neighborVerticesIds = initialVertice.neighborVerticesIds;

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
