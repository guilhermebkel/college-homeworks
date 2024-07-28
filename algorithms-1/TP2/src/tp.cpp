#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <algorithm>
#include <functional>
#include <set>

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

struct UnionFind {
    vector<int> parent, rank;
    int components;

    UnionFind(int n) : parent(n), rank(n, 0), components(n) {
         for (int i = 0; i < n; ++i) {
            parent[i] = i;
         }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }

        return parent[u];
    }

    void unite(int u, int v) {
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

            components--;
        }
    }
};

using Graph = vector<vector<Edge>>;

// Função para encontrar os tempos mínimos de viagem
vector<int> find_min_travel_times(const Graph& graph, int start) {
    int n = graph.size();
    vector<Vertex> V(n);
    V[start].d = 0;
    V[start].hops = 0;
    V[start].pi = -1;

    queue<int> Q;
    Q.push(start);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            if (V[v].d > V[u].d + edge.travel_time) {
                V[v].d = V[u].d + edge.travel_time;
                V[v].pi = u;
                V[v].hops = V[u].hops + 1;
                Q.push(v);
            }
        }
    }

    vector<int> min_times(n);

    for (int i = 0; i < n; ++i) {
        min_times[i] = V[i].d;
    }

    return min_times;
}

// Função para encontrar o ano em que todos os vértices são alcançáveis
int find_year_all_reachable(const Graph& graph, int start, const set<int>& years, const vector<Edge>& edges) {
   auto is_all_reachable = [&](int t) {
        UnionFind uf(graph.size());

        for (const Edge& edge : edges) {
            if (edge.year <= t) {
                uf.unite(edge.from, edge.to);
            }
        }

        return uf.components == 1;
    };

    auto it = years.begin();
    int tmin = *it;
    int tmax = *(--years.end());

    while (tmin < tmax) {
        int mid = tmin + (tmax - tmin) / 2;

        if (is_all_reachable(mid)) {
            tmax = mid;
        } else {
            tmin = mid + 1;
        }
    }

    return is_all_reachable(tmin) ? tmin : -1;
}

// Função para encontrar o menor custo necessário para conectar todo o reino (MST)
int find_min_cost_mst(int N, vector<Edge>& edges) {
     sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
    });

    UnionFind uf(N);

    int min_cost = 0;

    for (const Edge& edge : edges) {
        if (uf.find(edge.from) != uf.find(edge.to)) {
            uf.unite(edge.from, edge.to);
            min_cost += edge.cost;
        }
    }

    return min_cost;
}

// Função para verificar se existe um caminho de comprimento N-1 até o ano t
bool has_path_with_n_minus_1_edges(const Graph& graph, int u, int target, int edges, int t, vector<bool>& visited) {
    if (edges == 0) {
        return u == target;
    }

    visited[u] = true;

    for (const Edge& edge : graph[u]) {
        if (edge.year <= t && !visited[edge.to]) {
            if (has_path_with_n_minus_1_edges(graph, edge.to, target, edges - 1, t, visited)) {
                return true;
            }
        }
    }

    visited[u] = false;

    return false;
}

// Função para encontrar o ano em que existe um caminho de comprimento N-1 a partir de tmin
int find_year_all_mutually_reachable(const Graph& graph, const set<int>& years, int tmin) {
    int n = graph.size();
    vector<bool> visited(n, false);
    
    auto it = years.lower_bound(tmin);
    
    while (it != years.end()) {
        int year = *it;
        if (has_path_with_n_minus_1_edges(graph, 0, n - 1, n - 1, year, visited)) {
            return year;
        }
        ++it;
    }

    return -1;
}

int main() {
    int N, M;
    cin >> N >> M;
    Graph graph(N);
    vector<Edge> edges;
    set<int> years;

    for (int i = 0; i < M; ++i) {
        int from, to, year, travel_time, cost;
        cin >> from >> to >> year >> travel_time >> cost;

        --from; --to;

        graph[from].push_back({ .from = from, .to = to, .year = year, .travel_time = travel_time, .cost = cost });
        graph[to].push_back({ .from = to, .to = from, .year = year, .travel_time = travel_time, .cost = cost });
        edges.push_back({ .from = from, .to = to, .year = year, .travel_time = travel_time, .cost = cost });

        years.insert(year);
    }

    int start = 0; // assumindo que o palácio está no vértice 0

    vector<int> min_times = find_min_travel_times(graph, start);
    for (int i = 0; i < N; ++i) {
        cout << min_times[i] << endl;
    }

    int year_all_reachable = find_year_all_reachable(graph, start, years, edges);
    int year_all_mutually_reachable = find_year_all_mutually_reachable(graph, years, year_all_reachable);
    int min_cost = find_min_cost_mst(N, edges);

    cout << year_all_mutually_reachable << endl;
    cout << year_all_reachable << endl;
    cout << min_cost << endl;

    return 0;
}
