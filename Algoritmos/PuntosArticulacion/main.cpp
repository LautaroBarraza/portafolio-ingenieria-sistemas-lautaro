#include <iostream>
#include <ostream>

#include "PuntoArticulacion.h"

int main(int argc, char **argv)
{
    Grafo<int> g;

    // Cargamos un grafo dirigido
    // Primero los vértices
    g.agregar_vertice(0);
    g.agregar_vertice(1);
    g.agregar_vertice(2);
    g.agregar_vertice(3);
    g.agregar_vertice(4);
    g.agregar_vertice(5);
    g.agregar_vertice(6);
    g.agregar_vertice(7);
    g.agregar_vertice(8);
    // Luego los arcos
    g.agregar_arco(1, 0, 12);
    g.agregar_arco(1, 7, 13);
    g.agregar_arco(0, 6, 14);
    g.agregar_arco(0, 2, 26);
    g.agregar_arco(0, 3, 35);
    g.agregar_arco(3, 5, 47);
    g.agregar_arco(3, 4, 56);
    g.agregar_arco(4, 6, 71);
    g.agregar_arco(6,7,34);
    g.agregar_arco(5,8,56);



    g.agregar_arco(0, 1, 12);
    g.agregar_arco(7, 1, 13);
    g.agregar_arco(6, 0, 14);
    g.agregar_arco(2, 0, 26);
    g.agregar_arco(3, 0, 35);
    g.agregar_arco(5, 3, 47);
    g.agregar_arco(4, 3, 56);
    g.agregar_arco(6, 4, 71);
    g.agregar_arco(7,6,34);

    g.agregar_arco(8, 5, 12);

    PuntoArticulacion p_a;
    list<int> l;
    p_a.get_puntos_articulacion(g,l);
    list<int>::iterator it = l.begin();
    while (it != l.end()) {
        cout << *it << endl;
        ++it;
    }

    return 0;
}
