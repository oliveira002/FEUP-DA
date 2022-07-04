#ifndef DA_T6_G62_ENCOMENDA_H
#define DA_T6_G62_ENCOMENDA_H

class Encomenda {
private:
    unsigned int vol;
    unsigned int peso;
    unsigned int recompensa;
    double var_decisiva = 1;
    bool prioridade=false;
    bool entregue=false;
public:
    /**
     * Encomenda
     * @param recompensa recompensa da encomenda
     */
     Encomenda(unsigned int vol, unsigned int peso, unsigned int recompensa);

    /**
     * Desconstrutor do objeto Encomenda
     */
    virtual ~Encomenda() = default;

    /**
     * Retorna volume da encomenda
     * @return volume
     */
    unsigned int getVol() const {return vol;};

    /**
     * Retorna peso da encomenda
     * @return peso
     */
    unsigned int getPeso() const {return peso;};

    /**
     * Retorna recompensa da encomenda
     * @return recompensa
     */
    unsigned int getRecompensa() const {return recompensa;};

    /**
     * Retorna se encomenda tem prioridade
     * @return prioridade
     */
    bool getPrioridade() const {return prioridade;};

    /**
     * Retorna estado da encomenda
     * @return entregue
     */
    bool getEstado() const {return entregue;};

    /**
     * Define prioridade da entrega
     * @param _prioridade prioridade
     */
    void setPrioridade(bool const _prioridade) { this->prioridade=_prioridade;};

    /**
     * Define estado da entrega
     * @param _entregue entregue
     */
    void setEstado(bool const _entregue) { this->entregue=_entregue;};

    /**
     * Define variável decisiva, balanço entre peso e volume
     * @param peso_peso percentagem do peso
     * @param peso_vol percentagem do volume
     */
    void setVarDecisiva(double peso_peso, double peso_vol);

    /**
     * Retorna variavel decisiva
     * @return var_decisiva
     */
    double getVarDecisiva() const {return var_decisiva;};

    /**
     * Retorna variavel recompensa/var_decisiva
     * @return Recompensa por Unidade
     */
    double getRecompensaUnidade() const {return recompensa/var_decisiva;};
};

class ExpressoEncomenda: public Encomenda {
private:
    unsigned int duracao;
public:
    /**
     * Encomenda do tipo expresso
     * @param recompensa recompensa da encomenda
     * @param duracao duracao da encomenda ( viagem de ida e volta )
     */
    ExpressoEncomenda(unsigned int vol, unsigned int peso, unsigned int recompensa, unsigned int duracao);

    /**
     * Retorna duracao da encomenda
     * @return duracao
     */
    unsigned int getDuracao() const {return duracao;};

};

class NormalEncomenda: public Encomenda {
private:
public:
    /**
     * Encomenda do tipo normal
     * @param vol volume da encomenda
     * @param peso peso da encomenda
     * @param recompensa recompensa da encomenda
     */
    NormalEncomenda(unsigned int vol, unsigned int peso, unsigned int recompensa);
};

#endif //DA_T6_G62_ENCOMENDA_H
