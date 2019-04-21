//
// Created by AYA OSMAN on 4/17/2019.
//

#ifndef COMPILER_CFGPARSER_H
#define COMPILER_CFGPARSER_H

#include <string>
#include "CFG.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "../error/ErrorHandler.h"

#define START_GRAMMER "#"
#define ORING "|"
#define TERMINAL '\''
#define Euality "="

using namespace std;
class CFGParser {
private:
    string filename;
    CFG* grammer;
    set<string> nonTerminalOnRHS;

    bool read_file(CFG* grammer);
    vector <string> splitBySpaces(string line);
    string trim(string word);
    void throwError(string error);
    bool checkNonTerminal(set<string> tokens, CFG* cfg);
public:
    CFGParser(string filename);
};


#endif //COMPILER_CFGPARSER_H
