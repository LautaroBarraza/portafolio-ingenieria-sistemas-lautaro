//
// Created by lauba on 10/8/2024.
//

#ifndef SOLUCION_H
#define SOLUCION_H
#include <map>
using namespace std;


class Solucion {
private:
    map<int,int> dist;
    map<int,int>pred;
public:
    Solucion(map<int,int> &dist,map<int,int> &pred);
};



#endif //SOLUCION_H
