#include "cenarios.h"
//#include "dpmatrix.h"

Cenario2::Cenario2(const Empresa &e) {
    this->encomendas = e.getEncomendas();
    this->carrinhas = e.getCarrinhas();
}

bool Cenario2::sortByVarCarrinha(const Carrinha *c1, const Carrinha *c2) {
    return c1->getCustoUnidade() < c2->getCustoUnidade();
}

ENCOMENDA_VALOR Cenario2::solveKnapsack(Carrinha &c, vector<Encomenda *> encomendas) {
    if (!c.getEncomendas()->empty()) return {};
    int n = (int) encomendas.size();
    // dp[index][volume][peso]
    vector<vector<vector<ENCOMENDA_VALOR>>> dp(2,vector<vector<ENCOMENDA_VALOR>>(c.getVolMax() + 1,vector<ENCOMENDA_VALOR>(c.getPesoMax() + 1,ENCOMENDA_VALOR())));

    int cGetVol = (int) c.getVolMax(), cGetPeso = (int) c.getPesoMax();

    for (int i = 0; i <= n; i++) {
        int eVol, ePes, eRec; // vars da encomenda a ser iterada
        if (i != 0) {
            if (encomendas[i - 1]->getEstado()) { // entregue
                continue;
            }
            eVol = (int) encomendas[i - 1]->getVol(), ePes = (int) encomendas[i -1]->getPeso(), eRec = (int) encomendas[i -1]->getRecompensa();
        }
        // preencher tabela dynamic programming
        for (int v = 0; v <= cGetVol; v++) {
            for (int w = 0; w <= cGetPeso; w++) {
                if (i == 0 || v == 0 || w == 0) {
                    dp[i % 2][v][w].profit = 0;
                    continue;
                }
                if (eVol <= v && ePes <= w) { // encomenda cabe na celula da tabela
                    // adicionar encomenda atualmente a ser iterada
                    if ((encomendas[i - 1]->getPrioridade() ? eRec * 4 : eRec) +
                        dp[(i - 1) % 2][v - eVol][w - ePes].profit > dp[(i - 1) % 2][v][w].profit) {
                        dp[i % 2][v][w] = dp[(i - 1) % 2][v - eVol][w - ePes];
                        dp[i % 2][v][w].profit += encomendas[i - 1]->getPrioridade() ? eRec * 4 : eRec;
                        dp[i % 2][v][w].CarrinhaEncomenda.push_back(encomendas[i - 1]);
                    } else { // nao compensa adicionar encomenda atualmente a ser iterada
                        dp[i % 2][v][w] = dp[(i - 1) % 2][v][w];
                    }
                } else // encomenda a ser iterada nao cabe, dp igual a linha anterior
                    dp[i % 2][v][w] = dp[(i - 1) %
                                         2][v][w];
            }
        }
    }
    return dp[n % 2][cGetVol][cGetPeso];
}

int Cenario2::solveMaxLucro() {
    prepareSolve(); // preparação dos datasets

    int profit = 0, unprofit = 0;
    int nr_carrinhas = 0, nr_encomendas = 0;
    cout << "Encomendas do dia: " << encomendas.size() << endl;
    for (auto &carrinha: carrinhas) {
        ENCOMENDA_VALOR solved = prepareKnapsack(*carrinha); // knapsack

        int peso = 0, vol = 0, money = 0;
        for (auto &i: solved.CarrinhaEncomenda) {
            peso += (int) i->getPeso();
            vol += (int) i->getVol();
            money += (int) i->getRecompensa();
        }

        if (solved.profit == -5 || unprofit == 3) { // nao existem mais encomendas por entregar
            break;
        } else if (money - (int) carrinha->getCusto() < 0) { // nao existe profit para configuracao
            unprofit++;
            continue;
        }
        unprofit = 0; // reset unprofit combo

        for (auto &n: solved.CarrinhaEncomenda) {
            carrinha->adicionarEncomenda(n);
            nr_encomendas++;
        }
        nr_carrinhas++;
        profit += carrinha->getBalanco();
    }
    cout << "Total de carrinhas: " << nr_carrinhas << ", Balanco: " << profit << ", Encomendas entregues: "
         << nr_encomendas << endl;
    return profit;
}

void Cenario2::prepareSolve() {
    sort(carrinhas.begin(), carrinhas.end(), sortByVarCarrinha);
}

ENCOMENDA_VALOR Cenario2::prepareKnapsack(Carrinha &c) {
    vector<Encomenda *> e;
    for (auto &encomenda: encomendas) {
        if (!encomenda->getEstado()) {
            e.push_back(encomenda); // encomendas por entregar
        }
    }
    if (e.empty()) { // tudo entregue
        ENCOMENDA_VALOR v;
        v.profit = -5;
        return v;
    }

    return solveKnapsack(c, e);
}

double Cenario2::getQuocient() {
    int counter = 0;
    for (auto x: encomendas) {
        if (x->getEstado()) {
            counter++;
        }
    }
    return (counter / (double) encomendas.size());
}
