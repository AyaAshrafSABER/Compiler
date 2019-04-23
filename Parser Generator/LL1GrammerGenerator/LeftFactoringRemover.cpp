//
// Created by TARGET on 4/17/2019.
//

#include "LeftFactoringRemover.h"
LeftFactoringRemover* LeftFactoringRemover::instance;

LeftFactoringRemover::LeftFactoringRemover () {
    //loop each production
    //check if it contains a vector
    //return vector index
    //remove sub prefix to be added
    // ->loop for each vector for first word and add it in a vctor if vector length > 2
    // -> loop to get the rest of the prefix
    // -> append the rest of the prefix and remove old vectors
    // -> create new production containing the two vectors without the prefix
    //TODO get map of production

    CFG* cfg = CFG::getInstance();
    this->non_t_productions = cfg->getProduction();
    loopProductions();
    cfg->setProduction(this->factored_productions);
}

void LeftFactoringRemover::loopProductions() {
    auto itMap = non_t_productions.begin();
    while (itMap != non_t_productions.end()) { // left factoring for each production loop
        int id = 1;
        leftFactoring((itMap)->first, id, (itMap)->second);
        itMap++;
    }
}

void LeftFactoringRemover::leftFactoring(string productionLabel, int id, vector<vector<string>> rightSide) {
    bool visited[rightSide.size()];
    for(int i = 0 ; i < rightSide.size(); i++) {
        visited[i] = false;
    }
    factored_productions.insert(make_pair(productionLabel, rightSide));
    for(int i = 0; i < rightSide.size(); i++) {
        if(visited[i])
            continue;
        vector<vector<string>> groupOfSamePrefix; //should create new empty vector
        groupOfSamePrefix.push_back(rightSide[i]);
        visited[i] = true;
        for (int j = i + 1; j < (rightSide.size()); j++) {
            if(rightSide[i][0] == rightSide[j][0]) {
                groupOfSamePrefix.push_back(rightSide[j]);
                visited[j] = true;
            }
        }
        if(groupOfSamePrefix.size() > 2) {
            //start recursion and create new production
            //-> return index from recursion
            //-> get prefix and add to it new production label
            //-> create the new vector to production  --> BxA'|dz where A' new production
            //-> remove old production and push modified production to new map
            //-> remove from the production the two vectors and push back the new vector
            //-> call left factoring for the new production
            removeGroupedVectorsFromRightSide(rightSide, groupOfSamePrefix);
            string newProductionLabel = productionLabel + to_string(id) + "'";
            CFG::getInstance()->insetNonTerminal(newProductionLabel);
            int indexPrefix = recursionPrefix(rightSide);
            vector<string> modifiedVector;
            for(int i = 0; i <= indexPrefix; i++)
                modifiedVector.push_back(groupOfSamePrefix[0][i]);
            modifiedVector.push_back(newProductionLabel);
            rightSide.push_back(modifiedVector);
            for(int i = 0; i < groupOfSamePrefix.size(); i++) {
                groupOfSamePrefix[i].erase(groupOfSamePrefix[i].begin(), groupOfSamePrefix[i].begin() + indexPrefix);
                if(groupOfSamePrefix[i].size() == 0) {
                    groupOfSamePrefix[i].push_back({EPSILON});
                }
            }
            leftFactoring(productionLabel, id + 1, groupOfSamePrefix);
        }
    }
}

void LeftFactoringRemover::removeGroupedVectorsFromRightSide (vector<vector<string>> rightSide,
                                                              vector<vector<string>> groupOfSamePrefix) {
    int j = 0;
    for(int i = 0; i < rightSide.size() && j < groupOfSamePrefix.size(); i++) {
        if(rightSide[i] == rightSide[j]) {
            //groupOfPrefix have elements in the same order in rightside
            //so no need of checking from start again. Like sorted arrays
            rightSide.erase(rightSide.begin()+i);
            i--;
            j++;
        }
    }

}
int LeftFactoringRemover::recursionPrefix (vector<vector<string>> rightSide) {
    int i = 1;
    while (true) {
        string word = rightSide[0][i];
        for(int j = 1; j < rightSide.size(); j++) {
            if(i == rightSide[j].size() || rightSide[j][i] !=  word) {
                return i -1;
            }
        }
    }
}

LeftFactoringRemover* LeftFactoringRemover::getInstance(){
        if (instance == nullptr)
        {
            instance = new LeftFactoringRemover();
        }
        return instance;
}

