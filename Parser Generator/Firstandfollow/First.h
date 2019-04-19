//
// Created by sohayla on 19/04/19.
//

#ifndef COMPILER_FIRST_H
#define COMPILER_FIRST_H

#include "Firstandfollow_tables.h"
#include <string>

using namespace std;
class First {
private:
    //TODO whatever comes from parser declare here.
    vector<string> visited;
public:
    First();
    void calculateFirst();
    void recurseOnNonTerminal(string non_t);
    vector<string> findFirst(string prod);
    bool checkIfEpsOccurs(string non_t);
};


#endif //COMPILER_FIRST_H
