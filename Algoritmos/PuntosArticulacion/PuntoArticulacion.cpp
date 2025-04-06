//
// Created by lauba on 9/20/2024.
//

#include "PuntoArticulacion.h"

PuntoArticulacion::PuntoArticulacion() {

}
PuntoArticulacion::~PuntoArticulacion() {

}

void PuntoArticulacion::get_puntos_articulacion(const Grafo<int> &g, list<int> &puntos) {
    if(padre!=nullptr) {
        this->~PuntoArticulacion();
    }
    this->cantidad_vertices=g.cantidad_vertices();
    this->padre=new int[cantidad_vertices];
    this->visitados= new int[cantidad_vertices];
    this->pre_orden= new int[cantidad_vertices];
    this->max= new int[cantidad_vertices];
    for(int i=0;i<cantidad_vertices;i++) {
        padre[i]=-1;
        visitados[i]=0;
        max[i]=g.cantidad_vertices()+1;
    }
    for (int i=0;i<cantidad_vertices;i++) {
        if(visitados[i]==0) {
            visitados[i]=1;
            this->puntos_articulacion(g,i,puntos);
        }
    }
}

void PuntoArticulacion::puntos_articulacion(const Grafo<int> &g, int u, list<int> &puntos) {
    time=time+1;
    pre_orden[u]=time;
    max[u]=time;
    int c=g.cantidad_adyacentes(u);
    if(padre[u]==-1 && c>=2) {
        puntos.push_back(u);
    }
    list<Grafo<int>::Arco> l;
    g.devolver_adyacentes(u,l);
    list<Grafo<int>::Arco>::iterator it=l.begin();
    while (it!=l.end()) {
        if(visitados[it->devolver_destino()]==0) {
            padre[it->devolver_destino()]=u;
            visitados[it->devolver_destino()]=1;

            puntos_articulacion(g,it->devolver_destino(),puntos);

            if(max[it->devolver_destino()]>=pre_orden[u] && padre[u]!=-1) {
                puntos.push_back(u);
            }
            max[u]=std::min(max[u],max[it->devolver_destino()]);
        }else {
            max[u]=std::min(max[u],pre_orden[it->devolver_destino()]);
        }
        ++it;
    }
}



