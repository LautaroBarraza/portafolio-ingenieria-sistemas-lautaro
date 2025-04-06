//
// Created by lauba on 10/7/2024.
//

#include "Sets.h"

#include <cassert>

Sets::Sets(int n) {
    p = new int[(n+1)];
    for (int i = 0; i < n; i++) {
        p[i] = -1;
    }
    count=n;
}
Sets::~Sets() {
    delete []p;
}
int Sets::Count() {
    return count;
}
bool Sets::connected(int i, int j) {
    return Find(i)== Find(j);
}

void Sets::Union(int i, int j) {
    assert (p[i]<0 && p[j]<0); //i y j deben ser raices de conjuntos
    int temp = p[i]+p[j];
    if(p[i]>p[j]) { //i tiene menos nodos
        p[i]=j; p[j]=temp;
    }else { // j tiene menos nodos
        p[j]=i; p[i]=temp;
    }
    count--;
}

int Sets::Find(int i) {
    int r= i, temp;
    while (p[r]>=0)
        r=p[r]; //encuentra la raiz
    while (i!=r) { //cuelga cada naodo en el camino de i a la raiz de la raiz
        temp=p[i];
        p[i]=r;
        i=temp;
    }
        return r;
}




