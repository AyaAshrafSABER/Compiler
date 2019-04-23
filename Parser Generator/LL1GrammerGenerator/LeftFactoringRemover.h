//
// Created by TARGET on 4/17/2019.
//

#ifndef COMPILER_LEFTFACTORINGREMOVER_H
#define COMPILER_LEFTFACTORINGREMOVER_H

#include <string>
#include <vector>
#include <map>
#include "..\CFG.h"

using namespace std;

class LeftFactoringRemover {
private:
    map<string, vector<vector<string>>> non_t_productions;
    map<string, vector<vector<string>>> factored_productions;
    /* Here will be the instance stored. */
    static LeftFactoringRemover* instance;
    /* Private constructor to prevent instancing. */
     LeftFactoringRemover ();
    void leftFactoring(string productionLabel, int id, vector<vector<string>> rightSide);
    void loopProductions();
    void removeGroupedVectorsFromRightSide (vector<vector<string>> rightSide, vector<vector<string>> groupOfSamePrefix);
    int recursionPrefix (vector<vector<string>> rightSide);
    public:
    static LeftFactoringRemover* getInstance();
};

#endif //COMPILER_LEFTFACTORINGREMOVER_H
