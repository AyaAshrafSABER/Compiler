//
// Created by AYA OSMAN on 4/17/2019.
//

#include "CFGParser.h"


//Constructor
CFGParser::CFGParser(string filename){
    this->filename = filename;
    this->read_file(this->grammer);
    this->checkNonTerminal(this->nonTerminalOnRHS, this->grammer);
    LeftFactoringRemover* lfr = LeftFactoringRemover::getInstance();
    this->grammer->printProduction();

}

//handle starting with # or |
bool CFGParser::read_file(CFG* grammer) {

    ifstream infile(this->filename);
    string line;
    vector<string> words;
    int counter = 0;
    grammer = CFG::getInstance();

    if (infile.is_open()) {
        vector<vector<string>> currPro;
        vector<string> currRule;
        string currTerminal;
        while (getline(infile, line)) {
            if (line.length() == 0 || line == " ")
                continue;
            words = splitBySpaces(line);
            if (counter == 0) {
                if (words[0] == START_GRAMMER) {
                    grammer->setStartSymbol(words[1]);
                    grammer->insetNonTerminal(words[1]);
                } else {
                    throwError(ErrorHandler::errors[ErrorHandler::NotCompleteGrammer]);
                }
                counter++;
            }
            if (words[0] == START_GRAMMER) {
                vector<vector<string>> nextPro;
                for (int i = 0; i < currPro.size(); i++) {
                    nextPro.push_back(currPro.at(i));
                }
                if (currTerminal != "") {
                    grammer->insetRule(currTerminal, nextPro);
                    grammer->insetNonTerminal(currTerminal);
                    currPro.clear();
                    currRule.clear();
                }
                currTerminal = words[1];
                if (words[2] == Euality) {
                    for (int i = 3; i < words.size(); i++) {
                        if (words[i] == ORING) {
                            vector<string> nextRule;
                            for (int i = 0; i < currRule.size(); i++) {
                                nextRule.push_back(currRule.at(i));
                            }
                            currPro.push_back(nextRule);
                            currRule.clear();
                        } else if (words[i].at(0) == TERMINAL && words[i].at(words[i].size() - 1) == TERMINAL) {
                            string temp = trim(words[i]);
                            grammer->insertTerminal(temp);
                            currRule.push_back(temp);

                        } else if (words[i].at(0) != TERMINAL && words[i].at(words[i].size() - 1) != TERMINAL) {
                            CFGParser::nonTerminalOnRHS.insert(words[i]); // to be check if it terminal
                            currRule.push_back(words[i]);

                        } else {
                            throwError(ErrorHandler::errors[ErrorHandler::NotCompleteGrammer]);
                        }
                    }
                    vector<string> nextRule;
                    for (int i = 0; i < currRule.size(); i++) {
                        nextRule.push_back(currRule.at(i));
                    }
                    currPro.push_back(nextRule);
                    currRule.clear();
                } else {
                    throwError(ErrorHandler::errors[ErrorHandler::NotCompleteGrammer]);
                }

            } else if (words[0] == ORING) {
                vector<string> nextRule;
                for (int i = 0; i < currRule.size(); i++) {
                    nextRule.push_back(currRule.at(i));
                }
                if (!nextRule.empty()) {
                    currPro.push_back(nextRule);
                    currRule.clear();
                }
                for (int i = 1; i < words.size(); i++) {
                    if (words[i] == ORING && i != 1) {
                        vector<string> nextRule;
                        for (int i = 0; i < currRule.size(); i++) {
                            nextRule.push_back(currRule.at(i));
                        }
                        currPro.push_back(nextRule);
                        currRule.clear();
                    } else  if (words[i].at(0) == TERMINAL && words[i].at(words[i].size() - 1) == TERMINAL) {
                        string temp = trim(words[i]);
                        grammer->insertTerminal(temp);
                        currRule.push_back(temp);

                    } else if (words[i].at(0) != TERMINAL && words[i].at(words[i].size() - 1) != TERMINAL) {
                        CFGParser::nonTerminalOnRHS.insert(words[i]); // to be check if it terminal
                        currRule.push_back(words[i]);

                    } else {
                        throwError(ErrorHandler::errors[ErrorHandler::NotCompleteGrammer]);
                    }
                }
                for (int i = 0; i < currRule.size(); i++) {
                    nextRule.push_back(currRule.at(i));
                }
                currPro.push_back(nextRule);
                currRule.clear();
            }else  {
                throwError(ErrorHandler::errors[ErrorHandler::NotCompleteGrammer]);
        }

    }
        if (!(currRule.empty())){
            currPro.push_back(currRule);
        }
        grammer->insetRule(currTerminal, currPro);
        grammer->insetNonTerminal(currTerminal);

    return true;

    } else {
        cout<<"error"<<endl;
        return false;
    }
}

vector <string> CFGParser::splitBySpaces(string line){
    vector<string> arr;
    stringstream ssin(line);
    string str;
    while(ssin >> str) {
        arr.push_back(str);
    }
    return arr;
}

string CFGParser::trim(string word) {
    return word.substr(1, word.size() - 2);
}

void CFGParser::throwError(string error) {
    cout <<error<<endl;
    exit(0);
}

bool CFGParser::checkNonTerminal(set<string> tokens, CFG *cfg) {
    for (auto s :tokens) {
       bool t = cfg->getInstance()->IsNonTerminal(s);
       if (!t) throwError(ErrorHandler::errors[ErrorHandler::NotNonTerminal]);
    }
    return true;
}


