//
// Created by lauba on 10/1/2024.
//

#include "Kruskal.h"

#include <algorithm>

Kruskal::Kruskal(Grafo<int> &g): componentes(g.cantidad_vertices()), _arcm(Grafo<int>()) {
    list<int> v;
    g.devolver_vertices(v);
    list<int>::iterator it = v.begin();
    while (it != v.end()) {
        _arcm.agregar_vertice(*it);
        ++it;
    }
    this->_aristas = list<Grafo<int>::Arco>();
    g.devolver_arcos(_aristas);
    _aristas.sort();
}

Kruskal::~Kruskal() {
}

void Kruskal::KRUSKAL(Grafo<int> &g) {
    int c_u, c_v;
    while (componentes.Count()>1) {
        Grafo<int>::Arco arco= _aristas.front();
        _aristas.pop_front();
        c_u= componentes.Find(arco.devolver_origen());
        c_v= componentes.Find(arco.devolver_destino());
        if (c_u != c_v) {
            _arcm.agregar_arco(arco.devolver_origen(), arco.devolver_destino(),arco.devolver_costo());
            componentes.Union(c_u,c_v);
        }
    }
    g=_arcm;
}

