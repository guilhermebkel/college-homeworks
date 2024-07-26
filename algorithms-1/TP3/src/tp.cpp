#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct Manobra {
    int pontuacaoBase;
    int tempo;
};

struct Secao {
    int fatorBonificacao;
    int tempoTravessia;
};

// Função para calcular a pontuação total para uma seção
int calcularPontuacao(const Secao& secao, const vector<Manobra>& manobras, const vector<int>& escolhidas) {
    int pontuacaoTotal = 0;
    for (int idx : escolhidas) {
        int pj = manobras[idx].pontuacaoBase;
        pontuacaoTotal += pj;
    }
    return pontuacaoTotal * secao.fatorBonificacao;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<Secao> secoes(N);
    for (int i = 0; i < N; ++i) {
        cin >> secoes[i].fatorBonificacao >> secoes[i].tempoTravessia;
    }

    vector<Manobra> manobras(K);
    for (int j = 0; j < K; ++j) {
        cin >> manobras[j].pontuacaoBase >> manobras[j].tempo;
    }

    int pontuacaoMaxima = 0;
    vector<vector<int>> manobrasPorSecao(N);

    for (int i = 0; i < N; ++i) {
        int melhorPontuacao = 0;
        vector<int> melhorEscolha;

        for (int j = 0; j < K; ++j) {
            if (manobras[j].tempo <= secoes[i].tempoTravessia) {
                vector<int> escolhaAtual = {j};
                int pontuacaoAtual = calcularPontuacao(secoes[i], manobras, escolhaAtual);

                if (pontuacaoAtual > melhorPontuacao) {
                    melhorPontuacao = pontuacaoAtual;
                    melhorEscolha = escolhaAtual;
                }
            }
        }

        pontuacaoMaxima += melhorPontuacao;
        manobrasPorSecao[i] = melhorEscolha;
    }

    cout << pontuacaoMaxima << endl;
    for (const auto& manobras : manobrasPorSecao) {
        cout << manobras.size();
        for (int m : manobras) {
            cout << " " << m + 1;
        }
        cout << endl;
    }

    return 0;
}
