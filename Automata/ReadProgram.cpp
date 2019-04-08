//
// Created by RowanAdel on 07-Apr-19.
//
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include "ReadProgram.h"

ReadProgram::ReadProgram (string filename) {
    this->filename = filename;
    this->dfa = DFAMinimizer::getInstance();
    this->transition_table = dfa->getMinimizedDFA();
    readFile();
}

vector <string> ReadProgram::splitBySpaces(string line) {
    vector<string> arr;
    int i = 0;
    stringstream ssin(line);
    string str;
    while(ssin >> str) {
        arr.push_back(str);
    }
    return arr;
}

void ReadProgram::writeOutputFile() {
    //TODO flush file
    ofstream outfile;
    outfile.open("tokens.txt");
    for (int i = 0; i < tokens.size(); i++)
        outfile << tokens[i] << endl;
    outfile.close();
}

void ReadProgram::readFile() {
    ifstream infile(filename);
    string line;
    vector <string> lineTokens;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (line.length() == 0 || line == " ")
                continue;
            lineTokens = splitBySpaces(line);
            for (int i = 0; i < lineTokens.size(); i++) {
                Node *nextState = dfa->getStartState();
                Node *lastAcc = nullptr;
                int lastInd = -1;
                for (int j = 0; j < lineTokens[i].length(); j++) {
                    nextState = getNextState(nextState, lineTokens[i].at(j));
                    if(lineTokens[i] == "") {
                        continue;
                    }
                    if (nextState != nullptr && nextState->getStatus() != N_ACC){
                        lastAcc = nextState;
                        lastInd = j;
                    }
                    if ((nextState == nullptr)
                        || (j == lineTokens[i].length() - 1 && nextState->getStatus() == N_ACC)) {
                        if (lastInd > -1){
                            tokens.push_back(lastAcc->getStatus());
                            lastAcc = nullptr;
                            j = lastInd - 1;
                        }
                        else {
                            tokens.push_back("Not Matched");
                        }
                        nextState = dfa->getStartState();
                    }
                }
                tokens.push_back(nextState->getStatus());
            }
        }
    }
    writeOutputFile();
}

Node* ReadProgram::getNextState(Node* currentState, char inputChar) {
    map <Definition*, Node*> transitions;
    vector<pair<Node*, map<Definition*, Node*>>>::iterator it;
    for (it = (*transition_table).begin() ; it != (*transition_table).end(); ++it) {
        if((*it).first == currentState) {
            transitions = (*it).second;
        }
    }
    for (map<Definition*, Node*>::iterator it = transitions.begin(); it != transitions.end(); ++it) {
        if ((*it).first->contains(inputChar)) {
            return (*it).second;
        }
    }
    return nullptr;
}
