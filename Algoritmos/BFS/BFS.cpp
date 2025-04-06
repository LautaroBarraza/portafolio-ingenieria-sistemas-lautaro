//
// Created by lauba on 9/14/2024.
//

#include "BFS.h"

#include <queue>

BFS::BFS(): padre(nullptr), visitados(nullptr) {

}
BFS::~BFS() {
    delete[] padre;
    delete[] visitados;
}

void BFS::bfs_forest(const Grafo<int> & g) {
    this->cant_vertices=g.cantidad_vertices();
    this->padre= new int[cant_vertices];
    this->visitados=new bool[cant_vertices];
    for(int i = 0; i < cant_vertices; i++) {
        visitados[i]=false;
        padre[i]=-1;
    }
    for(int i = 0; i < cant_vertices; i++) {
        if(visitados[i]==false) {
            bfs(g,i);
        }
    }
}


void BFS::bfs(const Grafo<int> &g, int u) {
    int v;
    list<int> l;
    visitados[u]=true;
    l.push_front(u);
    while(!l.empty()) {
        v=l.front();
        list<Grafo<int>::Arco> ady;
        g.devolver_adyacentes(v,ady);
        list<Grafo<int>::Arco>::iterator it = ady.begin();
        while(it != ady.end()) {
            if(!visitados[it->devolver_destino()]) {
                visitados[it->devolver_destino()]=true;
                padre[it->devolver_destino()]=v;
                l.push_front(it->devolver_destino());
            }
            ++it;
        }
        l.pop_front();
    }
}
void BFS::obtener_padre(int p[]) {
    for(int i=0;i<this->cant_vertices;i++) {
        p[i]=padre[i];
    }
}

