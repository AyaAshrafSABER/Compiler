//
// Created by sohayla on 20/03/19.
//

#include "NFA.h"
static NFA* instance;

NFA::NFA() {
}

NFA* NFA::getInstance() {
    if(instance == NULL)
        instance = new NFA();
    return instance;
}
bool NFA::setAutomata(Graph *graph) {
    this->automata = graph;
}

Graph* NFA::getAutomata() {
    return this->automata;
}