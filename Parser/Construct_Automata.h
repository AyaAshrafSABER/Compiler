//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_CONSTRUCT_AUTOMATA_H
#define JAVA_COMPILER_CONSTRUCT_AUTOMATA_H

#include <string>
#include <map>
#include <stack>
#include "../Automata/Graph.h"

using namespace std;
#define EPS "eps"
class Construct_Automata {
private:
    map<string, Graph*> sub_Automatas;
    stack<string> building;
public:
    void insertNewSub(Graph* sub_g);
    bool constructNFA();
    bool constructGraph(string line);

};


#endif //JAVA_COMPILER_CONSTRUCT_AUTOMATA_H
