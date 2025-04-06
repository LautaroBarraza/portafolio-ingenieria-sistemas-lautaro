//
// Created by lauba on 10/7/2024.
//

#ifndef SETS_H
#define SETS_H



class Sets {
private:
    int * p;
    int count;
public:
    Sets(int n);
    ~Sets();
    int Count();
    bool connected(int i, int j);
    void Union(int i, int j);
    int Find(int j);

};



#endif //SETS_H
