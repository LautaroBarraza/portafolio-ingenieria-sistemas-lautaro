//
// Created by lauba on 9/10/2024.
//

#include "DFS.h"

DFS::DFS():
    //inicializo los arreglos dinamicos que apunten a null, asi evito que apunten a basura
    padre(nullptr),
    visitados(nullptr),
    pre_orden(nullptr),
    post_orden(nullptr){
}

//destructor de la clase
DFS::~DFS() {
    delete[] padre;
    delete[] visitados;
    delete[] pre_orden;
    delete[] post_orden;
}


void DFS::dfs_forest(const Grafo<int>& g) {
    if(padre!=nullptr) {
        this->~DFS();
    }

    this->cantidad_vertices=g.cantidad_vertices();
    this->padre=new int[cantidad_vertices];
    this->visitados= new int[cantidad_vertices];
    this->pre_orden= new int[cantidad_vertices];
    this->post_orden= new int[cantidad_vertices];
    for(int i=0;i<cantidad_vertices;i++) {
        padre[i]=-1;
        visitados[i]=0;
    }
    for (int i=0;i<cantidad_vertices;i++) {
        if(visitados[i]==0) {
            this->dfs(g,i);
        }
    }

}

void DFS::dfs(const Grafo<int>& g, int u) {
    this->time=time+1;
    pre_orden[u]=time;
    visitados[u]=1;
    list<Grafo<int>::Arco> ady;
    g.devolver_adyacentes(u,ady);
    list<Grafo<int>::Arco>::iterator it= ady.begin();
    while (it!=ady.end()) {
        int v=it->devolver_destino();
        if(visitados[v]==0) {
            padre[v]=u;
            dfs(g,v);
        }++it;
    }
    time=time+1;
    post_orden[u]=time;
    visitados[u]=2;
}


void DFS::obtener_padre(int padre[]) {
    for(int i=0;i<cantidad_vertices;i++) {
        padre[i]=this->padre[i];
    }
}


