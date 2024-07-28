#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <algorithm>
#include <functional>
#include <set> // Para armazenar anos únicos

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
vector<int> find_min_travel_times(const Graph& graph, int start) {
    int n = graph.size();
    vector<Vertex> V(n);
    V[start].d = 0;
    V[start].hops = 0;
    V[start].pi = -1;

    earliest_arrival_bfs_explore(graph, V, start, 0);

    vector<int> min_times(n);

    for (int i = 0; i < n; ++i) {
        min_times[i] = V[i].d;
    }

    return min_times;
}

// Função para verificar se todos os vértices são alcançáveis até o ano t
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
int find_year_all_reachable(const Graph& graph, int start, const set<int>& years) {
    auto it = years.begin();
    int tmin = *it;
    int tmax = *(--years.end());

    while (tmin < tmax) {
        int mid = tmin + (tmax - tmin) / 2;
        if (is_all_reachable(graph, start, mid)) {
            tmax = mid;
        } else {
            tmin = mid + 1;
        }
    }

    return is_all_reachable(graph, start, tmin) ? tmin : -1;
}

// Função para encontrar o menor custo necessário para conectar todo o reino (MST)
int find_min_cost_mst(int N, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
    });

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

// Função para verificar se existe um caminho com exatamente N-1 arestas até o ano t usando DFS
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

// Função para encontrar o ano em que existe um caminho de comprimento N-1
int find_year_all_mutually_reachable(const Graph& graph, const set<int>& years) {
    int n = graph.size();
    vector<bool> visited(n, false);
    for (int year : years) {
        if (has_path_with_n_minus_1_edges(graph, 0, n - 1, n - 1, year, visited)) {
            return year;
        }
    }
    return -1; // Se não houver ano que satisfaça a condição
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
        if (min_times[i] == -1) {
            cout << "INF" << endl;
        } else {
            cout << min_times[i] << endl;
        }
    }

    int year_all_mutually_reachable = find_year_all_mutually_reachable(graph, years);
    cout << year_all_mutually_reachable << endl;

    int year_all_reachable = find_year_all_reachable(graph, start, years);
    cout << year_all_reachable << endl;

    int min_cost = find_min_cost_mst(N, edges);
    cout << min_cost << endl;

    return 0;
}
