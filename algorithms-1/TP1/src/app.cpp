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

	std::vector<std::vector<int>> adjacencyList(vertices.size());

	for (size_t i = 0; i < vertices.size(); ++i) {
		int verticeId = vertices[i].id;
		std::vector<int> neighborVerticesIds = vertices[i].neighborVerticesIds;

		adjacencyList[verticeId] = neighborVerticesIds;
    }

	std::vector<std::vector<Vertice>> faces;

	for (size_t verticeIndex = 0; verticeIndex < adjacencyList.size(); verticeIndex++) {
		int initialVerticeId = verticeIndex;
		std::vector<int> neighborVerticeIds = adjacencyList[verticeIndex];

		for (size_t neighborVerticeIndex = 0; neighborVerticeIndex < neighborVerticeIds.size(); neighborVerticeIndex++) {
			int neighborVerticeId = neighborVerticeIds[neighborVerticeIndex];

			std::vector<Vertice> face;
			face.push_back(vertices[initialVerticeId]);
			buildFace(vertices, &face, neighborVerticeId);
		}
	}

	std::vector<int> cNeighborVerticeIds = adjacencyList[2];
	for (size_t i = 0; i < cNeighborVerticeIds.size(); ++i) {
		int neighborVerticeId = cNeighborVerticeIds[i];
		Vertice neighbor = vertices[neighborVerticeId];
		Vertice init = vertices[5];
		Vertice prev = vertices[5];
		Vertice curr = vertices[2];

		std::cout << neighborVerticeId << " ---- [distancia]: " << getEuclideanDistance(init, neighbor) <<  " ---- [curva]: " << getCurveAngle(prev, curr, neighbor) << std::endl;
    }

	return 0;
}
