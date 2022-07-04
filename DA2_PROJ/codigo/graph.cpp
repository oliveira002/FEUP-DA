
#include "graph.h"
#include <map>
#include <algorithm>
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1), ES(num+1), LF(num+1){
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight, int capacity, int flow) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, capacity, flow});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, capacity, flow});
}

// Depth-First Search: example implementation
int Graph::dfs(int v) {
    int size = 1;
    cout << v << " "; // show node order
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            size += dfs(w);
    }
    return size;
}

// Depth-First Search: example implementation
void Graph::bfs(int v) {
    for (int k=1; k<=n; k++) nodes[k].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

int Graph::outDegree(int v) {
    if(v>nodes.size()-1 || v<1) return -1;
    return (int) nodes.at(v).adj.size();
}

int Graph::connectedComponents() {
    int result=0;
    for(int i=1; i<nodes.size(); i++){
        if(!nodes[i].visited) {
            dfs(i);
            result++;
        }
    }
    return result;
}

int Graph::giantComponent() {
    int max=0;
    for(int i=1; i<nodes.size(); i++){
        if(!nodes[i].visited) {
            int search = dfs(i);
            if(search>max) max = search;
        }
    }
    return max;
}

void Graph::dfshelper(int v, list<int>& order) {
    nodes[v].visited=true;
    for(auto node: nodes[v].adj){
        if(!nodes[node.dest].visited){
            dfshelper(node.dest, order);
        }
    }
    order.push_front(v);
}

list<int> Graph::topologicalSorting() {
    list<int> order;

    for(int i=1; i<nodes.size(); i++){
        if(!nodes[i].visited){
            dfshelper(i, order);
        }
    }
    return order;
}

void Graph::bfshelper(int a) {
    for (int v=1; v<=n; v++) {nodes[v].visited = false; nodes[v].parent = -1; nodes[v].distance = 0;}
    nodes[a].parent = a;
    queue<int> q; // queue of unvisited nodes
    q.push(a);
    nodes[a]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        //cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited && e.capacity != 0) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].parent = u;
                nodes[w].distance = nodes[u].distance + 1;
            }
        }
    }
}

int Graph::distance(int a, int b) {
    bfshelper(a);
    return nodes[b].distance;
}

int Graph::diameter() {
    if(this->connectedComponents()>1) return -1;
    int diameter = 0;
    for(int i=1; i<nodes.size(); i++){
        bfshelper(i);
        for(const Node& k : nodes){
            int j = k.distance;
            if(j>diameter) diameter=j;
        }
    }
    return diameter;
}

int Graph::kruskal() {
    MinHeap<int, int> heap(100, 0);
    DisjointSets<int> disjointSets;
    map<int, pair<int, int>> map;

    int k = 1;
    for(int i=1; i<nodes.size(); ++i){
        disjointSets.makeSet(i);

        Node* u = &nodes[i];
        for(Edge &e: u->adj){
            if(e.dest<i) continue;
            heap.insert(k, e.weight);
            map.insert(make_pair(k, make_pair(i, e.dest)));
            k++;
        }
    }

    int mst = 0;

    while(heap.getSize()>0){
        k = heap.removeMin();
        auto key = map.find(k);
        int origem = key->second.first;
        int destino = key->second.second;

        if(disjointSets.find(origem) != disjointSets.find(destino)){
            for(auto e: nodes[origem].adj) if(e.dest==destino) mst+=e.weight;
            disjointSets.unite(origem, destino);
        }
    }


    return mst;
}

int Graph::prim(int r) {
    MinHeap<int, int> heap((int)nodes.size(), 0);
    auto i = 1;
    for(Node &no: nodes){
        no.distance = INT16_MAX;
        no.parent = 0;
        heap.insert(i, no.distance);
        i++;
    }
    nodes[r].distance=0;
    heap.decreaseKey(r, 0);


    while(heap.getSize()>1){
        i = heap.removeMin();
        cout << i << endl;
        Node* u = &nodes[i];

        for(Edge &e: u->adj){
            if(!heap.hasKey(e.dest)) continue;
            if(e.weight<nodes[e.dest].distance){
                nodes[e.dest].parent=i;
                nodes[e.dest].distance=e.weight;
                heap.decreaseKey(e.dest, e.weight);
            }
        }
    }

    int sum = 0;

    for(const Node& no: nodes){
        if(no.parent==0) continue;
        sum += no.distance;
    }

    return sum;
}

