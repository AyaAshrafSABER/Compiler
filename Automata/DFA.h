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
//        0       1
//    A   b     d
//    b
//    d
    //(one one)*

//    0 -> 1 -> 3 -> 1
    set<Node*> getTransitionStates(Node* state, Definition* def);
    set<Node*> getEpsilonClosure(Node* state);
    string getNodeStatus(set<Node*> set);
    void insertNewStateInInitialTable(Node* node);
    void BFS(Node* start);
    void testDFA();
    set<Node*> loopDefinition(Definition* def, Node* node);
    int tableContainsTheSameState(set<Node*> state);

public:
    /* Static access method. */
    static DFA* getInstance();
    vector< pair <Node*,  map<Definition*, Node*>>>   getDFA();
};


#endif //COMPILER_DFA_H
