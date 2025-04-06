//
// Created by lauba on 10/1/2024.
//

#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "../TDAGrafo/include/Grafo.h"
#include "../Sets/Sets.h"


class Kruskal {
private:
    Grafo<int> _arcm;
    list<Grafo<int>::Arco> _aristas;
    Sets componentes;
public:
    Kruskal(Grafo<int> & g);
    ~Kruskal();
    void KRUSKAL(Grafo<int> &g);
};



#endif //KRUSKAL_H
