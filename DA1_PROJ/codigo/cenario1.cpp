#include <algorithm>
#include "cenarios.h"

using namespace std;

Cenario1::Cenario1(Empresa e) {
    this->encomendas = e.getEncomendas();
    this->carrinhas = e.getCarrinhas();
}

bool Cenario1::sortByVarCarrinha(const Carrinha *c1, const Carrinha *c2) {
    return c1->getVarDecisiva() > c2->getVarDecisiva();
}

bool Cenario1::sortByVarEncomenda(const Encomenda *e1, const Encomenda *e2) {
    if(e1->getPrioridade()!=e2->getPrioridade()) return e1->getPrioridade() > e2->getPrioridade();
    return e1->getVarDecisiva() > e2->getVarDecisiva();
}

int Cenario1::firstFit() {
    sort(encomendas.begin(),encomendas.end(), sortByVarEncomenda);
    sort(carrinhas.begin(),carrinhas.end(), sortByVarCarrinha);
    int numEntregues = 0;
    int numCarrinhas = 0;
    for(auto & carrinha : carrinhas) {
        for(auto & encomenda : encomendas) {
            if(encomenda->getEstado()) {
                continue;
            }
            carrinha->adicionarEncomenda(encomenda);
        }
    }
    for(auto x : carrinhas) {
        if(!x->getEncomendas()->empty()) {
            numCarrinhas++;
        }
    }
    return numCarrinhas;
}

double Cenario1::getQuocient() {
    int counter = 0;
    for(auto x : encomendas) {
        if(x->getEstado()) {
            counter++;
        }
    }
    return(counter / (double) encomendas.size());
}
