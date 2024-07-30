#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f

class DisjointSetUnion {
	private:
		std::vector<long long int> parent;
		std::vector<long long int> rank;
	
	public:
		DisjointSetUnion(long long int n) {
			for (long long int i = 0; i < n; i++) { 
				this->parent.push_back(-1);
				this->rank.push_back(1);
			}
		}

		long long int find(long long int v) {
			if (parent[v] == -1) {
				return v;
			}
	
			return parent[v] = find(parent[v]); 
		}

		void unite(long long int u, long long int v) {
			long long int s1 = this->find(u); 
			long long int s2 = this->find(v); 

			if (s1 != s2) { 
				if (rank[s1] < rank[s2]) { 
					parent[s1] = s2; 
				} else if (rank[s1] > rank[s2]) { 
					parent[s2] = s1; 
				} else { 
					parent[s2] = s1; 
					rank[s1] += 1; 
				}
			} 
		}
};

class Edge {
	public:
		long long int fromVertexId, toVertexId, year, duration, cost;

		Edge(long long int fromVertexId, long long int toVertexId, long long int year, long long int duration, long long int cost) {
			this->fromVertexId = fromVertexId;
			this->toVertexId = toVertexId;
			this->year = year;
			this->duration = duration;
			this->cost = cost;
		}
};

class Vertex {
	public:
		long long int id, distance, totalTime;
		std::vector<Edge> adjacencyList;

		Vertex(long long int id){
			this->id = id;
			this->distance = INF;
			this->totalTime = 0;
		}

		void addEdge(Edge edge) {
			this->adjacencyList.push_back(edge);  
		}
};

using Graph = std::vector<Vertex>;

using DistanceAndIdPair = std::pair<long long int, long long int>;

void dijkstraAlgorithm(Graph graph) {
	int verticesCount = graph.size();
	std::priority_queue<DistanceAndIdPair, std::vector<DistanceAndIdPair>, std::greater<DistanceAndIdPair>> priorityQueue;

	priorityQueue.push(std::make_pair(0, 1));
	graph[0].distance = 0;

	while (!priorityQueue.empty()) {
		long long int fromVertexId = priorityQueue.top().second;
		Vertex *fromVertex = &graph[fromVertexId-1];
		priorityQueue.pop();

		for(size_t i=0; i < fromVertex->adjacencyList.size(); i++) {
			Vertex *toVertex = &graph[fromVertex->adjacencyList[i].toVertexId-1];

			if (toVertex->distance > fromVertex->distance + fromVertex->adjacencyList[i].duration) {
				toVertex->distance = fromVertex->distance + fromVertex->adjacencyList[i].duration;
				toVertex->totalTime = fromVertex->adjacencyList[i].year;

				priorityQueue.push(std::make_pair(toVertex->distance, toVertex->id));
			} else if (toVertex->distance == fromVertex->distance + fromVertex->adjacencyList[i].duration) {
				if (toVertex->totalTime > fromVertex->adjacencyList[i].year) {
					toVertex->distance = fromVertex->distance + fromVertex->adjacencyList[i].duration;
					toVertex->totalTime = fromVertex->adjacencyList[i].year;

					priorityQueue.push(std::make_pair(toVertex->distance, toVertex->id));
				}
			}
		}
	}

	for (long long int i = 0; i < verticesCount; i++) {
		std::cout << graph[i].distance << std::endl;
	}

	long long int yearAllMutuallyReachable = 0;

	for (long long int i = 0; i < verticesCount; i++) {
		if (graph[i].totalTime > yearAllMutuallyReachable) {
			yearAllMutuallyReachable = graph[i].totalTime;
		}
	}

	std::cout << yearAllMutuallyReachable << std::endl;
}

void kruskalAlgorithm(Graph graph) {
	int verticesCount = graph.size();
	std::vector<Edge> edges;

	for (long long int i = 0; i < verticesCount; i++) {
		for (size_t j = 0; j < graph[i].adjacencyList.size(); j++) {
			edges.push_back(graph[i].adjacencyList[j]);
		}
	}
	
	long long int yearAllReachable = 0;
	DisjointSetUnion dsu1 = DisjointSetUnion(verticesCount);
	std::sort(edges.begin(), edges.end(), [](Edge e1, Edge e2){ return e1.year < e2.year; });
	for (size_t i = 0; i < edges.size(); i++) {
		if (dsu1.find(edges[i].fromVertexId-1) != dsu1.find(edges[i].toVertexId-1)) {
			dsu1.unite(edges[i].fromVertexId-1, edges[i].toVertexId-1);

			if (edges[i].year > yearAllReachable) {
				yearAllReachable = edges[i].year;
			}
		}
	}
	std::cout << yearAllReachable << std::endl;

	long long int minCost = 0;
	DisjointSetUnion dsu2 = DisjointSetUnion(verticesCount);
	std::sort(edges.begin(), edges.end(), [](Edge e1, Edge e2){ return e1.cost < e2.cost; });
	for (size_t i = 0; i < edges.size(); i++) {
		if (dsu2.find(edges[i].fromVertexId-1) != dsu2.find(edges[i].toVertexId-1)) {
			dsu2.unite(edges[i].fromVertexId-1, edges[i].toVertexId-1);

			minCost += edges[i].cost;
		}
	}
	std::cout << minCost << std::endl;
}

int main() {
	Graph graph;

	int N, M;
	std::cin >> N >> M;

	for (long long int i=0; i < N; i++) {
		Vertex vertex = Vertex(i+1);
		graph.push_back(vertex);
	}

	for(long long int i = 0; i < M; i++) {
		int fromVertexId, toVertexId, year, travelTime, cost;
		std::cin >> fromVertexId >> toVertexId >> year >> travelTime >> cost;

		Edge edge = Edge(fromVertexId, toVertexId, year, travelTime, cost);
		graph[fromVertexId-1].addEdge(edge);
		
		Edge inverseEdge = Edge(toVertexId, fromVertexId, year, travelTime, cost);
		graph[toVertexId-1].addEdge(inverseEdge);
	}
	
	dijkstraAlgorithm(graph);

	kruskalAlgorithm(graph);
}