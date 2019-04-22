//
// Created by sohayla on 19/04/19.
//

#ifndef COMPILER_FOLLOW_H
#define COMPILER_FOLLOW_H

#include <CFG.h>
#include "Firstandfollow_tables.h"
#include "TableObject.h"
#include "TestFirstFollow.h"

using namespace std;

class Follow {
private:
//    CFG* cfg;
    TestFirstFollow* cfg;
    Firstandfollow_tables * firstandfollow_tables;
    set<string> non_terminals;
    map<string, vector<vector<string>>> non_t_productions; //Non-terminal vector of (or)s
    map<string, vector<string>> follows_of_non_terminal;
    map<string, vector<TableObject*>> firsts;
    map<string, string> visited;
    void initializeFollowsMap();
    void insertFollow (string nonTerminal, string terminal);
    void findFollowsInNonTerminal(string nonTerminal);
    void findFollowInProduction(vector<string> &vector, string nonTerminal, string leftNonTerminal);
    bool checkIfExists(string nonterminal, string terminal);
    void insertDollarSign();
    void loopNonTerminal();
    void insertFirstInFollow(string vector, string nonTerminal);
    void insertFollowLeftNonTerminal (string leftNonTerminal, string nonTerminal);
    void testOutput ();
public:
    Follow();

    bool containsEps(string nonTerminal);
};


#endif //COMPILER_FOLLOW_H
