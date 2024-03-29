#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>

using namespace std;

struct Ponto {
    double x, y;
};

struct Vertice {
    int id;
    Ponto ponto;
    vector<int> neighborVerticesIds;
};

// Estrutura para representar uma aresta do grafo
struct Aresta {
    int u, v; // Identificadores dos vértices
    Ponto pontoU, pontoV; // Coordenadas dos vértices
};

// Determina se o ponto c está à esquerda, à direita ou na reta definida pelos pontos a e b.
int TipoCurva(Ponto a, Ponto b, Ponto c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // esquerda.
    if (v > 0) return +1; // direita.
    return 0; // em frente.
}

// Verifica se os segmentos de linha ab e cd se intersectam.
bool IntersecaoSegmentos(Ponto a, Ponto b, Ponto c, Ponto d) {
    int t1 = TipoCurva(a, b, c) * TipoCurva(a, b, d);
    int t2 = TipoCurva(c, d, a) * TipoCurva(c, d, b);
    return t1 <= 0 && t2 <= 0;
}

// Função para encontrar os vértices que compõem cada face
vector<vector<int>> EncontrarVerticesPorFace(const vector<Vertice>& vertices) {
    vector<vector<int>> faces;
    vector<Aresta> arestas;

    // Criar as arestas a partir dos vértices
    for (const Vertice& v : vertices) {
        for (int neighborId : v.neighborVerticesIds) {
            arestas.push_back({v.id, neighborId, v.ponto, vertices[neighborId - 1].ponto});
        }
    }

    // Conjunto para verificar se uma face já foi encontrada
    unordered_set<int> facesEncontradas;

    // Encontrar os vértices que compõem cada face
    for (size_t i = 0; i < arestas.size(); ++i) {
        const Aresta& aresta = arestas[i];

        if (facesEncontradas.count(i) == 0) { // Verificar se a face já foi encontrada
            vector<int> face;
            unordered_set<int> verticesAdicionados; // Para garantir que os vértices não se repitam
            for (size_t j = i; j < arestas.size(); ++j) {
                const Aresta& outra = arestas[j];
                if (IntersecaoSegmentos(aresta.pontoU, aresta.pontoV, outra.pontoU, outra.pontoV)) {
                    if (verticesAdicionados.count(outra.u) == 0) {
                        face.push_back(outra.u);
                        verticesAdicionados.insert(outra.u);
                    }
                    if (verticesAdicionados.count(outra.v) == 0) {
                        face.push_back(outra.v);
                        verticesAdicionados.insert(outra.v);
                    }
                    facesEncontradas.insert(j); // Marcar que essa aresta pertence à face atual
                }
            }
            if (verticesAdicionados.count(aresta.u) == 0) {
                face.push_back(aresta.u);
            }
            if (verticesAdicionados.count(aresta.v) == 0) {
                face.push_back(aresta.v);
            }
            facesEncontradas.insert(i); // Marcar que essa aresta pertence à face atual
            faces.push_back(face);
        }
    }

    return faces;
}

int main() {
    // Defina seus vértices
    Vertice vertices[] = {
        {1, {0, 0}, {2, 3}},
        {2, {1, 1}, {1, 4, 5, 7}},
        {3, {1, -1}, {1, 4, 5, 6, 7}},
        {4, {2, 0}, {2, 3}},
        {5, {4, 0}, {2, 3, 6}},
        {6, {4, -1.5}, {3, 5}},
        {7, {-3, 0}, {2, 3, 8}},
        {8, {-2, 0}, {7}}
    };

    vector<Vertice> verticesList(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));

    // Encontre os vértices que compõem cada face
    vector<vector<int>> faces = EncontrarVerticesPorFace(verticesList);

    // Exemplo de saída
    for (size_t i = 0; i < faces.size(); ++i) {
        cout << "Face " << i+1 << ": ";
        for (int vertexId : faces[i]) {
            cout << vertexId << " ";
        }
        cout << endl;
    }

    return 0;
}
