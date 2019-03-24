//
// Created by TARGET on 3/23/2019.
//

#include "MinimizeDFA.h"
/* Null, because instance will be initialized on demand. */
MinimizeDFA* MinimizeDFA::instance = 0;

MinimizeDFA* MinimizeDFA::getInstance()
{
    if (instance == 0)
    {
        instance = new MinimizeDFA();
    }

    return instance;
}

MinimizeDFA::MinimizeDFA()
{
}
vector<map<Definition*,set<Node*>>>  MinimizeDFA::getMinimizedDFA(){
    return this->transitionStateTable;
}
