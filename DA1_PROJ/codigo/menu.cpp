#include "menu.h"
#include "cenarios.h"
#include <iomanip>
#include <iostream>

using namespace std;

Menu::Menu(Empresa e){
    this->e = e;
}

int Menu::start() {
    int option=-1;

    cout << "Bem vindo, qual dos seguintes cenário pretende explorar de forma a implementar na plataforma digital:\n";
    cout << "1) Cenario 1\n";
    cout << "2) Cenario 2\n";
    cout << "3) Cenario 3\n";
    cout << "5) Reset encomendas\n";

    while(option) {
        cout << "\nInsere opção (0 para sair, 5 reset encomendas):\n";
        cin >> option;
        switch (option) {
            case 1:
                Cenario1();
                break;
            case 2:
                Cenario2();
                break;
            case 3:
                Cenario3();
                e.removerEncomendas();
                break;
            case 5:
                e.removerEncomendas();
                break;
            default:
                break;
        }

        string f = e.getFileEncomendas();
        e.novoDia(&f);
    }
    return 0;
}

int Menu::Cenario1() {
    class Cenario1 c1(e);
    cout << "Número de carrinhas usadas para entregar: " << c1.firstFit() << endl;
    cout << fixed;
    cout << setprecision(2);
    cout << "Percentagem encomendas entregues: " << (c1.getQuocient() * 100) << "%" << endl;
    return 0;
}

int Menu::Cenario2() {
    class Cenario2 c2(e);
    c2.solveMaxLucro();
    cout << fixed;
    cout << setprecision(2);
    cout << "Percentagem encomendas entregues: " << (c2.getQuocient() * 100) << "%" << endl;
    return 0;
}

int Menu::Cenario3() {
    vector<int>avg;
    vector<double>quo;
    cout << "Número de encomendas a entregar: " << e.getExpEncomendas().size() << endl;
    class Cenario3 c3(e);
    avg = c3.greedyMinAvgTime();
    quo = c3.getQuocientes();

    int numeroDias = 1;
    for(size_t i = 0; i <avg.size(); i++) {
        cout << "Dia: " << numeroDias << endl;
        cout << "Tempo Médio: " << avg[i] << endl;
        cout << fixed;
        cout << setprecision(2);
        cout << "Percentagem encomendas entregues: " << (quo[i] * 100) << "%" << std::endl;
        if(i != avg.size() - 1) {
            cout << "--------------------------------------------------" << std::endl;
        }
        numeroDias++;
    }
    return 0;
}
