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
#include "../Automata/Definitions_Table.h"


using namespace std;
#define EPS "eps"
class Construct_Automata {
private:
    vector<Graph*> sub_Automatas;
    Definitions_Table* def_t;
    int def_id = 1;
    int nfa_id = 1;
    list<string> helpers;
    int node_id;
public:
    Construct_Automata();
    bool constructAutomata(string line);

    Graph* constructNFASubGraph(vector<string> tokens);
    bool constructDefinition(string id, vector<string> definition);

    bool constructNFA();

    Graph* recurseBuild(vector<string> tokens, int* i);

    Graph *recurseBrackets(vector<string> *pVector, int *pInt);

    string helperValue(vector<string> *pVector);

    Graph *createGraph(string basic_string, int *pInt);

    Graph *splitToken(string basic_string, int *pInt, string h);

    Graph *createGraph(vector<string> *pVector, string basic_string, int *pInt, string h);
    Graph* createGraphFromExistingDefintition(Definition* def, int* i, string temp) ;


        void testGraph(Graph *pGraph);

    Graph* getCont(Graph *d_g, vector<string> *tokens, int *i);

    void constructKeyWords(vector<string> tokens);

    void constructPunct(vector<string> tokens);
};


#endif //JAVA_COMPILER_CONSTRUCT_AUTOMATA_H