int Graph::printDirections() {
    for (int i=1; i<=n; i++) {
        printf("%d ", i);
        auto itr = nodes[i].adj.begin();
        for (; itr!=nodes[i].adj.end(); itr++) {
            printf("-> %d ", itr->dest);
        }
        printf("\n");
    }
    return 0;
}

void Graph::MaxCapWays(int s) {
    for (int v=1; v<=n; v++) { nodes[v].parent = -1; nodes[v].distance = 0; }
    nodes[s].distance = INT_MAX / 2;

    MaxHeap<int, int> heap(n, -1);
    heap.insert(s, nodes[s].distance);
    for(int v=1;v<=n; v++) heap.insert(v, nodes[v].distance);

    while(heap.getSize()>0) {
        int v = heap.removeMax();

        Node* u = &nodes[v];
        for(const Edge &e: u->adj){
            if(!heap.hasKey(e.dest)) continue;
            if(nodes[e.dest].distance < min(u->distance, e.capacity)){
                nodes[e.dest].parent=v;
                nodes[e.dest].distance=e.capacity;
                heap.increaseKey(e.dest, e.capacity);
            }
        }
    }
}
void Graph::MaxCapWaysWithUse(int s) {
    for (int v=1; v<=n; v++) { nodes[v].parent = -1; nodes[v].distance = 0; }
    nodes[s].distance = INT_MAX / 2;

    MaxHeap<int, int> heap(n, -1);
    heap.insert(s, nodes[s].distance);
    for(int v=1;v<=n; v++) heap.insert(v, nodes[v].distance);

    while(heap.getSize()>0) {
        int v = heap.removeMax();

        Node* u = &nodes[v];
        for(const Edge &e: u->adj){
            if(nodes[e.dest].distance < min(u->distance, e.capacity) && nodes[e.dest].use ){
                nodes[e.dest].parent=v;
                nodes[e.dest].distance=e.capacity;
                heap.increaseKey(e.dest, e.capacity);
            }
        }
    }
}
vector<int> Graph::getDistances() {
    vector<int> d;
    for(int v=0; v<=n; v++) d.push_back(nodes[v].distance);
    return d;
}

void Graph::getPath(vector<int> *path, int t) {
    int i = t;
    while(true) {
        path->push_back(i);
        i = nodes[i].parent;
        if(i <= 0 || nodes[i].parent==i) break;
    }
    if (nodes[i].parent==i) path->push_back(i);
    reverse(path->begin(), path->end());
}

int Graph::pathCapacity(vector<int> vector1) {
    int cap = INT_MAX / 2;
    for (int i = 0; i < vector1.size() - 1; i++) {
        int w = vector1[i];
        for(auto e: nodes[w].adj) {
            if(e.dest == vector1[i + 1]) {
                if(e.capacity < cap) cap = e.capacity;
            }
        }
    }
    return cap;
}

void Graph::setPath(vector<int> vector1) {
    for(int i = 1; i < nodes.size(); i++){
        nodes[i].use = false;
    }
    for(int i = 0; i < vector1.size(); i++){
        nodes[vector1[i]].use = true;
    }
    return;
}

int Graph::unusedNodes(){
    int n = 0;
    for(int i = 1; i < nodes.size(); i++){
        if(!nodes[i].use){
            n++;
        }
    }
    return n;
}
void Graph::setUseNode(){
    for(int i = 1; i < nodes.size(); i++){
        if(!nodes[i].use){
            nodes[i].use = true;
            break;
        }

    }
}

