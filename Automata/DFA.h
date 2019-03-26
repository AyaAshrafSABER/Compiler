//
// Created by TARGET on 3/23/2019.
//

#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H
#include <vector>
#include <map>
#include <set>
#include "Definition.h"
#include "Node.h"

using namespace std;

class DFA {
private:
    /* Here will be the instance stored. */
    static DFA* instance;
    /* Private constructor to prevent instancing. */
    DFA();

    map< Node*,  map<Definition*,set<Node*>>> nfaStateTable;
    vector< set<Node*>>  stateMappingTable;
    vector< pair <Node*,  map<Definition*,Node*>>>  transitionStateTable;

    set<Node*> getTransitionStates(Node* state, Definition* def);
    set<Node*> getEpsilonClosure(Node* state);

    void insertNewStateInInitialTable(Node* node);
    void BFS(Node* start, int numberOfStates);
    void loopDefinition(Definition* def, Node* node, set<Node*> set);
    int tableContainsTheSameState(set<Node*> state);

public:
    /* Static access method. */
    static DFA* getInstance();
    vector< pair <Node*,  map<Definition*, Node*>>>   getDFA();
};


#endif //COMPILER_DFA_H
