#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <algorithm>
#include <functional> // Para std::function

using namespace std;

struct Vertex {
    int d; // distância mínima em termos de tempo
    int hops; // número de saltos
    int pi; // predecessor
    Vertex() : d(INT_MAX), hops(INT_MAX), pi(-1) {}
};

struct Edge {
    int from;
    int to;
    int year;
    int travel_time;
    int cost;
};

using Graph = vector<vector<Edge>>;

// Função para explorar o grafo considerando o tempo
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

// Função para encontrar os tempos mínimos de viagem
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

int find_max_year(const Graph& graph) {
    int max_year = INT_MIN; // Inicializa com o menor valor possível de int

    for (const auto& edges : graph) {
        for (const auto& edge : edges) {
            if (edge.year > max_year) {
                max_year = edge.year;
            }
        }
    }

    return max_year;
}

// Função para encontrar o ano em que todos os vértices são mutuamente alcançáveis
int find_year_all_mutually_reachable(const Graph& graph) {
    // heurística: a construtora sempre vai construir todos os canais, então no ultimo ano de construção todos canais serão mutuamente alcançáveis.
    return find_max_year(graph);
}

bool is_all_reachable(const Graph& graph, int start, int t) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> Q;
    Q.push(start);
    visited[start] = true;
    int reachable_count = 1;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            if (!visited[v] && edge.year <= t) {
                visited[v] = true;
                Q.push(v);
                reachable_count++;
            }
        }
    }

    return reachable_count == n;
}

// Função para encontrar o ano em que todos os vértices são alcançáveis
int find_year_all_reachable(const Graph& graph, int start, int tmin, int tmax) {
    for (int t = tmin; t <= tmax; ++t) {
        if (is_all_reachable(graph, start, t)) {
            return t;
        }
    }

    return -1; // Retorna -1 se não for possível alcançar todos os vértices até tmax
}

// Função para encontrar o menor custo necessário para conectar todo o reino
int find_min_cost_mst(int N, vector<Edge>& edges) {
    // Ordena as arestas pelo custo
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
    });

    // Disjoint Set Union (DSU) ou Union-Find para gerenciar componentes conectados
    vector<int> parent(N), rank(N, 0);
    for (int i = 0; i < N; ++i) parent[i] = i;

    function<int(int)> find = [&](int u) {
        if (u != parent[u]) parent[u] = find(parent[u]);
        return parent[u];
    };

    auto unite = [&](int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    };

    int min_cost = 0;
    for (const Edge& edge : edges) {
        if (find(edge.from) != find(edge.to)) {
            unite(edge.from, edge.to);
            min_cost += edge.cost;
        }
    }

    return min_cost;
}

int main() {
    int N, M;
    cin >> N >> M;

    Graph graph(N);
    vector<Edge> edges;

    for (int i = 0; i < M; ++i) {
        int u, v, a, l, c;
        cin >> u >> v >> a >> l >> c;
        --u; --v; // assumindo que os vértices de entrada são 1-based
        graph[u].push_back({u, v, a, l, c});
        graph[v].push_back({v, u, a, l, c});
        edges.push_back({u, v, a, l, c});
    }

    int start = 0; // assumindo que o palácio está no vértice 0
    int tmin = 0;  // tempo inicial mínimo
    int tmax = 1000; // tempo máximo (ou um valor apropriado para o seu caso)
    
    vector<int> min_times = find_min_travel_times(graph, start, tmin, tmax);
    int min_cost = find_min_cost_mst(N, edges);
    int year_all_reachable = find_year_all_reachable(graph, start, tmin, tmax);
    int year_all_mutually_reachable = find_year_all_mutually_reachable(graph);

    for (int i = 0; i < N; ++i) {
        if (min_times[i] == -1) {
            cout << "INF" << endl;
        } else {
            cout << min_times[i] << endl;
        }
    }

    cout << year_all_mutually_reachable << endl;

    cout << year_all_reachable << endl;

    cout << min_cost << endl;

    return 0;
}