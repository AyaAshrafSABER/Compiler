//
// Created by AYAOSMAN on 4/17/2019.
//

#ifndef COMPILER_LEFTRECURSIONREMOVER_H
#define COMPILER_LEFTRECURSIONREMOVER_H

#include "..\CFG.h"
#include <string.h>
#include <vector>
#include <set>
#include <map>

using namespace std;
class LeftRecursionRemover {
private:
    /* Here will be the instance stored. */
    static LeftRecursionRemover* instance;
    /* Private constructor to prevent instancing. */
    LeftRecursionRemover ();
    CFG* cfg;
    int id = 0;
    void findLeftRecursion();
    bool checkLeftRecursion (vector<vector<string>> *alpha, vector<vector<string>> *beta, string key, vector<vector<string>> prodctions);
    string renamingNonTerminal(string nonTerminal,int id);
    void substituteNonterminalInProductions(vector<vector<string>> *newProduction, vector<string> currProsuction,vector<vector<string>> nextProductions);
public:
    static LeftRecursionRemover* getInstance();

};


#endif //COMPILER_LEFTRECURSIONREMOVER_H