int Graph::fordFulkerson(Graph& residual, int s, int t, vector<vector<int>> *paths, int dimension) {
    int max_flow = 0;

    while (true) {
        residual.bfshelper(s);
        if(residual.nodes[t].parent == -1) break;

        int path_flow = INT_MAX/2;
        for (int v = t; v != s; v = residual.nodes[v].parent) {
            int u = residual.nodes[v].parent;
            for (auto e: residual.nodes[u].adj) {
                if (e.dest == v) path_flow = min(path_flow, e.capacity);
            }
        }

        for (int v = t; v != s; v = residual.nodes[v].parent) {
            int u = residual.nodes[v].parent;
            for (auto &e: residual.nodes[u].adj) {
                if (e.dest == v) e.capacity -= path_flow;
            }
            for (auto &e: residual.nodes[v].adj) {
                if(e.dest == u) e.capacity += path_flow;
            }
        }

        vector<int> path;
        residual.getPath(&path, t);
        paths->push_back(path);
        max_flow += path_flow;
        if (dimension != -1 && max_flow >= dimension) return max_flow;
    }

    return max_flow;
}

Graph Graph::createResidual() {
    Graph r(this->n, true);

    for (int v = 1; v <= n; v++) {
        for (auto e: nodes[v].adj) {
            r.addEdge(v, e.dest, e.weight, e.capacity - e.flow, e.flow);
            r.addEdge(e.dest, v, e.weight, e.flow, e.capacity-e.flow);
        }
    }

    return r;
}

int Graph::getTime(vector<int> vector1, int limit) {
    int time = 0;

    for (int i = 0; i < vector1.size() - 1; i++) {
        if(limit != -1 && i == limit) {
            break;
        }
        int u = vector1[i];
        int v = vector1[i + 1];
        for (auto e : nodes[u].adj) {
            if(e.dest == v) {
                time += e.weight;
                break;
            }
        }
    }
    return time;
}

int Graph::getDuration(int a, int b) {
    for(auto x : nodes[a].adj) {
        if(x.dest == b) {
            return x.weight;
        }
    }
}
int Graph::minDuration(int s,int t) {
    Graph residual = this->createResidual();

    vector<vector<int>> paths;
    vector<pair<int,int>> waitTime;
    fordFulkerson(residual, s, t, &paths);

    for(auto &x :residual.nodes) {
        for(auto &y : x.adj) {
            y.flow = 0;
        }
    }
    for(auto x : paths) {
        for(int i = 0; i < x.size() - 1; i++) {
            int from = x[i];
            int to = x[i+1];
            for(int j = 0; j < residual.nodes.size(); j++) {
                for(auto &w : residual.nodes[j].adj) {
                    if(j == from && to == w.dest) {
                        w.flow = 1;
                    }
                }
            }
        }
    }

    vector<int> Pred(n+1,-1);
    vector<int> Grau(n+1,0);
    queue<int> q;

    for(int i = 1; i < residual.nodes.size(); i++) {
        for(auto w : residual.nodes[i].adj) {
            if(w.flow == 0) {
                continue;
            }
            int no = w.dest;
            Grau[no]++;
        }
    }

    for(int i = 1; i < Grau.size(); i++) {
        if(Grau[i] == 0) {
            q.push(i);
        }
    }


    int durMin = -1;
    int vf = -1;

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        if(durMin < ES[v]) {
            durMin = ES[v];
            vf = v;
        }
        for(auto e : residual.nodes[v].adj) {
            int w = e.dest;
            if(e.flow == 0) {
                continue;
            }
            if(ES[w] < ES[v] + e.weight) {
                ES[w] = ES[v] + e.weight;
                Pred[w] = v;
            }
            Grau[w]--;
            if(Grau[w] == 0) {
                q.push(w);
            }
        }
    }
    return durMin;
}

