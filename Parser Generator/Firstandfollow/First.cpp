//
// Created by sohayla on 19/04/19.
//

#include "First.h"

First::First() {
    //TODO initialize whatever comes from parser declare here.
}

vector<string> First::findFirst(string production) {
    //check if first in production is a terminal or eps, if yes insert into map and return.
    //if it's non-terminal -> recurse on it
    //if it contains eps and not last non_terminal, pop from production recurse on production
    //return vector
    return  vector<string>();


}

bool First::checkIfEpsOccurs(string non_t) {
    //check for eps
    return false;
}

void First::calculateFirst() {
    //call recurse on nonTerminal for each non_t in map if it's not visited


}

void First::recurseOnNonTerminal(string non_t) {
    //get its production vector
    //send each to findFirst
    //insert first(s) into the map and update index, get to next production
    //mark as visited

}
