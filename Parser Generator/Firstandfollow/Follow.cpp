//
// Created by sohayla on 19/04/19.
//

#include <iostream>
#include "Follow.h"
#include "First.h"
#include "TestFirstFollow.h"

Follow::Follow() {
    cfg = CFG::getInstance();
   // cfg = TestFirstFollow::getInstance();
    firstandfollow_tables = Firstandfollow_tables::getInstance();
    non_t_productions = cfg->getProduction();
    firsts = firstandfollow_tables->getFirst();
    non_terminals = cfg->getNonTerminal();
    initializeFollowsMap();
    insertDollarSign();
    loopNonTerminal();
    firstandfollow_tables->setFollowTable(follows_of_non_terminal);
    testOutput();
}

//for each nonterminal check if it exists in production
//if its true
//1st->if what's next terminal add it
//2nd->if what's next is nth get follow the (non terminal producer) --> recursion
//3rd->if what's next is non terminal gets it's firsts
void Follow::loopNonTerminal(){
    auto itNonTerminal = non_terminals.begin();
    while (itNonTerminal != non_terminals.end()) {
        findFollowsInNonTerminal((*itNonTerminal));
        itNonTerminal++;
    }
}

void Follow::findFollowsInNonTerminal(string nonTerminal) {
    if(visited.find(nonTerminal) == visited.end()) {
        visited.insert(make_pair(nonTerminal, nonTerminal));
        auto it = non_t_productions.begin();
        while (it != non_t_productions.end()) {
            for (int i = 0; i < (*it).second.size(); i++) {
                findFollowInProduction((*it).second[i], nonTerminal, (*it).first);
            }
            it++;
        }
    }
}
//TODO Done
void Follow::initializeFollowsMap() {
    auto it = non_terminals.begin();
    while (it != non_terminals.end()) {
        follows_of_non_terminal.insert(pair<string, vector<string>>((*it), vector<string>()));
        it++;
    }
}

void Follow::findFollowInProduction(vector<string> &vector, string nonTerminal, string leftNonTerminal) {
    for(int i = 0; i < vector.size(); i++) {
        if(vector[i] == nonTerminal) {
            if((i+1) == vector.size()) {
                //2nd case
                insertFollowLeftNonTerminal (leftNonTerminal, nonTerminal);
            } else if (non_terminals.find(vector[i+1]) != non_terminals.end()) {
                //next is non terminal
                //3rd case
                insertFirstInFollow(vector[i+1], nonTerminal);
                int j = i + 1;
                while (j < vector.size() && containsEps(vector[j])) {
                    if (j+1 < vector.size()) {
                        insertFirstInFollow(vector[j + 1], nonTerminal);
                    } else {
                        insertFollowLeftNonTerminal (leftNonTerminal, nonTerminal);
                    }
                    j++;
                }
            } else {
                //terminal
                //1st case
                insertFollow(nonTerminal, vector[i+1]);
            }
        }
    }
}
//TODO Done
void Follow::insertFollow (string nonTerminal, string terminal) {
    if (!checkIfExists(nonTerminal, terminal)) {
        follows_of_non_terminal.at(nonTerminal).push_back(terminal);
    }
}
//TODO Done
bool Follow::checkIfExists(string nonterminal, string terminal) {
    vector<string> vector = follows_of_non_terminal.at(nonterminal);
    for(int i = 0; i < vector.size(); i++) {
        if(vector[i] == terminal) {
            return true;
        }
    }
    return false;
}
//TODO Done
void Follow::insertDollarSign() {
    string startSymbol = cfg->getStartSymbol();
    follows_of_non_terminal.at(startSymbol).push_back("$");
}

void Follow::insertFirstInFollow(string vector, string nonTerminal) {
    std::vector<TableObject*> firstOfNext = firsts.at(vector);
    for (int i = 0; i < firstOfNext.size(); i++) {
        if ((*firstOfNext[i]).getValue() == EPS)
            continue;
        insertFollow(nonTerminal, (*firstOfNext[i]).getValue());
    }
}

bool Follow::containsEps(string nonTerminal) {
    std::vector<TableObject*> firstOfNext = firsts.at(nonTerminal);
    for (int i = 0; i < firstOfNext.size(); i++) {
        if((*firstOfNext[i]).getValue() == EPS) {
            return true;
        }
    }
    return false;
}

void Follow::insertFollowLeftNonTerminal (string leftNonTerminal, string nonTerminal) {
    findFollowsInNonTerminal(leftNonTerminal);
    std::vector<string> follows = follows_of_non_terminal.at(leftNonTerminal);
    for (int i = 0; i < follows.size(); i++) {
        insertFollow(nonTerminal, follows[i]);
    }
}

void Follow::testOutput () {

    map<string, vector<string>> follow = firstandfollow_tables->getFollow();
    auto it = follow.begin();
    cout <<endl<< "Follows"<< endl;
    while(it != follow.end()){
        // Push the key in given map
        cout <<(*it).first << " -> { ";
        vector<string> follows = (*it).second;
        for (int i = 0; i < follows.size(); ++i) {
            cout<< follows[i] << " ";
        }
        cout<< " }" << endl;
        it++;
    }
    cout<<"__________________________________________"<<endl;
}

