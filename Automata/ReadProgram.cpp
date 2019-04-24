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

ReadProgram::ReadProgram () {
    this->filename = filename;
    this->dfa = DFAMinimizer::getInstance();
    this->transition_table = dfa->getMinimizedDFA();
    //readFile();
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
    ofstream outfile;
    outfile.open("tokens.txt");
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (line.length() == 0 || line == " ")
                continue;

            lineTokens = splitBySpaces(line);
            state token;
            while (token.vec_ind < lineTokens.size()){
                token = getNextToken(lineTokens, token.vec_ind, token.ch_ind);
                outfile << token.token << endl;
            }
            /*for (int i = 0; i < lineTokens.size(); i++) {
                Node *nextState = dfa->getStartState();
                Node *lastAcc = NULL;
                int lastInd = -1;
                int startInd = 0;
                for (int j = 0; j < lineTokens[i].length(); j++) {
                    if(lineTokens[i] == " ") {
                        continue;
                    }
                    //get nextState
                    nextState = getNextState(nextState, lineTokens[i].at(j));
                    //If there exist next state and it's acceptance
                    if (nextState != NULL && nextState->getStatus() != N_ACC){
                        lastAcc = nextState;
                        lastInd = j;
                    }
                    //If no next state or, last token and not accepted yet
                    if ((nextState == NULL)
                        || (j == lineTokens[i].length() - 1 && nextState->getStatus() == N_ACC)) {
                        //push last accepted, start from last index again
                        if (lastInd > -1 && lastAcc != nullptr){
                            tokens.push_back(lastAcc->getStatus());
                            cout<<lastAcc->getStatus()<<endl;
                            lastAcc = NULL;
                            startInd = lastInd;
                            j = lastInd;
                            lastInd = -1;
                        }
                        else {
                            //didn't match anything
                            tokens.push_back("Not Matched");
                            cout<<"Not Matched"<<endl;
                            //ignore and go to next
                            if (startInd != 0) {
                                j = startInd + 1;
                                lastInd = j;
                            }
                        }
                        //continue from next state
                        nextState = dfa->getStartState();
                    }
                    //if last index and it's accepted
                    else if (j == lineTokens[i].length() - 1 && nextState->getStatus() != N_ACC){
                        tokens.push_back(nextState->getStatus());
                        cout<<lastAcc->getStatus()<<endl;
                    }
                }
            }*/
        }
        outfile.close();

    }
    infile.close();
   // writeOutputFile();
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

ReadProgram::state ReadProgram::getNextToken(vector<string> lineTokens, int v_ind, int ch_ind) {
    state result;
    for (int i = v_ind; i < lineTokens.size() ; ++i) {
        Node *nextState = dfa->getStartState();
        Node *lastAcc = NULL;
        int lastInd = -1;
        int startInd = 0;
        if(i == v_ind)
            startInd = ch_ind;
            for (int j = startInd; j < lineTokens[i].length(); j++) {
                if(lineTokens[i] == " ") {
                    continue;
                }
                //get nextState
                nextState = getNextState(nextState, lineTokens[i].at(j));
                //If there exist next state and it's acceptance
                if (nextState != NULL && nextState->getStatus() != N_ACC){
                    lastAcc = nextState;
                    lastInd = j;
                }
                //If no next state or, last token and not accepted yet
                if ((nextState == NULL)
                    || (j == lineTokens[i].length() - 1 && nextState->getStatus() == N_ACC)) {
                    //push last accepted, start from last index again
                    if (lastInd > -1 && lastAcc != nullptr){
                        result.ch_ind = lastInd+1;
                        result.vec_ind = i;
                        result.token = lastAcc->getStatus();
                      /*  tokens.push_back(lastAcc->getStatus());
                        cout<<lastAcc->getStatus()<<endl;
                        lastAcc = NULL;
                        startInd = lastInd;
                        j = lastInd;
                        lastInd = -1;*/
                        return result;
                    }
                    else {
                        //didn't match anything
                       // tokens.push_back("Not Matched");
                        cout<<"Not Matched"<<endl;
                        result.ch_ind = startInd + 1;
                        result.vec_ind = i;
                        result.token = "Not Matched";
                        //ignore and go to next
                      /*  if (startInd != 0) {
                            j = startInd + 1;
                            lastInd = j;
                        }*/
                        return result;
                    }
                }
                    //if last index and it's accepted
                else if (j == lineTokens[i].length() - 1 && nextState->getStatus() != N_ACC){
                  /*  tokens.push_back(nextState->getStatus());
                    cout<<lastAcc->getStatus()<<endl;*/
                    result.ch_ind = 0;
                    result.vec_ind = i+1;
                    result.token = nextState->getStatus();
                    return result;

                }
            }



    }
    return result;
}

