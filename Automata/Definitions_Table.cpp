//
// Created by sohayla on 24/03/19.
//

#include "Definitions_Table.h"
static Definitions_Table* instance;

Definitions_Table::Definitions_Table() {
    Graph* g = new Graph();
    Node* n = new Node(0);
    g->setStart(n);
    g->setEnd(n);
    g->getStartState()->setStatus("eps");
    this->insertInMap("EPS", new Definition(g));
}
Definitions_Table* Definitions_Table::getInstance() {
    if(instance == NULL) {
        instance = new Definitions_Table();
    }
    return instance;
}

void Definitions_Table::insertInMap(string id, Definition *definition) {
    this->definitions.insert(pair<string, Definition*>(id, definition));
}

Definition* Definitions_Table::getDefinitions(string id) {
    if(definitions.count(id))
        return definitions[id];
    return NULL;
}

map<string, Definition*> Definitions_Table::getTable() {
    return this->definitions;
}