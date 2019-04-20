//
// Created by sohayla on 19/04/19.
//

#include <algorithm>
#include "First.h"
#define  EPS "eps"
First::First() {
    cfg = CFG::getInstance();
    first_table = Firstandfollow_tables::getInstance();
    non_t_productions = cfg->getProduction();
    terminals = cfg->getTerminal();
    non_terminals = cfg->getNonTerminal();
    initializeFirstsMap();
    calculateFirst();
}

void First::calculateFirst() {
    //call recurse on nonTerminal for each non_t in map if it's not visited
    auto it = non_t_productions.begin();
    // Iterate through the map on non visited non terminals
    while(it != non_t_productions.end()){
        // Push the key in given map
        if(find(visited.begin(), visited.end(), it->first) == visited.end())
            recurseOnNonTerminal(it->first);

        it++;
    }
}

void First::recurseOnNonTerminal(string non_t) {
    //get its production vector
    vector<vector<string>> productions = non_t_productions[non_t];
    vector<string> result;
    //send each to findFirst
    for (int i = 0; i < productions.size(); ++i) {
        vector<string> production = productions[i];
        vector<string> firsts = findFirst(production);
        //insert first(s) into the map and update index, get to next production
        insertFirstsIntoMap(non_t, i, firsts);
        result.insert(result.end(), firsts.begin(), firsts.end());

    }
    //mark as visited
    visited.push_back(non_t);
    firsts_of_non_terminal.insert(pair<string, vector<string>>(non_t, result));
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


void First::insertFirstsIntoMap(string non_t, int index, vector<string> firsts) {
    for (const auto &first : firsts) {
        TableObject* object = new TableObject(index, first);
        first_table->insertInFirst(non_t, object);
    }
}

bool First::checkIfEpsOccurs(vector<string>  firsts) {
    return find(firsts.begin(), firsts.end(), EPS) != firsts.end();
}

void First::initializeFirstsMap() {
    auto it = non_terminals.begin();
    while (it != non_terminals.end())
    {
        firsts_of_non_terminal.insert(pair<string, vector<string>>((*it), vector<string>()));
        it++;
    }
}
