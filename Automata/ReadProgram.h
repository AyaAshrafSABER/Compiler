//
// Created by RowanAdel on 07-Apr-19.
//

#ifndef COMPILER_READPROGRAM_H
#define COMPILER_READPROGRAM_H

#include <string.h>

#include "Definition.h"
#include "Node.h"
#include "DFAMinimizer.h"


using namespace std;
class ReadProgram {
private:
    string filename;
    vector<pair<Node*, map<Definition*, Node*>>>* transition_table;
    DFAMinimizer * dfa;
    vector<string> tokens;
    vector <string> splitBySpaces(string line);
public:
    ReadProgram(string filename);
    void readFile();
    Node* getNextState(Node* nextState, char input);
    void writeOutputFile();
};


#endif //COMPILER_READPROGRAM_H
