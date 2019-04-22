//
// Created by saraheldafrawy on 22/04/19.
//

#ifndef COMPILER_TESTFIRSTFOLLOW_H
#define COMPILER_TESTFIRSTFOLLOW_H

#include <map>
#include <set>
#include <vector>

using namespace std;

class TestFirstFollow {
private:
    static TestFirstFollow* instance;
    TestFirstFollow();
    set<string> terminals;
    set<string> non_terminals;
    map<string, vector<vector<string>>> non_t_productions;
    string startSymbol;
public:
    static TestFirstFollow* getInstance();
    string getStartSymbol();
    map<string, vector<vector<string>>> getProduction();
    set<string> getTerminal();
    set<string> getNonTerminal();
};


#endif //COMPILER_TESTFIRSTFOLLOW_H
