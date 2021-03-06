//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_TOKENIZING_H
#define JAVA_COMPILER_TOKENIZING_H

#include <string>
#include <vector>
#include <list>

using namespace std;
class Tokenizing {
private:
    vector<string> tokens;
    vector<string> helpers;
    void parseString(string str);
public:
    Tokenizing();
    vector<string> getTokens(string line, char del);

    void splitByspaces(string line);
};


#endif //JAVA_COMPILER_TOCKENIZING_H
