//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_READ_INPUT_H
#define JAVA_COMPILER_READ_INPUT_H

#include <string>
#include <vector>
#include "Construct_Automata.h"

using namespace std;
class Read_Input {
private:
    string filename;
public:
    Read_Input(string filename);
    bool read_file();
};


#endif //JAVA_COMPILER_READ_INPUT_H
