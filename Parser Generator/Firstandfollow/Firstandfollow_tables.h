//
// Created by sohayla on 19/04/19.
//

#ifndef COMPILER_FIRSTANDFOLLOW_TABLES_H
#define COMPILER_FIRSTANDFOLLOW_TABLES_H

#include <map>
#include <vector>
#include <set>
#include "TableObject.h"
#include "CFG.h"

using namespace std;
class Firstandfollow_tables {
private:
    set<string> non_terminals;
    map<string, vector<TableObject*>> first;
    map<string, vector<TableObject*>> follow;
    Firstandfollow_tables();
public:
    static Firstandfollow_tables* getInstance();
    void insertInFirst(string non_t, TableObject* object);
    void insertInFollow(string non_t, TableObject* object);
    map<string, vector<TableObject*>> getFirst();
    map<string, vector<TableObject*>> getFollow();
    void initializeMap();
};


#endif //COMPILER_FIRSTANDFOLLOW_TABLES_H
