#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

struct Manobra {
    int pontuacaoBase;
    int tempo;
};

struct Secao {
    int fatorBonificacao;
    int tempoTravessia;
};

struct Resultado {
    int pontuacaoMaxima;
    vector<vector<int>> manobrasPorSecao;
};

// Função para calcular a pontuação total para uma seção considerando as regras de pontuação
int calcularPontuacao(const Secao& secao, const vector<Manobra>& manobras, const vector<int>& escolhidas, const vector<int>& escolhidasPrevSecao) {
    int pontuacaoTotal = 0;
    for (int idx : escolhidas) {
        int pj = manobras[idx].pontuacaoBase;
        if (find(escolhidasPrevSecao.begin(), escolhidasPrevSecao.end(), idx) != escolhidasPrevSecao.end()) {
            pj = floor(pj / 2.0);
        }
        pontuacaoTotal += pj;
    }
    return pontuacaoTotal * escolhidas.size() * secao.fatorBonificacao;
}

// Função para gerar todas as combinações de manobras válidas
void gerarCombinacoes(const vector<Manobra>& manobras, int tempoDisponivel, vector<vector<int>>& combinacoes, vector<int>& atual, size_t start) {
    int somaTempo = 0;
    for (int idx : atual) {
        somaTempo += manobras[idx].tempo;
    }
    if (somaTempo <= tempoDisponivel) {
        combinacoes.push_back(atual);
    }
    for (size_t i = start; i < manobras.size(); ++i) {
        atual.push_back(i);
        gerarCombinacoes(manobras, tempoDisponivel, combinacoes, atual, i + 1);
        atual.pop_back();
    }
}

// Função para calcular a pontuação máxima total e as manobras selecionadas para cada seção
Resultado calcularPontuacaoMaximaPorSecao(const vector<Secao>& secoes, const vector<Manobra>& manobras) {
    size_t N = secoes.size();
    vector<vector<int>> manobrasPorSecao(N);

    // Gerar todas as combinações de manobras válidas para cada seção
    vector<vector<vector<int>>> combinacoesPorSecao(N);
    for (size_t i = 0; i < N; ++i) {
        vector<vector<int>> combinacoes;
        vector<int> atual;
        gerarCombinacoes(manobras, secoes[i].tempoTravessia, combinacoes, atual, 0);
        combinacoesPorSecao[i] = combinacoes;
    }

    // Considerar todas as combinações de seções (incluir ou não cada combinação)
    vector<int> escolhaAtual;
    vector<int> melhorEscolha;
    int melhorPontuacao = 0;

    function<void(size_t, vector<int>, int)> dfs = [&](size_t secaoIdx, vector<int> escolhidasPrevSecao, int pontuacaoAtual) {
        if (secaoIdx == N) {
            if (pontuacaoAtual > melhorPontuacao) {
                melhorPontuacao = pontuacaoAtual;
                melhorEscolha = escolhaAtual;
            }
            return;
        }

        // Não escolher nenhuma manobra para a seção atual
        dfs(secaoIdx + 1, escolhidasPrevSecao, pontuacaoAtual);

        // Escolher cada combinação de manobras para a seção atual
        for (size_t i = 0; i < combinacoesPorSecao[secaoIdx].size(); ++i) {
            const auto& combinacao = combinacoesPorSecao[secaoIdx][i];
            int pontuacaoSecao = calcularPontuacao(secoes[secaoIdx], manobras, combinacao, escolhidasPrevSecao);
            escolhaAtual.push_back(i);
            dfs(secaoIdx + 1, combinacao, pontuacaoAtual + pontuacaoSecao);
            escolhaAtual.pop_back();
        }
    };

    dfs(0, {}, 0);

    // Montar a lista de manobras por seção com base na melhor escolha
    for (size_t i = 0; i < N; ++i) {
        if (i < melhorEscolha.size()) {
            size_t escolhaIdx = melhorEscolha[i];
            if (escolhaIdx < combinacoesPorSecao[i].size()) {
                manobrasPorSecao[i] = combinacoesPorSecao[i][escolhaIdx];
            } else {
                manobrasPorSecao[i].clear(); // Garantir que a seção não tenha manobras se índice inválido
            }
        } else {
            manobrasPorSecao[i].clear(); // Garantir que a seção não tenha manobras se índice inválido
        }
    }

    return {melhorPontuacao, manobrasPorSecao};
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

    // Calcular a pontuação máxima e as manobras selecionadas para cada seção
    Resultado resultado = calcularPontuacaoMaximaPorSecao(secoes, manobras);

    cout << resultado.pontuacaoMaxima << endl;
    for (const auto& manobras : resultado.manobrasPorSecao) {
        cout << manobras.size();
        for (int m : manobras) {
            cout << " " << m + 1;
        }
        cout << endl;
    }

    return 0;
}
