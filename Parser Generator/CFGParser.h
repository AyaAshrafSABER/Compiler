//
// Created by TARGET on 4/17/2019.
//

#ifndef COMPILER_CFGPARSER_H
#define COMPILER_CFGPARSER_H

#include <string>
#include "CFG.h"
#include <fstream>
#include <sstream>
using namespace std;
class CFGParser {
private:
    string filename;
    CFG* grammer;
    bool read_file();
public:
    CFGParser(string filename);
};


#endif //COMPILER_CFGPARSER_H
