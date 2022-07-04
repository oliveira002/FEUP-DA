#ifndef DA_T6_G62_GRAPH_H
#define DA_T6_G62_GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "graph/minHeap.h"
#include "graph/maxHeap.h"
#include "graph/disjointSets.h"

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        int capacity;
        int flow;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // As the node been visited on a search?
        int distance;
        int parent;
        bool use = false;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

    void allPathsUntil(int i, int u, bool[], int[], int&);
    vector<int> ES;
    vector<int> LF;
public:

    /**
     * Retorna a duração minima para o caminho entre s<->t
     * @param s no inicial
     * @param t no final
     * @return a duração minima
     */
    int minDuration(int s,int t);

    /**
     * Retorna tempo máxima espera
     * @param s no inicial
     * @param t no final
     * @return a duração minima
     */
    int latestFinish(int s, int t);

    /**
     * Retorna a duração minima para o caminho entre s<->t (Grafo Inteiro)
     * @param s no inicial
     * @param t no final
     * @return a duração minima
     */
    int minDurationAll(int s,int t);

    /**
     * Retorna tempo máxima espera (Grafo Inteiro)
     * @param s no inicial
     * @param t no final
     * @return a duração minima
     */
    int latestFinishAll(int s, int t);

    vector<int> getDistances();
    int getDuration(int a, int b);
    void MaxCapWaysWithUse(int s);
    void setPath(vector<int> vector1);
    int unusedNodes();
    void setUseNode();

    // Constructor: nr nodes and direction (default: undirected)
    explicit Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1, int capacity = 1, int flow = 0);

    // Depth-First Search: example implementation
    int dfs(int v);

    // Breadth-First Search: example implementation
    void bfs(int v);

    // ----- Functions -----
    int outDegree(int v);
    int connectedComponents();
    int giantComponent();
    void dfshelper(int v, list<int>& order);
    list<int> topologicalSorting();
    void bfshelper(int a);
    int distance(int a, int b);
    int diameter();
    bool hasCycle();
    int prim(int v);
    int kruskal();

    int findDuration(int from, int to);

    int printDirections();

    /*
     * Adaptação do dijkstra para o 1.1
     */
    void MaxCapWays(int s);

    void getPath(vector<int> *pVector, int t);

    int pathCapacity(vector<int> vector1);

    /**
     * Edmonds-Karp implementação através do fordFulkerson
     * @param residual
     * @param s
     * @param t
     * @param paths
     * @param dimension
     * @return
     */
    static int fordFulkerson(Graph& residual, int s, int t, vector<vector<int>> *paths, int dimension = -1);

    /**
     * Cria um grafo residual
     */
    Graph createResidual();

    /**
     * Cria um grafo transposto
     */
    Graph createTranspose();

    int getTime(vector<int> vector1, int limit = -1);

    int checkMaxCap(vector<vector<int>> paths);
};

#endif //DA_T6_G62_GRAPH_H
