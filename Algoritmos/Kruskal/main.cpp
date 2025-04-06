//
// Created by lauba on 10/1/2024.
//
#include "../TDAGrafo/include/Grafo.h"
#include <iostream>

#include "Kruskal.h"

using namespace std;

template <typename C>
ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
    // Recorremos todos los vertices
    list<int> vertices;
    grafo.devolver_vertices(vertices);
    list<int>::iterator v = vertices.begin();
    while (v != vertices.end()) {
        salida << "    " << *v << endl;

        // Recorremos todos los adyacentes de cada vertice
        list<typename Grafo<C>::Arco> adyacentes;
        grafo.devolver_adyacentes(*v, adyacentes);
        typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
        while (ady != adyacentes.end()) {
            salida << "    " << *v << "-> " << ady->devolver_destino() << " (" << ady->devolver_costo() << ")" << endl;
            ++ady;
        }

        ++v;
    }

    list<typename Grafo<C>::Arco> arcos;
    grafo.devolver_arcos(arcos);
    salida << "Todos los arcos: " << endl;
    typename list<typename Grafo<C>::Arco>::iterator ady = arcos.begin();
    while (ady != arcos.end()) {
        salida << " (" << ady->devolver_origen() << ", " << ady->devolver_destino() << ", "  << ady->devolver_costo() << ")" << endl;
        ++ady;
    }
    return salida;
}

void recorrer(const Grafo<int> & grafo);

int main()
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

        Kruskal k(g);
        Grafo<int> g2;
        k.KRUSKAL(g2);

        // Mostramos el grafo
        cout << "Estructura del grafo:\n" << g2 << "(" << g2.cantidad_vertices()
            << " vertices, " << g2.cantidad_arcos() << " arcos)" << endl;

        recorrer(g2);

        return 0;
}

void recorrer(const Grafo<int> & grafo){

}
