//
// Created by sohayla on 19/04/19.
//

#include "Firstandfollow_tables.h"
static Firstandfollow_tables* instance;
Firstandfollow_tables::Firstandfollow_tables() {
    CFG * cfg = CFG::getInstance();
    non_terminals = cfg->getNonTerminal();
    initializeMap();

}

Firstandfollow_tables *Firstandfollow_tables::getInstance() {
    if(instance == nullptr){
        instance = new Firstandfollow_tables();
    }
    return instance;
}

void Firstandfollow_tables::insertInFirst(string non_t, TableObject *object) {
    this->first[non_t].push_back(object);
}

void Firstandfollow_tables::insertInFollow(string non_t, TableObject *object) {
    this->follow[non_t].push_back(object);

}

map<string, vector<TableObject*>> Firstandfollow_tables::getFollow() {
    return this->follow;
}

map<string, vector<TableObject*>> Firstandfollow_tables::getFirst() {
    return this->first;
}

void Firstandfollow_tables::initializeMap() {
    auto it = non_terminals.begin();
    while (it != non_terminals.end())
    {
        first.insert(pair<string, vector<TableObject*>>((*it), vector<TableObject*>()));
        follow.insert(pair<string, vector<TableObject*>>((*it), vector<TableObject*>()));
        it++;
    }

}
