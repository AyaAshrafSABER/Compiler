//
// Created by TARGET on 4/17/2019.
//

#include "CFG.h"

CFG::CFG()
{
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
