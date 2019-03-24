//
// Created by TARGET on 3/23/2019.
//

#include "DFA.h"
/* Null, because instance will be initialized on demand. */
DFA* DFA::instance = 0;

DFA* DFA::getInstance()
{
    if (instance == 0)
    {
        instance = new DFA();
    }

    return instance;
}
//constructor
DFA::DFA()
{
}
vector<pair<Node*, map<Definition*,set<Node*>>>>  DFA::getDFA(){
    return this->transitionStateTable;
}