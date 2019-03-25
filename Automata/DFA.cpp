//
// Created by TARGET on 3/23/2019.
//

#include <list>
#include <iostream>
#include "DFA.h"
#include "NFA.h"

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

set<Node*> DFA::getTransitionStates (Node* state, Definition* def) {
    set<Node*> setReturned;
    set<Node*> setPtr = initialStateTable.at(state).at(def);
    copy(setPtr.begin(), setPtr.end(), setReturned);
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
            //addedges in queue //TODO
        }
    }
    return setReturned;

}

//constructor
DFA::DFA()
{
    NFA nfa;
    Graph* graph = nfa.getAutomata();
    Node* start = graph->getStartState();
    int numberOfStates = graph->getAllstates().size();
    //initiate initialStateTable
    BFS(start, numberOfStates);

    //loop while new vector isn't empty or push in queue
        //take the Node
        //get its epison transitions --> recursively
        //create new set

        //---NOW I have my state---
        //loop definitions
            //get set transitions for each epison closure
            //check table if it contains the same state
            //->push new state
        //
        //




    // loop for all epison transition
    set<Node*> state = set_union();
    //

    //check if table contains the same state
    //->push new state to table
    //loop get state for each def and add it to the table
    //add their epison closure
    //repeat until no new state is added

    //required
    //-set union
    //-set difference to be zero //condition of equality


    //set memory free for all data structures unused
}
void DFA::loopDefinition(Definition* def, Node* state, set<Node*> set) {
    vector<Edge*> edges = state->getOutwardEdges();
    for (vector<Edge*>::iterator it = edges.begin() ; it != edges.end(); ++it) {
        if((*it)->getWeight() == def) {
            set.insert((*it)->getDestination());
        }
    }
}
void DFA::insertNewStateInTransitionTable(Node* state) {
    map<Definition*, set<Node*>> pairMap;
        /*//loop on definitions
        set<Node*> set = loopDefinition(def, state);
        pairMap.insert(def,set);
        //*/
    vector<Definition*> definitions; //TODO get definitions
    for (vector<Definition*>::iterator it = definitions.begin() ; it != definitions.end(); ++it) {
        set<Node*> set;
        loopDefinition((*it), state, set);
        pairMap.insert(make_pair((*it),set));
    }
    this->initialStateTable.insert(make_pair(state, pairMap));
}

void DFA::BFS(Node* start, int numberOfStates) {
    bool *visited = new bool[numberOfStates];
    for(int i = 0; i < numberOfStates; i++)
        visited[i] = false;

    list<Node*> queue;

    visited[start->getId()] = true;
    queue.push_back(start);

    while(!queue.empty())
    {
        start = queue.front();
        queue.pop_front();

        vector<Edge*> edges = start->getOutwardEdges();
        for (vector<Edge*>::iterator it = edges.begin() ; it != edges.end(); ++it) {
            if (!visited[(*it)->getDestination()->getId()]) {
                visited[(*it)->getDestination()->getId()] = true;
                queue.push_back((*it)->getDestination());
                insertNewStateInTransitionTable((*it)->getDestination());
            }
        }
    }
}

