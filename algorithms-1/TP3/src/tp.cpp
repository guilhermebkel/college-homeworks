#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Manobra {
    int pontuacaoBase;
    int tempo;
};

struct Secao {
    int fatorBonificacao;
    int tempoTravessia;
};

// Função para calcular a pontuação total para uma seção considerando as regras de pontuação
int calcularPontuacao(const Secao& secao, const vector<Manobra>& manobras, const vector<int>& escolhidas, const vector<int>& escolhidasPrevSecao) {
    int pontuacaoTotal = 0;
    for (int idx : escolhidas) {
        int pj = manobras[idx].pontuacaoBase;
        // Aplicar penalização se a manobra foi usada na seção anterior
        if (find(escolhidasPrevSecao.begin(), escolhidasPrevSecao.end(), idx) != escolhidasPrevSecao.end()) {
            pj = floor(pj / 2.0);
        }
        pontuacaoTotal += pj;
    }
    // Multiplicar pela bonificação e pelo número de manobras
    return pontuacaoTotal * escolhidas.size() * secao.fatorBonificacao;
}

// Função para gerar todas as combinações de manobras válidas
void gerarCombinacoes(const vector<Manobra>& manobras, int tempoDisponivel, vector<vector<int>>& combinacoes, vector<int>& atual, int start) {
    int somaTempo = 0;
    for (int idx : atual) {
        somaTempo += manobras[idx].tempo;
    }
    if (somaTempo <= tempoDisponivel) {
        combinacoes.push_back(atual);
    }
    for (int i = start; i < manobras.size(); ++i) {
        atual.push_back(i);
        gerarCombinacoes(manobras, tempoDisponivel, combinacoes, atual, i + 1);
        atual.pop_back();
    }
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
        vector<vector<int>> combinacoes;
        vector<int> atual;

        // Gerar todas as combinações de manobras válidas para a seção atual
        gerarCombinacoes(manobras, secoes[i].tempoTravessia, combinacoes, atual, 0);

        // Avaliar cada combinação
        for (const auto& combinacao : combinacoes) {
            int pontuacaoAtual = calcularPontuacao(secoes[i], manobras, combinacao, i > 0 ? manobrasPorSecao[i-1] : vector<int>());

            if (pontuacaoAtual > melhorPontuacao) {
                melhorPontuacao = pontuacaoAtual;
                melhorEscolha = combinacao;
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
