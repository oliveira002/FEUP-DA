#include "menu.h"
#include "empresa.h"

int Menu::start() {
    int option = -1;

    Graph g = e.getGraph();
    cout << "Bem vindo\n";
    cout << "1) Cenário 1\n";
    cout << "2) Cenário 2\n";

    while (option) {
        cout << "\nInsere opção (0 para sair)\n";
        cin >> option;

        switch (option) {
            case 1:
                if (!Cenario1()) {
                    cout << endl;
                    cout << "1) Cenário 1\n";
                    cout << "2) Cenário 2\n";
                }
                break;
            case 2:
                if (!Cenario2()) {
                    cout << endl;
                    cout << "1) Cenário 1\n";
                    cout << "2) Cenário 2\n";
                }
                break;
            default:
                break;
        }
    }
    return 0;
}

int Menu::Cenario1() {
    int s, t, option = -1;
    cout << "Starting point: "; cin >> s;
    cout << "Ending point: "; cin >> t;

    cout << "1) 1.1\n2) 1.2\n";
    while (option) {
        cout << "Insere opção (0 para sair)\n";
        cin >> option;

        switch (option) {
            case 1:
                e.one1(s, t);
                break;
            case 2:
                e.one2(s, t);
                break;
            default:
                break;
        }
    }

    return 0;
}

int Menu::Cenario2() {
    int s, t, option = -1;
    cout << "Starting point: "; cin >> s;
    cout << "Ending point: "; cin >> t;

    cout << "1) 2.1-2.2\n2) 2.3\n3) 2.4-2.5\n";
    while (option) {
        cout << "Insere opção (0 para sair)\n";
        cin >> option;

        switch (option) {
            case 1:
                e.two1(s, t);
                break;
            case 2:
                e.two3(s, t);
                break;
            case 3:
                CenarioOptions(s,t);
                break;
            default:
                break;
        }
    }
    return 0;
}

int Menu::CenarioOptions(int s, int t) {
    int option = -1;
    cout << "1) All paths\n";
    cout << "2) Previous paths\n";
    while (option) {
        cout << "Insere opção (0 para sair)\n";
        cin >> option;

        switch (option) {
            case 1:
                e.two4All(s,t);
                e.two5All(s,t);
                break;
            case 2:
                e.two4(s,t);
                e.two5(s,t);
                break;
            default:
                break;
        }
    }
}