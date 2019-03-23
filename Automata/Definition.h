//
// Created by sohayla on 22/03/19.
//

#ifndef JAVA_COMPILER_DEFINITION_H
#define JAVA_COMPILER_DEFINITION_H

#include "Graph.h"

using namespace std;
class Definition {
private:
    void* definition;
    bool is_string;
public:
    Definition(void* def, bool is_string);
    void* getDef();
    bool contains(string input);
    bool setDef(void* def);
};


#endif //JAVA_COMPILER_DEFINITION_H
