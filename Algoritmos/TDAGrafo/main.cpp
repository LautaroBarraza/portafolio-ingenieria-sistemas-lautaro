#include "./include/Grafo.h"

#include "iostream"

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
			ady++;
		}

		v++;
	}

	list<typename Grafo<C>::Arco> arcos;
	grafo.devolver_arcos(arcos);
	salida << "Todos los arcos: " << endl;
	typename list<typename Grafo<C>::Arco>::iterator ady = arcos.begin();
    while (ady != arcos.end()) {
        salida << " (" << ady->devolver_origen() << ", " << ady->devolver_destino() << ", "  << ady->devolver_costo() << ")" << endl;
        ady++;
    }
	return salida;
}

void recorrer(const Grafo<int> & grafo);

int main(int argc, char **argv)
{
	Grafo<int> g;

	// Cargamos un grafo dirigido
	// Primero los vértices
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
	g.eliminar_arco(1, 4);


	// Mostramos el grafo
	cout << "Estructura del grafo:\n" << g << "(" << g.cantidad_vertices()
        << " vertices, " << g.cantidad_arcos() << " arcos)" << endl;

    recorrer(g);

	return 0;
}

void recorrer(const Grafo<int> & grafo)
{


}
