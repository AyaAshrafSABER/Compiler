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

class DFA {
private:
    /* Here will be the instance stored. */
    static DFA* instance;
    /* Private constructor to prevent instancing. */
    DFA();

    vector< pair <Node*,  map<Definition*,set<Node*>>>>  transitionStateTable;
public:
    /* Static access method. */
    static DFA* getInstance();
    vector< pair <Node*,  map<Definition*,set<Node*>>>>   getDFA();
};


#endif //COMPILER_DFA_H
