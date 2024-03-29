#include <iostream>
#include <vector>

#include "graph.h"

int main () {
	std::vector<Vertice> vertices = {
		{ .id = 0, .x = 0, .y = 0, .degree = 2, .neighborVerticesIds = {2, 3}},				// a
		{ .id = 1, .x = 1, .y = 1, .degree = 4, .neighborVerticesIds = {1, 4, 5, 7}},		// b
		{ .id = 2, .x = 1, .y = -1, .degree = 5, .neighborVerticesIds = {1, 4, 5, 6, 7}},	// c
		{ .id = 3, .x = 2, .y = 0, .degree = 2, .neighborVerticesIds = {2, 3}},				// d
		{ .id = 4, .x = 4, .y = 0, .degree = 3, .neighborVerticesIds = {2, 3, 6}}, 			// e
		{ .id = 5, .x = 4, .y = -1.5, .degree = 2, .neighborVerticesIds = {3, 5}},			// f
		{ .id = 6, .x = -3, .y = 0, .degree = 3, .neighborVerticesIds = {2, 3, 8}},			// g
		{ .id = 7, .x = -2, .y = 0, .degree = 1, .neighborVerticesIds = {7}}				// h
	};

	std::vector<std::vector<int>> adjacencyList(vertices.size());

	for (size_t i = 0; i < vertices.size(); ++i) {
		int verticeId = vertices[i].id;
		std::vector<int> neighborVerticesIds = vertices[i].neighborVerticesIds;

		adjacencyList[verticeId] = neighborVerticesIds;
    }

	std::vector<std::vector<Vertice>> faces;

	std::vector<int> c = adjacencyList[2];
	for (size_t i = 0; i < c.size(); ++i) {
		int neighborVerticeId = c[i];
		
		std::cout << neighborVerticeId << ": " << getRelativeInclination(vertices[2], vertices[neighborVerticeId]) << std::endl;
    }

	return 0;
}
