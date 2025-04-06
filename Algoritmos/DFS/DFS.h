//
// Created by lauba on 9/10/2024.
//

#ifndef DFS_H
#define DFS_H
#include <ostream>

#include "../TDAGrafo/include/Grafo.h"


class DFS {
    public:
    DFS();
    ~DFS();
    void dfs_forest(const Grafo<int>& g);

    void obtener_padre(int padre[]);
    void obtener_post_order(int post_order[]);
    int obtener_pre_order(int pre_order[]);



    private:
    int time=0;
    void dfs(const Grafo<int>& g, int u);
    Grafo<int> g;
    int * visitados;
    int * padre;
    int * pre_orden;
    int * post_orden;
    int cantidad_vertices;


};



#endif //DFS_H
