//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_CONSTRUCT_AUTOMATA_H
#define JAVA_COMPILER_CONSTRUCT_AUTOMATA_H

#include <string>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include "Tokenizing.h"
#include "../Automata/Graph.h"
#include "../Automata/NFA.h"
#include "../Automata/Definition.h"


using namespace std;
#define EPS "eps"
class Construct_Automata {
private:
    list<Graph*> sub_Automatas;
    map<string, Definition*> definitions;
    list<string> helpers;
    int node_id;
public:
    Construct_Automata();
    bool constructAutomata(string line);

    Graph* constructGraph(vector<string> tokens);
    bool constructDefinition(string id, vector<string> definition);

    bool constructNFA();

    Graph* recurseBuild(vector<string> tokens, int i);

};


#endif //JAVA_COMPILER_CONSTRUCT_AUTOMATA_H
