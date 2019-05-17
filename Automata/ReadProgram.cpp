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
    for (int i = 0; i < tokens.size(); i++) {
        if(tokens[i].at(0) == '\\' && tokens[i].size() > 1)
            tokens[i] = tokens[i].at(1);
       // cout << tokens[i] << endl;
        outfile << tokens[i] << endl;
    }
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
                Node *lastAcc = NULL;
                int lastInd = -1;
                int startInd = 0;
                for (int j = 0; j < lineTokens[i].length(); j++) {

                    nextState = getNextState(nextState, lineTokens[i].at(j));
                    if(lineTokens[i] == " ") {
                        continue;
                    }
                    if (nextState != NULL && nextState->getStatus() != N_ACC){
                        lastAcc = nextState;
                        lastInd = j;
                    }
                    if ((nextState == NULL)
                        || (j == lineTokens[i].length() - 1 && nextState->getStatus() == N_ACC)) {
                        if (lastInd > -1 && lastAcc != nullptr){
                            tokens.push_back(lastAcc->getStatus());
                            cout<<lastAcc->getStatus()<<endl;
                            lastAcc = NULL;
                            startInd = lastInd;
                            j = lastInd;
                            lastInd = -1;
                        }
                        else {
                            tokens.push_back("Not Matched");
                            cout<<"Not Matched"<<endl;

                            if (startInd != 0) {
                                j = startInd + 1;
                                lastInd = j;
                            }
                        }
                        nextState = dfa->getStartState();
                    }
                    else if (j == lineTokens[i].length() - 1 && nextState->getStatus() != N_ACC){
                        tokens.push_back(nextState->getStatus());
                        cout<<lastAcc->getStatus()<<endl;
                    }
                }
            }
           // tokens.push_back("$");
        }
    }
    writeOutputFile();
}

Node* ReadProgram::getNextState(Node* currentState, char inputChar) {
    string input = string(1, inputChar);
    map <Definition*, Node*> transitions;
    vector<pair<Node*, map<Definition*, Node*>>>::iterator it;
    for (it = (*transition_table).begin() ; it != (*transition_table).end(); ++it) {
        if((*it).first == currentState) {
            transitions = (*it).second;
        }
    }
    for (map<Definition*, Node*>::iterator it = transitions.begin(); it != transitions.end(); ++it) {
        if ((*it).first->contains(input)) {
            return (*it).second;
        }
    }
    return NULL;
}

vector<string> ReadProgram::getTokens() {
    return tokens;
}
