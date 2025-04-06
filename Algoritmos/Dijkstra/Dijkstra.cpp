//
// Created by lauba on 10/8/2024.
//

#include "Dijkstra.h"

#include <limits.h>
#include <queue>
#include <set>

Dijkstra::Dijkstra() {

}

Solucion Dijkstra::dijkstra(Grafo<int> g, int origen) {
        map<int, int> dist;
        map<int, int> pred;
        set<int> S;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        list<int> v;
        g.devolver_vertices(v);
        //inicializo todas las distancias en infinito y padres en -1
        list<int>::iterator it =v.begin();
        while (it != v.end()) {
                dist[*it] = INT_MAX;
                pred[*it] = -1;
                ++it;
        }
        dist[origen]=0;
        pq.push(make_pair(0,origen));

        //comienzo a establecer las distacias minimas
        while (!pq.empty()) {
                int u= pq.top().second;
                pq.pop();
                if(S.find(u) == S.end()) {
                        S.insert(u);
                        list<typename Grafo<int>::Arco> ady;
                        g.devolver_adyacentes(u,ady);
                        list<typename Grafo<int>::Arco>::iterator it=ady.begin();
                        while (it != ady.end()) {
                                int v= it->devolver_destino();
                                int costo  = it->devolver_costo();
                                if(dist[v]>dist[u]+costo) {
                                        dist[v] = dist[u]+costo;
                                        pred[v] = u;
                                        pq.push(make_pair(dist[v],v));
                                }
                                ++it;
                        }
                }
        }
       return Solucion(dist,pred);
}

