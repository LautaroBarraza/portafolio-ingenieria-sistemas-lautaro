//
// Created by lauba on 8/31/2024.
//
#include "List.h"

#include <iostream>
#include <ostream>

#include "list"
using namespace std;

int main() {
    list<int> list;
    list.push_back(2);
    cout << list.front() << endl;

    return 0;
}