int Graph::minDurationAll(int s,int t) {
    Graph residual = this->createResidual();

    vector<int> Pred(n+1,-1);
    vector<int> Grau(n+1,0);
    queue<int> q;

    for(int i = 1; i < nodes.size(); i++) {
        for(auto w : nodes[i].adj) {
            int no = w.dest;
            Grau[no]++;
        }
    }

    for(int i = 1; i < Grau.size(); i++) {
        if(Grau[i] == 0) {
            q.push(i);
        }
    }


    int durMin = -1;
    int vf = -1;

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        if(durMin < ES[v]) {
            durMin = ES[v];
            vf = v;
        }
        for(auto e : nodes[v].adj) {
            int w = e.dest;
            if(ES[w] < ES[v] + e.weight) {
                ES[w] = ES[v] + e.weight;
                Pred[w] = v;
            }
            Grau[w]--;
            if(Grau[w] == 0) {
                q.push(w);
            }
        }
    }
    return durMin;
}

int Graph::latestFinish(int s, int t) {

    Graph residual = this->createResidual();

    vector<vector<int>> paths;
    vector<pair<int,int>> waitTime;
    fordFulkerson(residual, s, t, &paths);

    for(auto &x :residual.nodes) {
        for(auto &y : x.adj) {
            y.flow = 0;
        }
    }
    for(auto x : paths) {
        for(int i = 0; i < x.size() - 1; i++) {
            int from = x[i];
            int to = x[i+1];
            for(int j = 0; j < residual.nodes.size(); j++) {
                for(auto &w : residual.nodes[j].adj) {
                    if(j == from && to == w.dest) {
                        w.flow = 1;
                    }
                }
            }
        }
    }

    vector<int> Pred(n+1,-1);
    vector<int> Grau2(n+1,0);
    queue<int> q2;

    for(int i = 1; i < residual.nodes.size(); i++) {
        for(auto w : residual.nodes[i].adj) {
            if(w.flow == 0) {
                continue;
            }
            int no = w.dest;
            Grau2[no]++;
        }
    }

    for(int i = 1; i < Grau2.size(); i++) {
        if(Grau2[i] == 0) {
            q2.push(i);
        }
    }


    int durMin = -1;
    int vf = -1;

    while(!q2.empty()) {
        int v = q2.front();
        q2.pop();
        if(durMin < ES[v]) {
            durMin = ES[v];
            vf = v;
        }
        for(auto e : residual.nodes[v].adj) {
            int w = e.dest;
            if(e.flow == 0) {
                continue;
            }
            if(ES[w] < ES[v] + e.weight) {
                ES[w] = ES[v] + e.weight;
                Pred[w] = v;
            }
            Grau2[w]--;
            if(Grau2[w] == 0) {
                q2.push(w);
            }
        }
    }


    for(auto &x :this->nodes) {
        for(auto &y : x.adj) {
            y.flow = 0;
        }
    }
    for(auto x : paths) {
        for(int i = 0; i < x.size() - 1; i++) {
            int from = x[i];
            int to = x[i+1];
            for(int j = 0; j < this->nodes.size(); j++) {
                for(auto &w : this->nodes[j].adj) {
                    if(j == from && to == w.dest) {
                        w.flow = 1;
                    }
                }
            }
        }
    }

    Graph graphT = createTranspose();


    for(auto &x : LF) {
        x = durMin;
    }

    vector<int> Grau(n+1,0);
    vector<int> LS(n+1);
    vector<int> FT(n+1);


    for(int i = 1; i < graphT.nodes.size(); i++) {
        for(auto w : graphT.nodes[i].adj) {
            int no = w.dest;
            if(w.flow == 0) {
                continue;
            }
            Grau[no]++;
        }
    }

    queue<int> q;

    for(int i = 1; i < Grau.size(); i++) {
        if(Grau[i] == 0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for(auto &e : graphT.nodes[v].adj) {
            int w = e.dest;
            if(e.flow == 0) {
                continue;
            }
            if(LF[w] > LF[v] - e.weight) {
                LF[w] = LF[v] - e.weight;
            }
            Grau[w]--;
            if(Grau[w] == 0) {
                q.push(w);
            }
        }
    }

    vector<int> temp;
    for(int i = 1; i < nodes.size(); i++) {
        for(auto x : nodes[i].adj) {
            if(x.flow == 0) {
                continue;
            }
            if(LF[x.dest] - x.weight - ES[i] > FT[x.dest]) {
                FT[x.dest] = LF[x.dest] - x.weight - ES[i];
            }
        }
    }

    auto num = max_element(std::begin(FT), std::end(FT));
    cout << "Max Wait Time: " << *num << endl;
    cout << "Nodes with max wait time: " << endl;
    for(int i = 0; i < FT.size(); i++) {
        if (FT[i] == *num) {
            cout << i << endl;
        }
    }
    return 0;
}

int Graph::latestFinishAll(int s, int t) {

    Graph residual = this->createResidual();

    vector<int> Pred(n+1,-1);
    vector<int> Grau2(n+1,0);
    queue<int> q2;

    for(int i = 1; i < nodes.size(); i++) {
        for(auto w : nodes[i].adj) {
            int no = w.dest;
            Grau2[no]++;
        }
    }

    for(int i = 1; i < Grau2.size(); i++) {
        if(Grau2[i] == 0) {
            q2.push(i);
        }
    }


    int durMin = -1;
    int vf = -1;

    while(!q2.empty()) {
        int v = q2.front();
        q2.pop();
        if(durMin < ES[v]) {
            durMin = ES[v];
            vf = v;
        }
        for(auto e : nodes[v].adj) {
            int w = e.dest;
            if(ES[w] < ES[v] + e.weight) {
                ES[w] = ES[v] + e.weight;
                Pred[w] = v;
            }
            Grau2[w]--;
            if(Grau2[w] == 0) {
                q2.push(w);
            }
        }
    }

    Graph graphT = createTranspose();


    for(auto &x : LF) {
        x = durMin;
    }

    vector<int> Grau(n+1,0);
    vector<int> LS(n+1);
    vector<int> FT(n+1);


    for(int i = 1; i < graphT.nodes.size(); i++) {
        for(auto w : graphT.nodes[i].adj) {
            int no = w.dest;
            Grau[no]++;
        }
    }

    queue<int> q;

    for(int i = 1; i < Grau.size(); i++) {
        if(Grau[i] == 0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for(auto &e : graphT.nodes[v].adj) {
            int w = e.dest;
            if(LF[w] > LF[v] - e.weight) {
                LF[w] = LF[v] - e.weight;
            }
            Grau[w]--;
            if(Grau[w] == 0) {
                q.push(w);
            }
        }
    }

    vector<int> temp;
    for(int i = 1; i < nodes.size(); i++) {
        for(auto x : nodes[i].adj) {
            if(LF[x.dest] - x.weight - ES[i] > FT[x.dest]) {
                FT[x.dest] = LF[x.dest] - x.weight - ES[i];
            }
        }
    }

    auto num = max_element(std::begin(FT), std::end(FT));
    cout << "Max Wait Time: " << *num << endl;
    cout << "Nodes with max wait time: " << endl;
    for(int i = 0; i < FT.size(); i++) {
        if (FT[i] == *num) {
            cout << i << endl;
        }
    }
    return 0;
}

int Graph::checkMaxCap(vector<vector<int>> paths) {
    int maxCap = 0;
    for (int i = 0; i < paths.size(); i++) {
        int cap = 0;
        for (int j = 0; j < paths[i].size() - 1; j++) {
            int u = paths[i][j];
            int v = paths[i][j + 1];
            for (auto e: nodes[u].adj) {
                if(e.dest == v) cap = min(cap, e.capacity);
                if (j == 0) cap = e.capacity;
            }
        }
        maxCap += cap;
    }
    return maxCap;
}

Graph Graph::createTranspose() {
    Graph r(this->n, true);
    for(int i = 1; i <= n; i++) {
        for(auto y : nodes[i].adj) {
            r.addEdge(y.dest,i,y.weight,y.capacity,y.flow);
        }
    }
    return r;
}

int Graph::findDuration(int from, int to) {
    for(int i = 1; i < nodes.size(); i++) {
        for(auto x : nodes[i].adj) {
            if(i == from && x.dest == to) {
                return x.weight;
            }
        }
    }
}
