//
// Created by sohayla on 19/04/19.
//

#include <algorithm>
#include <iostream>
#include "First.h"

First::First() {
    cfg = CFG::getInstance();
    first_table = Firstandfollow_tables::getInstance();
    non_t_productions = cfg->getProduction();
    terminals = cfg->getTerminal();
    non_terminals = cfg->getNonTerminal();
    initializeFirstsMap();
    calculateFirst();
    testFirst();
}

void First::calculateFirst() {
    //call recurse on nonTerminal for each non_t in map if it's not visited
    auto it = non_t_productions.begin();
    // Iterate through the map on non visited non terminals
    while(it != non_t_productions.end()){
        // Push the key in given map
        if(find(visited.begin(), visited.end(), (*it).first) == visited.end())
            recurseOnNonTerminal((*it).first);

        it++;
    }
}

void First::recurseOnNonTerminal(string non_t) {
    //get its production vector
    vector<vector<string>> productions = non_t_productions[non_t];
    vector<string> result;
    //send each to findFirst
    vector<int> left_recursion;
    for (int i = 0; i < productions.size(); ++i) {
        vector<string> production = productions[i];
        if(production.empty())
            continue;
        if(production.front() == non_t) {
            left_recursion.push_back(i);
            continue;
        }
        vector<string> firsts = findFirst(production);
        //insert first(s) into the map and update index, get to next production
        insertFirstsIntoMap(non_t, i, firsts);
        result.insert(result.end(), firsts.begin(), firsts.end());
    }
    if(!left_recursion.empty()) {
        for (int i = 0; i < left_recursion.size(); ++i) {
            insertFirstsIntoMap(non_t, left_recursion[i], result);
        }
    }
    //mark as visited
    visited.push_back(non_t);
    firsts_of_non_terminal[non_t] = result;
}

vector<string> First::findFirst(vector<string> production) {
    vector<string> result;
    //check if first in production is a terminal or eps, if yes insert into map and return.
    if(production.front() == EPS) {
        result.push_back(EPS);
    } else if(find(terminals.begin(), terminals.end(), production.front()) != terminals.end()) {
        result.push_back(production.front());
        //if it's non-terminal -> recurse on it
    } else if (find(non_terminals.begin(), non_terminals.end(), production.front()) != non_terminals.end()) {
        if (find(visited.begin(), visited.end(), production.front()) == visited.end())
                recurseOnNonTerminal(production.front());
        result = firsts_of_non_terminal[production.front()];
    }
    //if it contains eps and not last non_terminal, pop from production recurse on production
    if(checkIfEpsOccurs(result) && production.size() > 1) {
        production.erase(production.begin());
         vector<string> additional_firsts = findFirst(production);
         result.insert(result.end(), additional_firsts.begin(), additional_firsts.end());
    }
    //return vector
    return  result;
}

bool First::checkIfEpsOccurs(vector<string>  firsts) {
    return find(firsts.begin(), firsts.end(), EPS) != firsts.end();
}

//////////////////////////////////////////////////////////Final Table Insertion////////////////////////////////////////
void First::insertFirstsIntoMap(string non_t, int index, vector<string> firsts) {
    for (const auto &first : firsts) {
        TableObject* object = new TableObject(index, first);
        first_table->insertInFirst(non_t, object);
    }
}

/////////////////////////////////Initialization////////////////////////////////////////////////
void First::initializeFirstsMap() {
    auto it = non_terminals.begin();
    while (it != non_terminals.end())
    {
        firsts_of_non_terminal.insert(pair<string, vector<string>>((*it), vector<string>()));
        it++;
    }
}
////////////////////////////////////testing///////////////////////////////////////////////////
void First::testFirst() {
    map<string, vector<TableObject*>> first = first_table->getFirst();
    auto it = first.begin();
    // Iterate through the map on non visited non terminals
    while(it != first.end()){
        // Push the key in given map
        cout << "Firsts Of non Terminal -> " << (*it).first << " :\n";
        vector<TableObject*> firsts = (*it).second;
        vector<vector<string>> productions = non_t_productions[(*it).first];
        for (int i = 0; i < firsts.size(); ++i) {
            TableObject* object = firsts[i];
            string production = vectorTostring(productions[object->getIndex()]);
            cout<<"From production -> " << production << " : " << object->getValue() << endl;
        }
        cout<< "________________________________________________________" << endl;
        it++;
    }
}

string First::vectorTostring(vector<string> &vector) {
    std::string result;
    for (auto const& s : vector) { result += s; }
    return result;
}
