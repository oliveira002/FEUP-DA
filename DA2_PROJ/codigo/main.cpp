#include <iostream>
#include <fstream>

#include "graph.h"
#include "menu.h"
#include "empresa.h"

Graph readFile(const string& file) {
    ifstream f;
    f.open(file);
    string nodes, edges;

    getline(f, nodes, ' ');
    Graph g(stoi(nodes), true);
    getline(f, edges);
    for(int i = 0; i < stoi(edges); i++) {
        string origin, destin, capacity, duration;
        getline(f, origin, ' ');
        getline(f, destin, ' ');
        getline(f, capacity, ' ');
        getline(f, duration);
        g.addEdge(stoi(origin), stoi(destin), stoi(duration), stoi(capacity));
    }
    f.clear();
    f.seekg(0, ios::beg);
    f.close();
    return g;
}

int main() {
    Graph g = readFile("../input/in04_b.txt");
    Empresa empresa(&g);
    Menu menu(&empresa);
    menu.start();
    return 0;
}
