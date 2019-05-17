//
// Created by AYA OSMAN on 4/17/2019.
//

#include "CFG.h"

CFG* CFG::instance;

CFG::CFG()
{
}
CFG* CFG::getInstance()
{
    if (instance == nullptr)
    {
        instance = new CFG();
    }
    return instance;
}

const set <string> &CFG::getNonTerminal() const {
    return nonTerminal;
}

void CFG::setNonTerminal(const set <string> &nonTerminal) {
    CFG::nonTerminal = nonTerminal;
}

const set <string> &CFG::getTerminal() const {
    return terminal;
}

void CFG::setTerminal(const set <string> &terminal) {
    CFG::terminal = terminal;
}

const string &CFG::getStartSymbol() const {
    return startSymbol;
}

void CFG::setStartSymbol(const string &startSymbol) {
    CFG::startSymbol = startSymbol;
}

const map<string, vector<vector<string>>> &CFG::getProduction() const {
    return production;
}

void CFG::setProduction(const map<string, vector<vector<string>>> &production) {
    CFG::production = production;
}

void CFG::insetRule(string key, vector<vector<string>> productions){
    CFG::production.insert(pair<string,vector<vector<string>>>(key,productions));
}

void CFG::insertTerminal(string terminal){
    CFG::terminal.insert(terminal);

}

void CFG::insetNonTerminal(string nonTerminal){
    CFG::nonTerminal.insert(nonTerminal);
}

bool CFG::IsNonTerminal(string word){
    auto it1 = CFG::nonTerminal.find(word);
    return it1 != CFG::nonTerminal.end() ? true : false;
}

void CFG::printProduction(){
    map<string, vector<vector<string>>> production = CFG::getInstance()->getProduction();
    int counter = 0;
    for(auto it = production.begin(); it != production.end(); ++it)
    {
        cout << counter <<" "<<it->first << " ->" << endl;
        for(int i = 0; i < it->second.size(); i++){

            for(int j = 0 ; j <  it->second[i].size();j++ ) {
                cout << it->second[i][j]<<"  ";
            }
            cout<<endl;
        }
        cout<<"__________________________________________"<<endl;
        counter++;
    }
}