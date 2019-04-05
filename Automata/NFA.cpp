//
// Created by sohayla on 20/03/19.
//

#include "NFA.h"
#include "../Parser/Read_Input.h"

static NFA* instance;

NFA::NFA() {

}
void NFA::read_input() {
    Read_Input *t = new Read_Input("/home/saraheldafrawy/CLionProjects/Compiler/input.txt");
    t->read_file();
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