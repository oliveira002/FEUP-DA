#include "carrinha.h"


Carrinha::Carrinha(unsigned int volMax, unsigned int pesoMax, unsigned int custo): volMax(volMax), pesoMax(pesoMax), custo(custo) {}

int Carrinha::adicionarEncomenda(Encomenda *encomenda) {
    if(verificaDisponibilidade(encomenda)) {
        return 1; // encomenda não cabe na carrinha
    }

    encomenda->setEstado(true);
    encomendas.push_back(encomenda);
    vol+=encomenda->getVol();
    peso+=encomenda->getPeso();
    balanco+=(int) encomenda->getRecompensa();
    return 0;
}

int Carrinha::verificaDisponibilidade(Encomenda *encomenda) const {
    if(encomenda->getVol()+vol>volMax || encomenda->getPeso()+peso>pesoMax) {
        return 1; // encomenda não cabe na carrinha
    }
    return 0;
}

void Carrinha::setVarDecisiva(double peso_peso, double peso_vol) {
    var_decisiva = peso_peso*pesoMax + peso_vol*volMax;
}

void Carrinha::clearEncomendas() {
    peso=0;
    vol=0;
    balanco=(int)-custo;
    encomendas.clear();
}
