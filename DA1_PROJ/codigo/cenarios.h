#ifndef DA_T6_G62_CENARIOS_H
#define DA_T6_G62_CENARIOS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

#include "encomenda.h"
#include "carrinha.h"
#include "empresa.h"

struct ENCOMENDA_VALOR{
    long profit = -1;
    std::vector<Encomenda *> CarrinhaEncomenda;
};

    /**
     * A soluçao do senario 1 vai ser usar Top-down Dynamic Programming with Memoization ou seja vamos usar uma soluçao recursiva
     * que vai contruir uma tabela e cima para baixo cujo o tempo de execuçao é igual a uma soluçao Bottom-up Dynamic Programming
     * a catch é que normalmente essas tabelas sao de 2 entradas. Nesta soluçao nos iremos ter que trabalhar inicialmente com uma soluçao
     * de uma tabela de 3 entradas para compensar o facto de termos 2 constraints e mais tarde de 4 entradas para ter em conta as diferentes carrinhas
     */
class Cenario1 {
private:
    std::vector<Encomenda *> encomendas;
    std::vector<Carrinha *> carrinhas;
public:
    /**
     * Constructor Montar argumentos necessarios para o funcionamento do cenario 1
     * @param e Empresa a ser estudada
     */
    explicit Cenario1( Empresa e);


    /**
     * Função responsável pelo job scheduling
     * @complexity Time:O(C * E);
     * @return tempo medio
     */
    int firstFit();

    /**
     * Função para ordenar pela variavel decisiva
     * @param e1 encomenda 1
     * @param e2 encomenda 2
     * @return
     */
    static bool sortByVarEncomenda(const Encomenda* e1, const Encomenda* e2);

    /**
     * Função para ordenar pela variavel decisivaunprofit, profit: 13218, custo: 13476

     * @param c1 encomenda 1
     * @param c2 encomenda 2
     * @return
     */
    static bool sortByVarCarrinha(const Carrinha* c1, const Carrinha* c2);

    /**
     * Quocient encomendas entregues / total
     * @return quocientes entre as entregues e total
     */
    double getQuocient();
};

class Cenario2 {
private:
    std::vector<Encomenda *> encomendas;
    std::vector<Carrinha *> carrinhas;
public:
    /**
     * Constructor Montar argumentos necessarios para o funcionamento do cenario 2
     * @param e Empresa a ser estudada
     */
    explicit Cenario2(const Empresa& e);

    /**
     * Processo de resoluçao da distribuicao das encomendas
     * @complexity Time:O(C * solveKnapsack);
     * @return lucro maximo
     */
    int solveMaxLucro();

    /**
     * Resolve problema atraves de knapsack com programção dinamica
     * @complexity Time:O(V * P * E); Space:O(V * P)
     * @param c carrinha a ser preenchida
     * @param encomendas encomendas a distribuir
     * @return estrutura com encomendas e profit distribuido
     */
    ENCOMENDA_VALOR solveKnapsack(Carrinha &c,vector<Encomenda *> encomendas);

    /**
     * Preparar dataset, ordenar por custo ou recompensa por unidade de medida
     */
    void prepareSolve();

    /**
     * Preparar conjunto de entregas a ser distribuidas
     * @param c carrinha a ser preenchida
     * @return estrutura com encomendas e profit distribuido
     */
    ENCOMENDA_VALOR prepareKnapsack(Carrinha &c);

    /**
     * Função para ordenar pela variavel decisiva
     * @param c1 encomenda 1
     * @param c2 encomenda 2
     * @return
     */
    static bool sortByVarCarrinha(const Carrinha* c1, const Carrinha* c2);

    /**
     * Quocient encomendas entregues / total
     * @return quocientes entre as entregues e total
     */
    double getQuocient();
};

class Cenario3 {
private:
    std::vector<ExpressoEncomenda *> encomendasExp;
    std::vector<double> quociente; // entregues & por entregar
public:

    /**
     * Constructor Montar argumentos necessarios para o funcionamento do cenario 3
     * @param e Empresa a ser estudada
     */
    explicit Cenario3(const Empresa& e);

    /**
     * Função para ordenar por duração
     * @param e1 encomenda 1
     * @param e2 encomenda 2
     * @return
     */
    static bool sortByDuracao(const ExpressoEncomenda* e1, const ExpressoEncomenda* e2);

    /**
     * Função responsável por minimizar o tempo das entregas expresso
     * @complexity Time:O(E);
     * @return o tempo medio minimizado
     */
    vector<int> greedyMinAvgTime();

    /**
     * Função responsável por retornar o número de encomendas que ainda não foram entregues
     * @return o número de encomendas por entregar
     */
    int encomendasPorEntregar();

    /**
     * Função responsável por retornar o vetor dos quocientes entre as encomendas entregues e não entregues
     * @return o vetor dos quocientes dos dias
     */
    vector<double> getQuocientes();

};

#endif //DA_T6_G62_CENARIOS_H
