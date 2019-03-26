//
// Created by sohayla on 20/03/19.
//

#include <fstream>
#include <sstream>
#include "Read_Input.h"
//Constructor
Read_Input::Read_Input(string filename) {
    this->filename = filename;
}

//Reading Language Description.
bool Read_Input::read_file() {
    ifstream infile(filename);
    string line;
    Construct_Automata automata_c;
    vector<string> lineTokens;
    if(infile.is_open()) {
        while (getline(infile, line)) {
            automata_c.constructAutomata(line);
        }
        automata_c.constructNFA();
    return true;
    } else {
        return false;
    }


}

