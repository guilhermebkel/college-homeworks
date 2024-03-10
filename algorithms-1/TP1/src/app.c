#include <stdio.h>
#include "graph.h"

int main () {
	VerticeDefinition vertices[] = {
		{ .id = 1, .x = 0, .y = 0, .degree = 2, .neighborVerticesIds = {2, 3}},
		{ .id = 2, .x = 1, .y = 1, .degree = 4, .neighborVerticesIds = {1, 4, 5, 7}},
		{ .id = 3, .x = 1, .y = -1, .degree = 5, .neighborVerticesIds = {1, 4, 5, 6, 7}},
		{ .id = 4, .x = 2, .y = 0, .degree = 2, .neighborVerticesIds = {2, 3}},
		{ .id = 5, .x = 4, .y = 0, .degree = 3, .neighborVerticesIds = {2, 3, 6}},
		{ .id = 6, .x = 4, .y = -1.5, .degree = 2, .neighborVerticesIds = {3, 5}},
		{ .id = 7, .x = -3, .y = 0, .degree = 3, .neighborVerticesIds = {2, 3, 8}},
		{ .id = 8, .x = -2, .y = 0, .degree = 1, .neighborVerticesIds = {7}}
	};

	GraphDefinition graph = {
		.verticesCount = 8,
		.edgesCount = 11,
		.vertices = vertices
	};
	
	return 0;
}
