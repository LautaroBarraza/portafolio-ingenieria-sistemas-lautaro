//
// Created by lauba on 9/20/2024.
//

#ifndef PUNTOARTICULACION_H
#define PUNTOARTICULACION_H
#include "../TDAGrafo/include/Grafo.h"


class PuntoArticulacion {
public:
    PuntoArticulacion();
    ~PuntoArticulacion();
    void get_puntos_articulacion(const Grafo<int>& g, list<int>& puntos);

private:
    int * padre;
    int * max;
    int * pre_orden;
    int * visitados;
    int time=0;
    int cantidad_vertices;
    void puntos_articulacion(const Grafo<int>& g, int u,list<int>& puntos);
};



#endif //PUNTOARTICULACION_H
