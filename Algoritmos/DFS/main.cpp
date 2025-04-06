#include <iostream>

#include "../TDAGrafo/include/Grafo.h"
#include "DFS.h"

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
    // Luego los arcos
    g.agregar_arco(1, 2, 12);
    g.agregar_arco(1, 3, 13);
    g.agregar_arco(1, 4, 14);
    g.agregar_arco(2, 6, 26);
    g.agregar_arco(3, 5, 35);
    g.agregar_arco(4, 7, 47);
    g.agregar_arco(5, 6, 56);
    DFS dfs;
    dfs.dfs_forest(g);
    int arr[g.cantidad_vertices()];
    dfs.obtener_padre(arr);
    for (int i = 0; i < g.cantidad_vertices(); i++) {
        cout << arr[i] << endl;
    }

    return 0;
}