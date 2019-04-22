//
// Created by Rowan on 19-Apr-19.
//

#include "ParsingTable.h"
#include "TestFirstFollow.h"
#include <iostream>

static ParsingTable* instance;

ParsingTable::ParsingTable() {
    TestFirstFollow *test = TestFirstFollow::getInstance();
    Firstandfollow_tables* firstAndFollow = Firstandfollow_tables::getInstance();
    this->first = firstAndFollow->getFirst();
    this->follow = firstAndFollow->getFollow();
    //CFG* cfg;
    //cfg->getInstance();
    this->non_t_productions = test->getProduction();
    this->terminal = test->getTerminal();
    this->nonTerminal = test->getNonTerminal();
    createParsingTable();
}

ParsingTable *ParsingTable::getInstance() {
    if(instance == nullptr){
        instance = new ParsingTable();
    }
    return instance;
}

void ParsingTable::createParsingTable() {
    auto non_t_it = nonTerminal.begin();
    while (non_t_it != nonTerminal.end()){
        map<string,int> terminalMap;
        auto t_it = terminal.begin();
        while (t_it != terminal.end()) {
            terminalMap[*t_it] = ERROR;
            t_it++;
        }
        terminalMap["$"] = ERROR;
        vector<TableObject*> currentFirst = first[*non_t_it];
        bool containsEPS = false;
        int epsProduction;
        for (int j = 0; j < currentFirst.size(); ++j) {
            if (currentFirst[j]->getValue() != EPS) {
                containsEPS = false;
                if (terminalMap[currentFirst[j]->getValue()] == ERROR) {
                    terminalMap[currentFirst[j]->getValue()] = currentFirst[j]->getIndex();
                } else {
                    printError();
                }
            }
            else{
                containsEPS = true;
                epsProduction = currentFirst[j]->getIndex();
            }
        }
        vector<string> currentFollow = follow[*non_t_it];
        for (int k = 0; k < currentFollow.size(); ++k) {
            if (terminalMap[currentFollow[k]] == ERROR) {
                if (!containsEPS) {
                    terminalMap[currentFollow[k]] = SYNCH;
                }else{
                    terminalMap[currentFollow[k]] = epsProduction;
                }
            } else {
                printError();
            }
        }
        parsingTable[*non_t_it] = terminalMap;
        non_t_it++;
    }
    printTable();
}

void ParsingTable::printError() {
    cout << "There is ambiguity " << endl;
    exit(1);
}

map<string,map<string,int>> ParsingTable::getParsingTable() {
    return parsingTable;
}

void ParsingTable::printTable() {
    auto it = parsingTable.begin();
    while(it != parsingTable.end()){
        cout << "non Terminal -> " << (*it).first << " :\n";
        map<string,int> table = (*it).second;
        auto it1 = table.begin();
        while(it1 != table.end()){
            cout << "Terminal -> " << (*it1).first << " : " ;
            if((*it1).second >= 0) {
                vector<vector<string>> productions = non_t_productions[(*it).first];
                string production = vectorTostring(productions[(*it1).second]);
                cout << production << endl;
            }else if ((*it1).second == -1){
                cout << "Error" << endl;
            }
            else if ((*it1).second == -2){
                cout << "Synch" << endl;
            }
            it1++;
        }
        cout<< "________________________________________________________" << endl;
        it++;
    }
}

string ParsingTable::vectorTostring(vector<string> &vector) {
    std::string result;
    for (auto const& s : vector) { result += s; }
    return result;
}

vector<string> ParsingTable::getTokens() {
    return {"(", "id", "+", "(", "*", "id", ")"};
    //return {"*", "+", "id", ")", "+", "(", "id", "*"};
}