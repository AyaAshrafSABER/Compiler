//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_HELPERS_H
#define JAVA_COMPILER_HELPERS_H

#include <string>
#include <map>
#include "Graph.h"

using namespace std;
class Helpers {
private:
    map<string, int> helpers;
public :
    Graph* mergeGraphs(Graph* graph_1, Graph* graph_2h, string helper);
    int getHelperCode(string helper);

};


#endif //JAVA_COMPILER_HELPERS_H
