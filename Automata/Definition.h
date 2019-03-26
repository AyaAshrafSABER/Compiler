//
// Created by sohayla on 22/03/19.
//

#ifndef JAVA_COMPILER_DEFINITION_H
#define JAVA_COMPILER_DEFINITION_H

#include "Graph.h"

using namespace std;
class Definition {
private:
    Graph *definition;
public:
    Definition(Graph *def);

    Graph *getDef();

    bool contains(string input);

    bool setDef(Graph *def);

    Node* DFS(Node *start, int numberOfStates, string input);
};


#endif //JAVA_COMPILER_DEFINITION_H