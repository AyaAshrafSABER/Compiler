//
// Created by RowanAdel on 07-Apr-19.
//

#ifndef COMPILER_READPROGRAM_H
#define COMPILER_READPROGRAM_H

#include <string.h>

#include "Definition.h"
#include "Node.h"
#include "../dfa-minimizer/DFAMinimizer.h"


using namespace std;
class ReadProgram {
private:
    string filename;
    vector<pair<Node*, map<Definition*, Node*>>>* transition_table;
    DFAMinimizer * dfa;
    vector<string> tokens;

public:
    struct state {
        int vec_ind = 0;
        int ch_ind = 0;
        string token = "";
    };
    ReadProgram();
    void readFile();
    Node* getNextState(Node* nextState, char input);
    void writeOutputFile();
    state getNextToken(vector<string> line, int v_ind, int ch_ind);
    vector <string> splitBySpaces(string line);

};


#endif //COMPILER_READPROGRAM_H
