//
// Created by lauba on 10/10/2024.
//

#include "Prim.h"

#include <limits.h>
#include <queue>

Prim::Prim() {

}

Prim::~Prim() {

}

void Prim::prim(Grafo<int> &g, Grafo<int> &g2) {
    int * s = new int[g.cantidad_vertices()];
    int * mas_cercano= new int[g.cantidad_vertices()];
    int * menor_costo= new int[g.cantidad_vertices()];
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    Grafo<int> arcm;
    s[0]=1;

    //seteo todos los vertices excepto el primero con la distancia que haya, si no hay arco entonces es infinito y ponego que ninguno se agrego al arbol de recubrimiento
    for (int i = 1; i < g.cantidad_vertices(); i++) {
        int c;
        if(g.existe_arco(0,i)) {
            c= g.costo_arco(0,i);
        }else {
            c= INT_MAX;
        }
        pq.push(make_pair(i,c));
        menor_costo[i]=c;
        mas_cercano[i]=0;
        s[i]=0;
    }

    for (int i = 1; i < g.cantidad_vertices(); i++) {
        //obtengo el vertice con menor costo
        int v= pq.top().first;
        int c= pq.top().second;
        pq.pop();
        if(menor_costo[v] == c) {
            if(s[v]==0) {
                //lo agrego al arbol de recubrimiento
                s[v]=1;
                arcm.agregar_vertice(v);
                arcm.agregar_vertice(mas_cercano[v]);
                arcm.agregar_arco(v,mas_cercano[v],c);

                for(int j = 1; j < g.cantidad_vertices(); j++) {
                    if(g.existe_arco(v,j)) {
                        c= g.costo_arco(v,j);
                    }else {
                        c= INT_MAX;
                    }
                    if(s[j]==0 && c<menor_costo[j]) {
                        pq.push(make_pair(j,c));
                        menor_costo[j]=c;
                        mas_cercano[j]=v;
                    }
                }
            }
        }
    }
    g2=arcm;
}


