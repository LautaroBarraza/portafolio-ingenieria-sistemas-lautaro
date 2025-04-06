//
// Created by lauba on 10/8/2024.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "../TDAGrafo/include/Grafo.h"
#include "Solucion/Solucion.h"


class Dijkstra {

public:
    Dijkstra();
    ~Dijkstra();
    Solucion dijkstra(Grafo<int> g, int origen);
};



#endif //DIJKSTRA_H
