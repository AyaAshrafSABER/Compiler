//
// Created by AyaOsman on 4/17/2019.
//

#include "LeftRecursionRemover.h"
LeftRecursionRemover* LeftRecursionRemover::instance;

LeftRecursionRemover::LeftRecursionRemover() {
    this->cfg = CFG::getInstance();
    this->findLeftRecursion();
}

void LeftRecursionRemover::findLeftRecursion() {
    map<string,vector<vector<string>>> rules = cfg->getProduction();

    map<string,vector<vector<string>>> nextRules;
    int id = 0;

    for(auto rule: rules) {
        bool leftRecursive = false;
        string n_T = rule.first;
        vector<vector<string>> newRule;
        vector<vector<string>> alpha;
        vector<vector<string>> beta;
        set<string> nonTerminalWithLF;
        /*iterating over productions for certain non terminal*/
        for (int i = 0; i < rule.second.size(); i++) {

            string firstSymbol = rule.second[i][0];
            std::set<string>::iterator ret;

            ret = cfg->getNonTerminal().find(firstSymbol) ;

            if (ret != cfg->getNonTerminal().end()){ // begin is non terminal

                auto nextRule = nextRules.find(firstSymbol);
                auto LF = nonTerminalWithLF.find(firstSymbol);
                if (nextRule != nextRules.end() && LF != nonTerminalWithLF.end()){
                    substituteNonterminalInProductions(&newRule,rule.second[i] ,nextRule->second);
                } else {
                    newRule.push_back(rule.second[i]);
                }
            }

            else {
                newRule.push_back(rule.second[i]);
            }
        }
        leftRecursive = checkLeftRecursion(&alpha,&beta,n_T, newRule);
        if (leftRecursive){
            string newNonTerminal = renamingNonTerminal(n_T, id);
            cfg->insetNonTerminal(newNonTerminal);
            for(auto &b : beta){
                b.push_back(newNonTerminal);
            }
            for(auto &a: alpha){
                a.push_back(newNonTerminal);
            }
            vector<string> temp;
            temp.push_back(EPSILON);
            alpha.push_back(temp);
             nextRules.insert(pair<string,vector<vector<string>>> (n_T,beta));
            nextRules.insert(pair<string,vector<vector<string>>> (newNonTerminal,alpha));
            id ++;
            nonTerminalWithLF.insert(n_T);
        }else {
            nextRules.insert(pair<string,vector<vector<string>>> (n_T,newRule));
        }

    }
    cfg->setProduction(nextRules);

}
void LeftRecursionRemover::substituteNonterminalInProductions(vector<vector<string>> *newProduction, vector<string> currProsuction,vector<vector<string>> nextProductions) {
//concatination
    for (int i = 0; i < nextProductions.size() ; i++) {
        vector<string> temp;
        for (int j = 0; j < nextProductions[i].size(); j++){
            temp.push_back(nextProductions[i][j]);
        }
        for (int j = 1; j < currProsuction.size(); j++){
            temp.push_back(currProsuction[j]);
        }
        newProduction->push_back(temp);
    }

}

    bool LeftRecursionRemover::checkLeftRecursion(vector<vector<string>> *alpha, vector<vector<string>> *beta,string key, vector<vector<string>> prodctions) {
    bool isLeftRec = false;
    for(int i = 0; i < prodctions.size(); i++) {
        if(key == prodctions[i][0]) {
            isLeftRec = true;
            vector<string> temp;
            for (int j = 1; j < prodctions[i].size() ; j++) {
                temp.push_back(prodctions[i][j]);
            }
            alpha->push_back(temp);
        }else {
            beta->push_back(prodctions[i]);
        }
    }
    return isLeftRec;
}




string LeftRecursionRemover::renamingNonTerminal(string nonTerminal,int id) {
    return nonTerminal + to_string(id);
}


LeftRecursionRemover* LeftRecursionRemover::getInstance(){
    if (instance == nullptr)
    {
        instance = new LeftRecursionRemover();
    }
    return instance;
}

