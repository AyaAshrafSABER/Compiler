//
// Created by TARGET on 3/23/2019.
//

#ifndef COMPILER_MINIMIZEDFA_H
#define COMPILER_MINIMIZEDFA_H

#include <vector>
#include <map>
#include <set>
#include "Definition.h"
#include "Node.h"

class MinimizeDFA {
private:
    /* Here will be the instance stored. */
    static MinimizeDFA* instance;
    /* Private constructor to prevent instancing. */
    MinimizeDFA();

    vector<map<Definition*,set<Node*>>> transitionStateTable;
    set<Node*> Accepted;
    set<Node*> NotAccepted;
    vector<set<Node*>> perviousPartition;
    vector<set<Node*>> nextPartition;

public:
    /* Static access method. */
    static MinimizeDFA* getInstance();
    vector<map<Definition*,set<Node*>>> getMinimizedDFA();

};


#endif //COMPILER_MINIMIZEDFA_H
