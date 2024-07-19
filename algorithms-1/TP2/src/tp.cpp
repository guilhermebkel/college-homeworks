#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits> // Para incluir INT_MAX

using namespace std;

struct Vertex {
    int d; // distância mínima em termos de tempo
    int hops; // número de saltos
    int pi; // predecessor
    Vertex() : d(INT_MAX), hops(INT_MAX), pi(-1) {}
};

struct Edge {
    int to;
    int year;
    int travel_time;
    int cost;
};

using Graph = vector<vector<Edge>>;

void earliest_arrival_bfs_explore(const Graph& G, vector<Vertex>& V, int r, int t) {
    queue<int> Q;
    Q.push(r);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (const Edge& edge : G[u]) {
            int v = edge.to;
            if (edge.year >= t && V[v].d > V[u].d + edge.travel_time) {
                V[v].d = V[u].d + edge.travel_time;
                V[v].pi = u;
                V[v].hops = V[u].hops + 1;
                Q.push(v);
            }
        }
    }
}

vector<int> find_min_travel_times(const Graph& graph, int start, int tmin, int tmax) {
    int n = graph.size();
    vector<Vertex> V(n);

    V[start].d = tmin;
    V[start].hops = 0;
    V[start].pi = -1;

    for (int t = tmin; t <= tmax; ++t) {
        for (int u = 0; u < n; ++u) {
            if (V[u].d <= t) {
                earliest_arrival_bfs_explore(graph, V, u, t);
            }
        }
    }

    vector<int> min_times(n);
    for (int i = 0; i < n; ++i) {
        min_times[i] = V[i].d == INT_MAX ? -1 : V[i].d;
    }

    return min_times;
}

int main() {
    int N, M;
    cin >> N >> M;

    Graph graph(N);

    for (int i = 0; i < M; ++i) {
        int u, v, a, l, c;
        cin >> u >> v >> a >> l >> c;
        --u; --v; // assumindo que os vértices de entrada são 1-based
        graph[u].push_back({v, a, l, c});
        graph[v].push_back({u, a, l, c});
    }

    int start = 0; // assumindo que o palácio está no vértice 0
    int tmin = 0;  // tempo inicial mínimo
    int tmax = 1000; // tempo máximo (ou um valor apropriado para o seu caso)
    
    vector<int> min_times = find_min_travel_times(graph, start, tmin, tmax);

    for (int i = 0; i < N; ++i) {
        if (min_times[i] == -1) {
            cout << "INF" << endl;
        } else {
            cout << min_times[i] << endl;
        }
    }

    return 0;
}
