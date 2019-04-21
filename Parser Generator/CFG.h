//
// Created by AYA OSMAN on 4/17/2019.
//

#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#include <set>
#include <string>
#include <vector>
#include <map>

#define EPSILON "\\L"

using namespace std;
class CFG {
private:
    /* Here will be the instance stored. */
    static CFG* instance;
    /* Private constructor to prevent instancing. */
    CFG();

    set<std::string> nonTerminal;
    set<string> terminal;
    string startSymbol;
    map<string, vector<vector<string>>> production;


public:
    /* Static access method. */
    static CFG* getInstance();

    const set <string> &getNonTerminal() const;

    void setNonTerminal(const set <string> &nonTerminal);

    const set <string> &getTerminal() const;

    void setTerminal(const set <string> &terminal);

    const string &getStartSymbol() const;

    void setStartSymbol(const string &startSymbol);

    const map<string, vector<vector<string>>> &getProduction() const;

    void setProduction(const map<string, vector<vector<string>>> &production);

    void insetRule(string key, vector<vector<string>>);

    void insertTerminal(string terminal);
    void insetNonTerminal(string nonTerminal);

    bool IsNonTerminal(string word);

};


#endif //COMPILER_CFG_H
