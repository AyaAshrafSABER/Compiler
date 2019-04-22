//
// Created by saraheldafrawy on 22/04/19.
//

#include "TestFirstFollow.h"

TestFirstFollow* TestFirstFollow::instance;

TestFirstFollow* TestFirstFollow::getInstance() {
    if (instance == nullptr) {
        instance = new TestFirstFollow();
    }
    return instance;
}

TestFirstFollow::TestFirstFollow() {
    startSymbol = "E";
    non_terminals = {"E", "E'", "T", "T'", "F"};
    terminals = {"+", "*", "(", ")", "id"};
    non_t_productions = {
            {"E",  {{"T", "E'"}}},
            {"E'", {{"+", "T", "E'"}, {"eps"}}},
            {"T",  {{"F", "T'"}}},
            {"T'", {{"*", "F", "T'"}, {"eps"}}},
            {"F",  {{"(", "E", ")"}, {"id"}}}
            };
}

string TestFirstFollow:: getStartSymbol() {
    return startSymbol;
}

map<string, vector<vector<string>>> TestFirstFollow:: getProduction() {
    return non_t_productions;
};
set<string> TestFirstFollow:: getTerminal() {
    return terminals;
}
set<string> TestFirstFollow:: getNonTerminal() {
    return non_terminals;
}