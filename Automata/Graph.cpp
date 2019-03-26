//
// Created by sohayla on 20/03/19.
//

#include <algorithm>
#include "Graph.h"
Graph::Graph() {
    start = NULL;
    end = NULL;
    states.clear();
    transitions.clear();
}

bool Graph::addEdge(Node *source, Node *Destination, Definition *weight) {
    if(find(states.begin(), states.end(), source) == states.end())
        states.push_back(source);
    if(find(states.begin(), states.end(),Destination ) == states.end())
        states.push_back(Destination);
    if(this->getTargetNode(source, weight) == Destination)
        return false;
    Edge* transition = new Edge(source, Destination, weight);
    source->insertEdge(transition, false);
    Destination->insertEdge(transition, true);
    this->transitions.push_back(transition);
    return true;

}

Node* Graph::getTargetNode(Node *src, Definition *weight) {
    if(find(states.begin(), states.end(), src) == states.end())
        return NULL;
    vector<Edge*> outward = src->getOutwardEdges();
    for(int i = 0; i < outward.size(); i++) {
        if(outward[i]->getWeight() == weight) {
            return outward[i]->getDestination();
        }
    }
    return NULL;

}



vector<Node*> Graph::getAllstates() {
    return this->states;
}

Node* Graph::getEndState() {
    return this->end;
}

void Graph::setEnd(Node *new_e) {
    if(find(states.begin(), states.end(), new_e) == states.end())
        this->states.push_back(new_e);
    this->end = new_e;
}

void Graph::setStart(Node *new_s) {
    if(find(states.begin(), states.end(), new_s) == states.end())
        this->states.push_back(new_s);
    this->start = new_s;
}
Node* Graph::getStartState() {
    return this->start;
}


vector<Edge*> Graph::getEdges() {
    return this->transitions;
}



void Graph::mergeGraph(vector<Edge *> edges, vector<Node *> states) {
    for (int i = 0; i < edges.size() ; ++i) {
        this->transitions.push_back(edges[i]);
    }
    for (int i = 0; i < states.size() ; ++i) {
        this->states.push_back(states[i]);
    }
}