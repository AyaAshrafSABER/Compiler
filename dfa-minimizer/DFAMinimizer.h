//
// Created by AyaOsman on 3/23/2019.
//

#ifndef COMPILER_DFAMinimizer_H
#define COMPILER_DFAMinimizer_H

#include <vector>
#include <map>
#include <set>
#include<iterator>
#include <string.h>
#include <iostream>
#include "../Automata/Definition.h"
#include "../Automata/Node.h"
#include "../Automata/DFA.h"
#include "../Automata/Graph.h"
#include "../Automata/Definitions_Table.h"
class DFAMinimizer {
private:
    /* Here will be the instance stored. */
    static DFAMinimizer* instance;
    /* Private constructor to prevent instancing. */
    DFAMinimizer();

    vector<pair<Node*, map<Definition*, Node*>>> minimizedTransitionStateTable;
    DFA* dfa;
    set<Node*> Accepted;
    set<Node*> NotAccepted;
    vector<set<Node*>> previousPartition;
    vector<set<Node*>> nextPartition;
    Node* startState;

private:
    void setFirstPartition(set<Node*> *Acc, set<Node*>* Not_Acc, vector<set<Node*>> *partitions);
    void partitioning(DFA* dfa, vector<set<Node*>>*pre, vector<set<Node*>> *next);
    void partitioningHelper(DFA* dfa, vector<set<Node*>>*pre,vector<set<Node*>>*next);
    void distinguishStates(DFA* dfa,vector<set<Node*>> *P , vector<set<Node*>> *n, set<Node*> curr);
    bool areEquivalentStates(DFA* dfa , vector<set<Node*>> *P, Node* A , Node *B);
    bool isEqualPartition(vector<set<Node*>> *P,vector<set<Node*>> *N);
    void buildMinimumeDFA(DFA* dfa,vector<pair<Node*, map<Definition*, Node*>>>*ret, vector<set<Node*>> *nextPartition);
public:
    Node *getStartState() const;

    void setStartState(Node *startState);
    /* Static access method. */
    static DFAMinimizer* getInstance();
    vector<pair<Node*,map<Definition*,Node*>>> *getMinimizedDFA();
    void printMinimizedDFA();

};


#endif //COMPILER_DFAMinimizer_H
