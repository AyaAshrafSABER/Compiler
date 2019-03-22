//
// Created by sohayla on 20/03/19.
//

#include "Construct_Automata.h"

bool Construct_Automata::constructAutomata(string line) {
    Tokenizing tokeniser;
    vector<string> tokens = tokeniser.getTokens(line, ' ');
    char* type = const_cast<char *>(tokens[1].c_str());
    switch (type[1])  {
        case '=': { // definition
            return constructDefinition(tokens[0], line.substr(2));
        }
        case ':': {
            // part of the automata
            Graph *sub_g = constructGraph(tokens);
            sub_Automatas.push_back(sub_g);
            //construct new subgraph
            //add subgraph to map
            //return

            break;
        }
        default: {
            //switch check if valid input

            if (line.at(0) == '{') {
                //keywords
                //data types
            } else if (line.at(0) == '[') {
                //puncuation


            } else {
                return false;
            }


        }

    }

    return true;


}
Graph* Construct_Automata::constructGraph(vector<string> tokens) {

}
bool Construct_Automata::constructDefinition(string id, string definition) {


}
bool Construct_Automata::constructNFA() {}