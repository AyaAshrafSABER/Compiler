//
// Created by sohayla on 20/03/19.
//

#include <fstream>
#include "Definition.h"
#include "Helpers.h"

static Helpers* instance ;


Helpers::Helpers() {
    ifstream infile("Helpers.txt");
    string line;
    if(infile.is_open()) {
        while (getline(infile, line)) {
            helpers.push_back(line);
        }
    }
}
Helpers* Helpers::getInstance() {
    if(instance == NULL){
       instance = new Helpers();
    }
    return instance;

}


list<string> Helpers::getHelpers() {
    return this->helpers;
}

Graph* Helpers::mergeGraphs(Graph *graph_1, Graph *graph_2, string helper) {

    if(helper == "|")
            return mergeOr(graph_1, graph_2);
    if(helper == "*")
            return mergeAst(graph_1);
    if(helper == "\\+")
            return mergePlus(graph_1);
    if(helper == ".")
            return mergeCont(graph_1, graph_2);


    return NULL;


}

Graph *Helpers::mergeOr(Graph *pGraph, Graph *graph_2) {
    if(graph_2 == NULL)
        return pGraph;
    if(pGraph == NULL)
        return graph_2;
    Node* end_first = pGraph->getEndState();
    Node* end_second = graph_2->getEndState();
    Node* start_first = pGraph->getStartState();
    Node* start_second = graph_2->getStartState();
    string e = "eps";
    Definition *w = new Definition(&e, true);
    string id;
    id = end_first->getStatus() + "|"+ end_second->getStatus();


    end_first->setStatus(N_ACC);
    end_second->setStatus(N_ACC);

    int i = max(end_first->getId(), end_second->getId()) + 1+1;
    Node* new_end = new Node(i);
    new_end->setStatus(id);

    i = i-1;
    Node* new_start = new Node(i);
    new_start->setStatus(N_ACC);

    Graph* g = pGraph;
    g->mergeGraph(graph_2->getEdges(), graph_2->getAllstates());

    g->addEdge(new_start, start_first,w);
    g->addEdge(new_start, start_second,w);

    g->addEdge(end_first, new_end,w);
    g->addEdge(end_second, new_end,w);

    g->setStart(new_start);
    g->setEnd(new_end);

    return g;
}

Graph *Helpers::mergePlus(Graph *pGraph) {
    return nullptr;
}

Graph *Helpers::mergeAst(Graph *pGraph) {
    return nullptr;
}

Graph *Helpers::mergeCont(Graph *pGraph, Graph *graph_2) {
    if(graph_2 == NULL)
        return pGraph;
    if(pGraph == NULL)
        return graph_2;

    return nullptr;
}
