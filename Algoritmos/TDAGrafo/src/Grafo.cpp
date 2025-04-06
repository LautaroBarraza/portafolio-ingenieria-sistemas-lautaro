#include "../include/Grafo.h"

#include <cassert>
#include <list>
#include <stdexcept>

using namespace std;


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco()
{
}

template <typename C> Grafo<C>::Arco::Arco(int origen, int destino, const C & costo)
{
    this->origen = origen;
    this->destino = destino;
    this->costo = costo;
}

template <typename C> int Grafo<C>::Arco::devolver_origen() const
{
    return origen;
}

template <typename C> int Grafo<C>::Arco::devolver_destino() const
{
    return destino;
}

template <typename C> const C & Grafo<C>::Arco::devolver_costo() const
{
    return costo;
}
template <typename C> bool Grafo<C>::Arco::operator<(const Arco& otro) const {
    return this->costo < otro.costo;
}


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo()
{
    _cantidad_vertices = 0;
    _cantidad_arcos = 0;
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{
    //Construir el grafo actual (this) a partir de otroGrafo
}

template <typename C> Grafo<C>::~Grafo()
{
}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{
    //Construir el grafo actual (this) a partir de otroGrafo
    list<int> l;
    otroGrafo.devolver_vertices(l);
    list<int>::iterator it = l.begin();
    while (it != l.end()) {
        this->agregar_vertice(*it);
        ++it;
    }
    list<Arco> l2;
    otroGrafo.devolver_arcos(l2);
    typename list<Arco>::iterator it2 = l2.begin();
    while (it2 != l2.end()) {
        this->agregar_arco(it2->devolver_origen(),it2->devolver_destino(),it2->devolver_costo());
        ++it2;
    }
    this->_cantidad_vertices = otroGrafo.cantidad_vertices();
    this->_cantidad_arcos = otroGrafo.cantidad_arcos();
    return *this;
}

template <typename C> bool Grafo<C>::esta_vacio() const
{
    return (this->_cantidad_vertices == 0);
}

template <typename C> int Grafo<C>::cantidad_vertices() const
{
    return this->_cantidad_vertices;
}

template <typename C> int Grafo<C>::cantidad_arcos() const
{
    return this->_cantidad_arcos;
}
template<typename C>
int Grafo<C>::cantidad_adyacentes(int origen) const {
    typename  map<int,map<int,C>>::const_iterator it = this->_adyacentes.find(origen);
    if (it != this->_adyacentes.end()) {
        return it->second.size();
    }
    return 0;
}

template <typename C> bool Grafo<C>::existe_vertice(int vertice) const {
    typename  map<int,map<int,C>>::const_iterator it = this->_adyacentes.find(vertice);
    return (it != this->_adyacentes.end());
}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const
{
    typename map<int,map<int,C>>::const_iterator it = this->_adyacentes.find(origen);
    if(it != this->_adyacentes.end()) {
        typename map<int,C>::const_iterator it2 = it->second.find(destino);
        return (it2 != it->second.end());
    }
    return false;
}

template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const
{
    typename map<int,map<int,C>>::const_iterator it = this->_adyacentes.find(origen);
    if(it != this->_adyacentes.end()) {
        typename map<int,C>::const_iterator it2 = it->second.find(destino);
        if(it2 != it->second.end()) {
            return it2->second;
        }
    }
    throw out_of_range("el arco no existe");
}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & vertices) const
{
    typename map<int,map<int,C>>::const_iterator it = this->_adyacentes.begin();
    while(it != this->_adyacentes.end()) {
        vertices.push_back(it->first);
        ++it;
    }
}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const
{
    typename map<int,map<int,C>>::const_iterator it = this->_adyacentes.find(origen);
    if(it != this->_adyacentes.end()) {
        typename map<int,C>::const_iterator it2 = it->second.begin();
        while(it2 != it->second.end()) {
            adyacentes.push_back(Arco(it->first, it2->first, it2->second));
            ++it2;
        }
    }
}

template <typename C> void Grafo<C>::devolver_arcos(list<Arco> & arcos) const
{
    typename map<int,map<int,C>>::const_iterator it = this->_adyacentes.begin();
    while(it != this->_adyacentes.end()) {
        typename map<int,C>::const_iterator it2 = it->second.begin();
        while(it2 != it->second.end()) {
            arcos.push_back(Arco(it->first,it2->first,it2->second));
            ++it2;
        }
        ++it;
    }
}

template <typename C> void Grafo<C>::agregar_vertice(int vertice)
{
    this->_adyacentes[vertice]=map<int,C>();
    _cantidad_vertices++;
}

template <typename C> void Grafo<C>::eliminar_vertice(int vertice)
{
    this->_adyacentes.erase(vertice);
    typename map<int,map<int,C>>::iterator it = this->_adyacentes.begin();
    while(it != this->_adyacentes.end()) {
        typename map<int,C>::iterator it2 = it->second.find(vertice);
        if(it2 != it->second.end()) {
            it->second.erase(it2);
        }
        ++it;
    }
    _cantidad_vertices--;
}

template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{
    assert((origen <= cantidad_vertices()) && (destino <= cantidad_vertices()));
}

template <typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C & costo)
{
    assert((origen <= cantidad_vertices()) && (destino <= cantidad_vertices()));
    if(this->existe_vertice(origen) && this->existe_vertice(destino)) {
        typename map<int,map<int,C>>::iterator it = this->_adyacentes.find(origen);
        if(it != this->_adyacentes.end()) {
            it->second[destino]=costo;
        }
        _cantidad_arcos++;
    }

}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino)
{
    assert((origen <= cantidad_vertices()) && (destino <= cantidad_vertices()));
    typename map<int,map<int,C>>::iterator it = this->_adyacentes.find(origen);
    if(it != this->_adyacentes.end()) {
        typename map<int,C>::iterator it2 = it->second.find(destino);
        if(it2 != it->second.end()) {
            it->second.erase(it2);
        }
    }
    _cantidad_arcos--;
}

template <typename C> void Grafo<C>::vaciar()
{
    _adyacentes.clear();
}

template class Grafo<int>;
