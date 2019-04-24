//
// Created by Rowan on 19-Apr-19.
//

#ifndef COMPILER_PARSERTABLE_H
#define COMPILER_PARSERTABLE_H

#include <map>
#include <vector>
#include "TableObject.h"
#include "Firstandfollow_tables.h"

#define ERROR -1
#define SYNCH -2
#define EPS "\\L"

using namespace std;
class ParsingTable {
private:
    ParsingTable();
    map<string, vector<TableObject*>> first;
    map<string, vector<string>> follow;
    map<string,map<string,int>> parsingTable;
    set<string> nonTerminal;
    set<string> terminal;
    map<string, vector<vector<string>>> non_t_productions;
    void printTable();
    string vectorTostring(vector<string> &vector);
public:
    static ParsingTable* getInstance();
    void createParsingTable();
    void printError();
    map<string,map<string,int>> getParsingTable();
    vector<string> getTokens();
};


#endif //COMPILER_PARSERTABLE_H
