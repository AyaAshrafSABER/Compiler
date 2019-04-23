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
    CFG* cfg;
    vector<vector<string>> alpha;
    vector<vector<string>> beta;
    void findLeftRecursion();
    bool checkLeftRecursion (string key, vector<vector<string>> prodctions);
    void solveLeftRecursion( vector<vector<string>> alpha,vector<vector<string>> beta);
    string renamingNonTermial(string nonTerminal);
    void substituteNonterminalInProductions();
public:
    LeftRecursionRemover(CFG *cfg);
};


#endif //COMPILER_LEFTRECURSIONREMOVER_H
