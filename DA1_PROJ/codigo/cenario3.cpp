#include <algorithm>
#include "cenarios.h"

Cenario3::Cenario3(const Empresa& e) {
    encomendasExp = e.getExpEncomendas();
}

bool Cenario3::sortByDuracao(const ExpressoEncomenda* e1, const ExpressoEncomenda* e2) {
    return e1->getDuracao() < e2->getDuracao();
}

int Cenario3::encomendasPorEntregar() {
    int counter = 0;
    for(auto x : encomendasExp) {
        if(!x->getEstado()) {
            counter++;
        }
    }
    return counter;
}


vector<int> Cenario3::greedyMinAvgTime() {
    sort(encomendasExp.begin(), encomendasExp.end(), sortByDuracao);
    double sum = encomendasExp[0]->getDuracao();
    int startTime = 32400 + (int) encomendasExp[0]->getDuracao();// corresponde a 09:00 + a 1st encomenda
    encomendasExp[0]->setEstado(true); // entregue
    int endTime = 61200; // corresponde a 17:00
    int avgTime;
    int numEncomendas = 1;
    int temp = 0;
    vector<int> avgTimeAllDays;
    for(size_t i = 1; i < encomendasExp.size(); i++) {
        if(startTime + (int) encomendasExp[i]->getDuracao() <= endTime) {
            temp += (int) encomendasExp[i-1]->getDuracao();
            sum += temp + encomendasExp[i]->getDuracao();
            numEncomendas++;
            startTime += (int)encomendasExp[i]->getDuracao();
            encomendasExp[i]->setEstado(true);
        }
        else {
            avgTime = (int) sum / numEncomendas;
            avgTimeAllDays.push_back(avgTime);
            quociente.push_back((numEncomendas / (double) (numEncomendas + encomendasPorEntregar())));
            startTime = 32400 + (int) encomendasExp[i]->getDuracao();
            if(startTime > endTime) {
                break;
            }
            if(i == encomendasExp.size() - 1){
                avgTimeAllDays.push_back((int)encomendasExp[i]->getDuracao());
                quociente.push_back((numEncomendas / (double) (numEncomendas + encomendasPorEntregar())));
                break;
            }
            numEncomendas = 1;
            temp = 0;
            sum = encomendasExp[i]->getDuracao();
            encomendasExp[i]->setEstado(true);
        }
    }

    avgTime = (int) sum / numEncomendas;
    if(avgTimeAllDays.empty() || numEncomendas < (int) encomendasExp.size()) {
        avgTimeAllDays.push_back(avgTime);
        quociente.push_back((numEncomendas / (double) (numEncomendas + encomendasPorEntregar())));
    }
    return avgTimeAllDays;
}

vector<double> Cenario3::getQuocientes() {
    return quociente;
}
