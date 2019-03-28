//
// Created by TARGET on 3/23/2019.
//

#include <list>
#include <iostream>
#include <algorithm>
#include "DFA.h"
#include "NFA.h"

/* Null, because instance will be initialized on demand. */
DFA* DFA::instance = 0;

DFA* DFA::getInstance() {
    if (instance == 0)
    {
        instance = new DFA();
    }

    return instance;
}

set<Node*> DFA::getTransitionStates (Node* state, Definition* def) {
    set<Node*> setReturned;
    set<Node*> setPtr = nfaStateTable.at(state).at(def);
//    copy(setPtr.begin(), setPtr.end(), setReturned);
    return setReturned;
}

set<Node*> DFA::getEpsilonClosure(Node *start) {
    Definition* Eps; //TODO get Epsilon
    set<Node*> setReturned;
    Node* state;

    list<Node*> queue;
    queue.push_back(start);
    while(!queue.empty()) {
        state = queue.front();
        queue.pop_front();
        //check if it doesn't exist in set
        if(setReturned.find(state) != setReturned.end()) {
            setReturned.insert(state);
            set<Node*> set = getTransitionStates(state, Eps);
            //add edges in queue
            for (std::set<Node*>::iterator it=set.begin(); it!=set.end(); ++it) {
                queue.push_back(*it);
            }
        }
    }
    return setReturned;
}

int DFA::tableContainsTheSameState(set<Node *> state) {
    for(vector<set<Node*>>::iterator it = stateMappingTable.begin(); it != stateMappingTable.end(); ++it ) {
        if((*it) == state) {
            return it - stateMappingTable.begin();
        }
    }
    return 0;
}

DFA::DFA() {
    NFA* nfa;
    Graph* graph = nfa->getInstance()->getAutomata();
    Node* start = graph->getStartState();
    int numberOfStates = graph->getAllstates().size();
    //initiate initialStateTable
    BFS(start, numberOfStates);

    int id = 1;
    Node* state = new Node(id);
    stateMappingTable.push_back(getEpsilonClosure(start));
    //TODO create state add status w ay 7aga tanya
    transitionStateTable.push_back(make_pair(state,map<Definition*,Node*>()));
    id++;
    vector<pair<Node*, map<Definition*,Node*>>>::iterator itVector;
    for (itVector = transitionStateTable.begin(); itVector != transitionStateTable.end(); ++itVector) {
        //get for each definition all states from epsilon transition
        set<Node *> setOfState = stateMappingTable[(*itVector).first->getId()];
        vector<Definition *> definitions; //TODO get definitions
        for (vector<Definition *>::iterator itDef = definitions.begin(); itDef != definitions.end(); ++itDef) {
            //get set for that definition
            set<Node *> setOfDefinition;
            for (set<Node *>::iterator itSet = setOfState.begin(); itSet != setOfState.end(); ++itSet) {
                set<Node *> returnedSet = getTransitionStates(*itSet, *itDef);
                setOfDefinition.insert(returnedSet.begin(), returnedSet.end());
            }
            //get the state eps closure
            set<Node *> eps;
            for (set<Node *>::iterator itSet = setOfDefinition.begin(); itSet != setOfDefinition.end(); ++itSet) {
                set<Node *> returnedSet = getEpsilonClosure(*itSet);
                eps.insert(returnedSet.begin(), returnedSet.end());
            }
            setOfDefinition.insert(eps.begin(), eps.end());

            if (int idOfState = tableContainsTheSameState(setOfDefinition)) {
                Node *stateInDefinition = transitionStateTable[idOfState].first;
                (*itVector).second.insert(make_pair(*itDef, stateInDefinition));
            } else {
                Node *state = new Node(id);
                id++;
                //TODO ezai 2a3mel state??
                (*itVector).second.insert(make_pair(*itDef, state));
                transitionStateTable.push_back(make_pair(state, map<Definition *, Node *>()));
                stateMappingTable.push_back(setOfDefinition);
            }
        }
    }
    //TODO set memory free for all data structures unused
}

void DFA::loopDefinition(Definition* def, Node* state, set<Node*> set) {
    vector<Edge*> edges = state->getOutwardEdges();
    for (vector<Edge*>::iterator it = edges.begin() ; it != edges.end(); ++it) {
        if((*it)->getWeight() == def) {
            set.insert((*it)->getDestination());
        }
    }
}

void DFA::insertNewStateInInitialTable(Node* state) {
    map<Definition*, set<Node*>> pairMap;
    vector<Definition*> definitions; //TODO get definitions
    for (vector<Definition*>::iterator it = definitions.begin(); it != definitions.end(); ++it) {
        set<Node*> set;
        loopDefinition((*it), state, set);
        pairMap.insert(make_pair((*it),set));
    }
    this->nfaStateTable.insert(make_pair(state, pairMap));
}

void DFA::BFS(Node* start, int numberOfStates) {
    bool *visited = new bool[numberOfStates];
    for(int i = 0; i < numberOfStates; i++)
        visited[i] = false;

    list<Node*> queue;

    visited[start->getId()] = true;
    queue.push_back(start);

    while(!queue.empty()) {
        start = queue.front();
        queue.pop_front();

        vector<Edge*> edges = start->getOutwardEdges();
        for (vector<Edge*>::iterator it = edges.begin() ; it != edges.end(); ++it) {
            if (!visited[(*it)->getDestination()->getId()]) {
                visited[(*it)->getDestination()->getId()] = true;
                queue.push_back((*it)->getDestination());
                insertNewStateInInitialTable((*it)->getDestination());
            }
        }
    }
}

vector< pair <Node*,  map<Definition*, Node*>>> DFA::getDFA() {
    return this->transitionStateTable;
}
