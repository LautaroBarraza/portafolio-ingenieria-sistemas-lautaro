//
// Created by lauba on 9/14/2024.
//

#ifndef BFS_H
#define BFS_H
#include "../TDAGrafo/include/Grafo.h"


class BFS {

public:
    BFS();
    ~BFS();
    void bfs_forest(const Grafo<int>& g);
    void obtener_padre(int p[]);



private:
    bool * visitados;
    int * padre;
    int cant_vertices;
    void bfs(const Grafo<int>& g,int u);
};



#endif //BFS_H
