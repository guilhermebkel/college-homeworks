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
            if (parent[v] == -1) 
                return v; 
        
            return parent[v] = find(parent[v]); 
        }

        void unite(long long int u, long long int v) {
            long long int s1 = this->find(u); 
            long long int s2 = this->find(v); 

            if (s1 != s2) { 
                if (rank[s1] < rank[s2]) { 
                    parent[s1] = s2; 
                } 
                else if (rank[s1] > rank[s2]) { 
                    parent[s2] = s1; 
                } 
                else { 
                    parent[s2] = s1; 
                    rank[s1] += 1; 
                } 
            } 
        }
};

class Edge {
    public:
        long long int v, u;
        long long int year;
        long long int duration;
        long long int cost;
        Edge(long long int _v, long long int _u, long long int _year, long long int _duration, long long int _cost) {
            this->v = _v;
            this->u = _u;
            this->year = _year;
            this->duration = _duration;
            this->cost = _cost;
        }
};

class Vertex {
    public:
        long long int distance, id, totalTime;
        std::vector<Edge> adjList;

        Vertex(long long int _id){
            this->distance = INF;
            this->totalTime = 0;
            this->id = _id;
        }

        void addEdge(Edge e) {
            this->adjList.push_back(e);  
        }
};

using Graph = std::vector<Vertex>;

using iPair = std::pair<long long int, long long int>;

void dijkstraAlgorithm(Graph graph) {
    int verticesCount = graph.size();
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> priorityQueue;

    priorityQueue.push(std::make_pair(0, 1));
    graph[0].distance = 0;

    int bigger_time = 0;

    while (!priorityQueue.empty()) {
        long long int u = priorityQueue.top().second;
        Vertex *vertex_u = &graph[u-1];
        priorityQueue.pop();

        for(long long int i=0; i < vertex_u->adjList.size(); i++) {
            Vertex *vertex_v = &graph[vertex_u->adjList[i].u-1];

            if (vertex_v->distance > vertex_u->distance + vertex_u->adjList[i].duration) {
                vertex_v->distance = vertex_u->distance + vertex_u->adjList[i].duration;
                vertex_v->totalTime = vertex_u->adjList[i].year;

                priorityQueue.push(std::make_pair(vertex_v->distance, vertex_v->id));
            } else if (vertex_v->distance == vertex_u->distance + vertex_u->adjList[i].duration) {
                if (vertex_v->totalTime > vertex_u->adjList[i].year) {
                    vertex_v->distance = vertex_u->distance + vertex_u->adjList[i].duration;
                    vertex_v->totalTime = vertex_u->adjList[i].year;

                    priorityQueue.push(std::make_pair(vertex_v->distance, vertex_v->id));
                }
            }
        }
    }

    for (long long int i = 0; i < verticesCount; i++) {
        std::cout << graph[i].distance << std::endl;
    }

    long long int maxYear = 0;

    for (long long int i = 0; i < verticesCount; i++) {
        if (graph[i].totalTime > maxYear) {
            maxYear = graph[i].totalTime;
        }
    }

    std::cout << maxYear << std::endl;
}

void kruscalAlgorithm(Graph graph, bool type) {
    int verticesCount = graph.size();
    DisjointSetUnion dsu = DisjointSetUnion(verticesCount);
    std::vector<Edge> edges;
    long long int bigger_year = 0;
    long long int ans = 0;

    for (long long int i = 0; i < verticesCount; i++) {
        for (long long int j = 0; j < graph[i].adjList.size(); j++) {
            edges.push_back(graph[i].adjList[j]);
        }
    }

    if (type == 0) {
        std::sort(edges.begin(), edges.end(), [](Edge e1, Edge e2){ return e1.year<e2.year; });
    }
    else if (type == 1) {
        std::sort(edges.begin(), edges.end(), [](Edge e1, Edge e2){ return e1.cost<e2.cost; });
    }

    for (long long int i = 0; i < edges.size(); i++) {
        if (dsu.find(edges[i].v-1) != dsu.find(edges[i].u-1)) {
            dsu.unite(edges[i].v-1, edges[i].u-1);

            if (type == 0) {
                if (edges[i].year > bigger_year) {
                    bigger_year = edges[i].year;
                }
            } else if (type == 1) {
                ans += edges[i].cost;
            }
        }
    }
    
    if(type == 0) {
        std::cout << bigger_year << std::endl;
    } else if (type == 1) {
        std::cout << ans << std::endl;
    }
    
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
        int from, to, year, travel_time, cost;
        std::cin >> from >> to >> year >> travel_time >> cost;

        Edge edge = Edge(from, to, year, travel_time, cost);
        graph[from-1].addEdge(edge);
        
        Edge inverse_edge = Edge(to, from, year, travel_time, cost);
        graph[to-1].addEdge(inverse_edge);
    }
    
    dijkstraAlgorithm(graph);

    kruscalAlgorithm(graph, 0);

    kruscalAlgorithm(graph, 1);
}