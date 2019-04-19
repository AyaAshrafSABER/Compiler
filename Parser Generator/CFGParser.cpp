//
// Created by TARGET on 4/17/2019.
//

#include "CFGParser.h"
//Constructor
CFGParser::CFGParser(string filename){
    this->filename = filename;
}
bool CFGParser::read_file() {
    ifstream infile(filename);
    string line;
    this->grammer = CFG::getInstance();
    if(infile.is_open()) {
        while (getline(infile, line)) {
            if(line.length() == 0 || line == " ")
                continue;
            //todo implement parser;
        }
        return true;
    } else {
        return false;
    }
}
