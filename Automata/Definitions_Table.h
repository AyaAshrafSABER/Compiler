//
// Created by sohayla on 24/03/19.
//

#ifndef JAVA_COMPILER_DEFINITIONS_TABLE_H
#define JAVA_COMPILER_DEFINITIONS_TABLE_H

#include <string>
#include <map>
#include "Definition.h"

using namespace std;
class Definitions_Table {
private:
    map<string, Definition*> definitions;
    Definitions_Table();
public:
    static Definitions_Table* getInstance();
    void insertInMap(string id, Definition* definition);
    map<string, Definition*> getTable();
    Definition* getDefinitions(string id);
    void test_Definitions();

};


#endif //JAVA_COMPILER_DEFINITIONS_TABLE_H
