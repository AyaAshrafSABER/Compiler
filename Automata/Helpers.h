//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_HELPERS_H
#define JAVA_COMPILER_HELPERS_H

#include <string>
#include <map>
#include <list>
#include "Graph.h"

using namespace std;
class Helpers {
private:
    vector<string> helpers;
    Definition *w;
    Helpers();
public :
    static Helpers* getInstance();
    Graph* mergeGraphs(Graph* graph_1, Graph* graph_2h, string helper, int* id);
    vector<string> getHelpers();

    Graph *mergeOr(Graph *pGraph, Graph *graph_2, int* id);

    Graph *mergePlus(Graph *pGraph, int* id);

    Graph *mergeAst(Graph *pGraph, int* id);

    Graph *mergeCont(Graph *pGraph, Graph *graph_2, int* id);

    bool isAhelper(string s);
};


#endif //JAVA_COMPILER_HELPERS_H
