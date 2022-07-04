#include <chrono>
#include "empresa.h"

void Empresa::one1(int s, int t) {
    Graph temp = rede;
    rede.MaxCapWays(s);

    vector<int> path;
    vector<int> d = rede.getDistances();
    int groupD = d[t];

    rede.getPath(&path, t);

    cout << "1.1) Dimensão do grupo (sem se separar) máxima entre " << s << " para " << t << ": " << groupD << endl;
    cout << "Número de transbordos: " << path.size() - 1 << endl;
    cout << path[0];
    for (int i = 1; i < path.size(); i++) {
        cout << " -> " << path[i];
    }
    cout << endl;
    rede = temp;
}

void Empresa::one2(int s, int t) {
    Graph temp = rede;
    rede.distance(s, t);

    vector<int> path;
    vector<int> d = rede.getDistances();

    vector<pair<vector<int>,int>> solutions;
    vector<int> pathAux;
    vector<int> capsAux;

    int transbordos = d[t];

    rede.getPath(&path, t);
    int pathCap = rede.pathCapacity(path);

    rede.setPath(path);
    solutions.push_back(pair<vector<int>,int>(path,pathCap));
    while(rede.unusedNodes()>1){
        rede.MaxCapWaysWithUse(s);
        pathAux.clear();
        rede.getPath(&pathAux, t);
        if(solutions.back().first != pathAux){
            solutions.push_back(pair<vector<int>,int>(pathAux,rede.pathCapacity(pathAux)));
        }
        rede.setUseNode();
    }

    sort(solutions.begin(), solutions.end(), sortPair);

    reverse(solutions.begin(), solutions.end());
    pair<vector<int>,int> last;
    if(solutions.size()>0){
        last = solutions[0];
    }
    for(int x = 1; x<solutions.size();x++){
        pair<vector<int>,int> actual = solutions[x];
        if(last.first.size()<actual.first.size() && last.second<actual.second){
            last = actual;
            continue;
        }
        if(last.first.size()==actual.first.size() && last.second<=actual.second){
            last = actual;
            continue;
        }
        solutions.erase(solutions.begin()+x);
        x--;
    }

    cout << "1.2) Mínimo de transbordos entre " << s << " para " << t << ": " << transbordos << endl;
    cout << "Dimensão máxima do grupo (sem se separar): " << pathCap << endl;
    cout << path[0];
    for (int i = 1; i < path.size(); i++) {
        cout << " -> "<< path[i];
    }
    cout << endl;
    for(int z = 1; z <solutions.size();z++){
        cout << endl << "Outra parento-solução: "<< endl;
        cout << "Numero de trasnbordos : "<<solutions[z].first.size() - 1 << endl;
        cout << "Capacidade do grupo :"<< solutions[z].second << endl;
        cout << solutions[z].first[0];
        for (int i = 1; i < solutions[z].first.size(); i++) {
            cout << " -> "<< solutions[z].first[i];
        }
        cout << endl;
    }
    rede = temp;
}

void Empresa::two1(int s, int t) {
    Graph temp = rede;
    int dimension, plus;
    cout << "2.1) Size of the group : \n";
    cin >> dimension;

    vector<vector<int>> paths;
    Graph residual = rede.createResidual();
    int maxFlow = Graph::fordFulkerson(residual, s, t, &paths, dimension);

    if (maxFlow < dimension) cout << "Can only transport " << maxFlow << " persons;" << endl;

    for (auto path : paths) {
        cout << path[0];
        for (int i = 1; i < path.size(); i++) {
            cout << " -> "<< path[i];
        }
        cout << endl;
    }

    cout << "2.2) Add to the group x unities : x -> ";
    cin >> plus;

    int maxCap = rede.checkMaxCap(paths);
    paths.clear();
    if (maxCap < dimension + plus) {
        residual = rede.createResidual();
        Graph::fordFulkerson(residual, s, t, &paths, dimension + plus);
    }

    if(!paths.empty()) cout << "Correção de encaminhamento para maior dimensão do grupo: " << endl;
    else cout << "Não foi necessária correção de encaminhamento" << endl;
    for (auto path : paths) {
        cout << path[0];
        for (int i = 1; i < path.size(); i++) {
            cout << " -> "<< path[i];
        }
        cout << endl;
    }
    temp = rede;
}

void Empresa::two3(int s, int t) {
    Graph temp = rede;
    Graph residual = this->rede.createResidual();
    vector<vector<int>> paths;

    int max_flow = Graph::fordFulkerson(residual, s, t, &paths);
    cout << "2.3) Ford-Fulkerson max_flow : " << max_flow << endl;

    int max_time = 0;
    for (auto path : paths) {
        int time = this->rede.getTime(path);
        max_time = max(max_time, time);

        cout << path[0];
        for (int i = 1; i < path.size(); i++) {
            cout << " -> "<< path[i];

        }
        cout << endl;
    }
    rede = temp;
}

void Empresa::two4(int s, int t) {
    Graph temp = rede;
    cout << "Time after which the groups reunites: " << this->rede.minDuration(s,t) << endl;
    rede = temp;

}

void Empresa::two5(int s, int t) {
    Graph temp = rede;
    this->rede.latestFinish(s,t);
    rede = temp;
}

void Empresa::two4All(int s, int t) {
    Graph temp = rede;
    cout << "Time after which the groups reunites: " << this->rede.minDurationAll(s,t) << endl;
    rede = temp;
}

void Empresa::two5All(int s, int t) {
    Graph temp = rede;
    this->rede.latestFinishAll(s,t);
    rede = temp;
}

bool Empresa::checkCommon(vector<int> path, int n) {
    for(auto x : path) {
        if(x == n) {
            return true;
        }
    }
    return false;
}

bool Empresa::sortPair(pair<vector<int>, int> &p1, pair<vector<int>, int> &p2) {
    if(p1.first.size() == p2.first.size()){
        return p1.second<p2.second;
    }
    return p1.first.size()>p2.first.size();
}
