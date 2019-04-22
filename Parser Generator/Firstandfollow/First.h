//
// Created by sohayla on 19/04/19.
//

#ifndef COMPILER_FIRST_H
#define COMPILER_FIRST_H

#include "Firstandfollow_tables.h"
#include <string>
#define  EPS "eps"

using namespace std;
class First {
private:
    CFG* cfg;
    Firstandfollow_tables * first_table;
    set<string> terminals;
    set<string> non_terminals;
    map<string, vector<vector<string>>> non_t_productions;
    vector<string> visited;
    map<string, vector<string>> firsts_of_non_terminal;
    void initializeFirstsMap();
public:
    First();
    void calculateFirst();

    void recurseOnNonTerminal(string non_t);
    vector<string> findFirst(vector<string> prod);
    bool checkIfEpsOccurs(vector<string>  firsts);

    void insertFirstsIntoMap(string non_t, int index, vector<string> firsts);

    void testFirst();

    string vectorTostring(vector<string> &vector);
};


#endif //COMPILER_FIRST_H
