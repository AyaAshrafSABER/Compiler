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

    map< Node*,  map<Definition*,set<Node*>>> initialStateTable;
    vector< pair <set<Node*>,  map<Definition*,set<Node*>>>>  setTransitionStateTable;
    vector< pair <Node*,  map<Definition*,set<Node*>>>>  transitionStateTable;

    set<Node*> getTransitionStates(Node* state, Definition* def);
    set<Node*> getEpsilonClosure(Node* state);

    void insertNewStateInTransitionTable(Node* node);
    void BFS(Node* start, int numberOfStates);
    void loopDefinition(Definition* def, Node* node, set<Node*> set);

public:
    /* Static access method. */
    static DFA* getInstance();
    vector< pair <Node*,  map<Definition*,set<Node*>>>>   getDFA();
};


#endif //COMPILER_DFA_H
