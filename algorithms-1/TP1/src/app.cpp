#include <iostream>
#include <vector>

#include "graph.h"

int main () {
	std::vector<Vertice> vertices = {
		{ .id = 0, .x = 0, .y = 0, .degree = 2, .neighborVerticesIds = {1, 2}},				// a
		{ .id = 1, .x = 1, .y = 1, .degree = 4, .neighborVerticesIds = {0, 3, 4, 6}},		// b
		{ .id = 2, .x = 1, .y = -1, .degree = 5, .neighborVerticesIds = {0, 3, 4, 5, 6}},	// c
		{ .id = 3, .x = 2, .y = 0, .degree = 2, .neighborVerticesIds = {1, 2}},				// d
		{ .id = 4, .x = 4, .y = 0, .degree = 3, .neighborVerticesIds = {1, 2, 5}}, 			// e
		{ .id = 5, .x = 4, .y = -1.5, .degree = 2, .neighborVerticesIds = {2, 4}},			// f
		{ .id = 6, .x = -3, .y = 0, .degree = 3, .neighborVerticesIds = {1, 2, 7}},			// g
		{ .id = 7, .x = -2, .y = 0, .degree = 1, .neighborVerticesIds = {6}}				// h
	};

	std::vector<std::vector<Vertice>> faces;

	for (size_t i = 0; i < vertices.size(); i++) {
		int initialVerticeId = vertices[i].id;
		std::vector<int> neighborVerticesIds = vertices[i].neighborVerticesIds;

		for (size_t neighborVerticeIndex = 0; neighborVerticeIndex < neighborVerticesIds.size(); neighborVerticeIndex++) {
			int neighborVerticeId = neighborVerticesIds[neighborVerticeIndex];

			std::vector<Vertice> face;
			face.push_back(vertices[initialVerticeId]);
			buildFace(vertices, &face, neighborVerticeId);
			faces.push_back(face);
		}
	}

	for (size_t i = 0; i < faces.size(); ++i) {
        std::cout << "Face " << i + 1 << ": ";
        
		for (size_t j = 0; j < faces[i].size(); ++j) {
            std::cout << faces[i][j].id << " ";
        }
        
		std::cout << std::endl;
    }

	return 0;
}
