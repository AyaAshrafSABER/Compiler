//
// Created by TARGET on 3/23/2019.
//

#include <list>
#include <iostream>
#include <algorithm>
#include "DFA.h"
#include "NFA.h"
#include "Definitions_Table.h"

/* Null, because instance will be initialized on demand. */
DFA* DFA::instance;

DFA* DFA::getInstance() {
    if (instance == NULL) {
        instance = new DFA();
    }
    return instance;
}
set<Node*> DFA::getTransitionStates (Node* state, Definition* def) {
    if(nfaStateTable.find(state) != nfaStateTable.end()) {
        if(nfaStateTable.at(state).find(def) != nfaStateTable.at(state).end()) {
            return nfaStateTable.at(state).at(def);
        }
    }
    return set<Node*>();
}

set<Node*> DFA::getEpsilonClosure(Node *start) {
    Definition* Eps = Definitions_Table::getInstance()->getDefinitions(EPS);
    set<Node*> setReturned;
    Node* state;

    list<Node*> queue;
    queue.push_back(start);
    while(!queue.empty()) {
        state = queue.front();
        queue.pop_front();
        //check if it doesn't exist in set
        if(setReturned.find(state) == setReturned.end()) {
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

string DFA::getNodeStatus(set<Node*> set) {
    for (std::set<Node*>::iterator it = set.begin(); it != set.end(); ++it) {
        if((*it)->getStatus() != N_ACC) {
            return (*it)->getStatus();
        }
    }
    return N_ACC;
}

void DFA::testDFA() {
    cout << "Def    " << "  1   " << "  2   " << "..." <<endl;
    for (vector<pair <Node*,  map<Definition*,Node*>>>::iterator it = transitionStateTable.begin() ; it != transitionStateTable.end(); ++it) {
        map<Definition*, Node*> map = (*it).second;
        cout<<(*it).first->getId()<<"    ";
        for (std::map<Definition*, Node*>::iterator itDef = map.begin(); itDef != map.end(); ++itDef) {
            cout<<"     "<<(*itDef).second->getId()<<"       ";
        }
        cout<< endl;
    }
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
    NFA* nfa = NFA::getInstance();
    Graph* graph = nfa->getAutomata();

    Node* start = graph->getStartState();
    //initiate initialStateTable
    BFS(start);

    Node* dummyState = NULL;
    int id = 0;
    Node* state = new Node(id);
    state->setStatus(start->getStatus());
    stateMappingTable.push_back(getEpsilonClosure(start));
    transitionStateTable.push_back(make_pair(state,map<Definition*,Node*>()));
    id++;

    Definition* Eps = Definitions_Table::getInstance()->getDefinitions(EPS);
    for (vector<pair<Node*, map<Definition*,Node*>>>::size_type itVector = 0; itVector != transitionStateTable.size(); ++itVector) {
        //get for each definition all states from epsilon transition
        set<Node *> setOfState = stateMappingTable[transitionStateTable[itVector].first->getId()];
        //get definitions table iterator
        map<string, Definition*> definitions = Definitions_Table::getInstance()->getTable();

        for (map<string, Definition*>::iterator itDef = definitions.begin(); itDef != definitions.end(); ++itDef) {
            //get set for that definition
            if(itDef->second == Eps) {
                continue;
            }
            set<Node *> returnedSetOfEachDefinition;
            for (set<Node *>::iterator itSet = setOfState.begin(); itSet != setOfState.end(); ++itSet) {
                set<Node *> returnedSet = getTransitionStates(*itSet, itDef->second);
                returnedSetOfEachDefinition.insert(returnedSet.begin(), returnedSet.end());
            }
            //get the state eps closure
            set<Node *> eps;
            for (set<Node *>::iterator itSet = returnedSetOfEachDefinition.begin(); itSet != returnedSetOfEachDefinition.end(); ++itSet) {
                set<Node *> returnedSet = getEpsilonClosure(*itSet);
                eps.insert(returnedSet.begin(), returnedSet.end());
            }
            returnedSetOfEachDefinition.insert(eps.begin(), eps.end());
            if(returnedSetOfEachDefinition.empty()) {
//                if (dummyState == NULL) {
//                    dummyState = new Node(id);
//                    id++;
//                    dummyState->setStatus(N_ACC);
//                    map<string, Definition*> definitions = Definitions_Table::getInstance()->getTable();
//                    for (map<string, Definition*>::iterator it = definitions.begin(); it != definitions.end(); ++it) {
//                        transitionStateTable[itVector].second.insert(make_pair(it->second, dummyState));
//                    }
//                }
//                transitionStateTable[itVector].second.insert(make_pair(itDef->second, dummyState));
                //TODO check example el sheet 2 types of dummy nodes
                continue;
            }
            if (int idOfState = tableContainsTheSameState(returnedSetOfEachDefinition)) {
                Node *stateInDefinition = transitionStateTable[idOfState].first;
                transitionStateTable[itVector].second.insert(make_pair(itDef->second, stateInDefinition));
            } else {
                Node *state = new Node(id);
                id++;
                state->setStatus(getNodeStatus(returnedSetOfEachDefinition));
                transitionStateTable[itVector].second.insert(make_pair(itDef->second, state));
                transitionStateTable.push_back(make_pair(state, map<Definition *, Node *>()));
                stateMappingTable.push_back(returnedSetOfEachDefinition);
            }
        }
    }
    //TODO set memory free for all data structures unused
    //TODO test graph cout
    testDFA();
}

set<Node*> DFA::loopDefinition(Definition* def, Node* state) {
    set<Node*> set;
    vector<Edge*> edges = state->getOutwardEdges();
    for (vector<Edge*>::iterator it = edges.begin() ; it != edges.end(); ++it) {
        if((*it)->getWeight() == def) {
            set.insert((*it)->getDestination());
        }
    }
    return set;
}

void DFA::insertNewStateInInitialTable(Node* state) {
    map<Definition*, set<Node*>> pairMap;
    map<string, Definition*> definitions = Definitions_Table::getInstance()->getTable();
    for (map<string, Definition*>::iterator it = definitions.begin(); it != definitions.end(); ++it) {
        set<Node*> set = loopDefinition(it->second, state);
        if(!set.empty()) {
            pairMap.insert(make_pair((it->second), set));
        }
    }
    this->nfaStateTable.insert(make_pair(state, pairMap));
}

void DFA::BFS(Node* start) {
    map <int, bool> visited;
    list<Node*> queue;

    visited.insert(make_pair(start->getId(),true));
    queue.push_back(start);

    while(!queue.empty()) {
        start = queue.front();
        queue.pop_front();
        visited.insert(make_pair(start->getId(),true));
        insertNewStateInInitialTable(start);
        vector<Edge*> edges = start->getOutwardEdges();
        for (vector<Edge*>::iterator it = edges.begin() ; it != edges.end(); ++it) {
            if (visited.find((*it)->getDestination()->getId()) == visited.end()) {
                visited.insert(make_pair((*it)->getDestination()->getId(),true));
                queue.push_back((*it)->getDestination());
                insertNewStateInInitialTable((*it)->getDestination());
            }
        }
    }
}

vector< pair <Node*,  map<Definition*, Node*>>> DFA::getDFA() {
    return this->transitionStateTable;
}
