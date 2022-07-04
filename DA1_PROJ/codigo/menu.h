#ifndef DA_T6_G62_MENU_H
#define DA_T6_G62_MENU_H

#include "empresa.h"

class Menu {
private:
    Empresa e;
public:
    /**
     * Menu construtor
     * @param e Empresa a estudar
     */
    explicit Menu(Empresa e);

    /**
     * Mostrar Menu
     * @return 0 quando acabar
     */
    int start();

    /**
     * Cenario 1
     * @return
     */
    int Cenario1();

    /**
     * Cenario 2
     * @return
     */
    int Cenario2();

    /**
     * Cenario 3
     * @return
     */
    int Cenario3();

};


#endif //DA_T6_G62_MENU_H
