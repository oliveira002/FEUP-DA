#ifndef DA_T4_G62_EMPRESA_H
#define DA_T4_G62_EMPRESA_H

#include <string>
#include <vector>

#include "encomenda.h"
#include "carrinha.h"

using namespace std;

class Empresa {
private:
    vector<Encomenda *> encomendas;
    vector<Carrinha *> carrinhas;
    vector<ExpressoEncomenda *> expEncomendas;

    string fileEncomendas, fileCarrinhas;

    double pesoPeso=0.5;
    double pesoVol=0.5;
    void balancaVars();
public:
    /**
     * Constructor
     */
    Empresa() = default;

    /**
     * Constructor
     * @param fileEncomendas localizacao do ficheiro de carrinhas.txt
     * @param fileCarrinhas localizacao do ficheiro encomendas.txt
     */
    Empresa(string fileEncomendas, string fileCarrinhas);

    /**
     * Ler ficheiro de encomendas para o dia
     * @param fileEncomendas
     */
    void novoDia(string *fileEncomendas);

    /**
     * Função responsável por ler o ficheiro das carrinhas
     * @param fileName localizacao do ficheiro de carrinhas.txt
     */
    void lerCarrinhas(string *fileName);

    /**
     * Função responsável por ler o ficheiro das encomendas
     * @param fileName localizacao do ficheiro encomendas.txt
     */
    void lerEncomendas(string *fileName);

    /**
     * Retorna vetor de encomendas
     * @return encomendas
     */
    vector<Encomenda *> getEncomendas() const {return encomendas;};

    /**
     * Retorna vetor de carrinhas
     * @return carrinhas
     */
    vector<Carrinha *> getCarrinhas() const {return carrinhas;};

    /**
     * Retorna vetor de encomendas expresso
     * @return encomendas
     */
    vector<ExpressoEncomenda *> getExpEncomendas() const {return expEncomendas;};

    /**
     * Remover todas as encomendas
     */
    void removerEncomendas();

    /**
     * Retorna o peso do volume na variável
     * @return o peso do volume na variável
     */
    double getPesoVol() const {return pesoVol;};

    /**
     * Retorna o "peso" do peso na variável
     * @return o "peso" do peso na variável
     */
    double getPesoPeso() const {return pesoPeso;};

    /**
     * Retorna a localizacao do ficheiro encomendas
     * @return localizacao do ficheiro
     */
    string getFileEncomendas() const {return fileEncomendas;};
};


#endif //DA_T4_G62_EMPRESA_H
