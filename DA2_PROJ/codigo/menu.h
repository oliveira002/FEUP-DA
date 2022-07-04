#ifndef DA_T6_G62_MENU_H
#define DA_T6_G62_MENU_H

#include "empresa.h"

class Menu {
private:
    Empresa e;
public:
    explicit Menu(Empresa *e): e(*e){}

    /**
     * Mostar Menu
     * @return 0 em caso de sucesso
     */
    int start();

    /**
     * Cenario 1
     * @return 0 em caso de sucesso
     */
    int Cenario1();

    /**
     * Cenario 2
     * @return 0 em caso de sucesso
     */
    int Cenario2();

    /**
     * Cenario 2 dividido em mais opções
     * @return 0 em caso de sucesso
     */
    int CenarioOptions(int s, int t);

};


#endif //DA_T6_G62_MENU_H
