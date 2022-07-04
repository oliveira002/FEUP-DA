#ifndef DA_T6_G62_EMPRESA_H
#define DA_T6_G62_EMPRESA_H

#include <string>
#include <algorithm>

#include "graph.h"


class Empresa {
private:
    Graph rede;
public:
    /**
     * Construtor
     * @param g Grafo com rede de transportes da empresa
     */
    explicit Empresa(Graph *g): rede(*g){};

    /**
     * Função para retornar o grafo
     * @return o grafo da rede de transportes
     */
    Graph getGraph() {return rede;};

    /**
     * Função para o cenário 1.1
     * @param s no inicial
     * @param t no final
     */
    void one1(int s, int t);

    /**
    * Função para o cenário 1.2
    * @param s no inicial
    * @param t no final
    */
    void one2(int s, int t);

    /**
    * Função para o cenário 2.3
    * @param s no inicial
    * @param t no final
    */
    void two3(int s, int t);

    /**
    * Função para o cenário 2.1
    * @param s no inicial
    * @param t no final
    */
    void two1(int s, int t);

    /**
    * Função para o cenário 2.4
    * @param s no inicial
    * @param t no final
    */
    void two4(int s, int t);

    /**
    * Função para o cenário 2.5
    * @param s no inicial
    * @param t no final
    */
    void two5(int s, int t);

    /**
    * Função para o cenário 2.4All
    * @param s no inicial
    * @param t no final
    */
    void two4All(int s, int t);

    /**
    * Função para o cenário 2.5All
    * @param s no inicial
    * @param t no final
    */
    void two5All(int s, int t);

    /**
     * Verifica se n existe no path
     * @param path
     * @param n
     * @return true if se existir
     */
    bool checkCommon(vector<int> path, int n);

    /**
     * Função para dar sort 1.2 (operador)
     * @param p1
     * @param p2
     * @return true/false
     */
    static bool sortPair(pair<vector<int>,int> &p1,pair<vector<int>,int> &p2);
};


#endif //DA_T6_G62_EMPRESA_H
