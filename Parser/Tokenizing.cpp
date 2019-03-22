//
// Created by sohayla on 20/03/19.
//

#include <cstring>
#include <sstream>
#include "Tokenizing.h"


vector<string> Tokenizing::getTokens(string line, char del) {
    vector<string> tokens;
    std::istringstream ss(line);
    std::string token;

    while(std::getline(ss, token, del)) {
        tokens.push_back(token);
    }
    return  tokens;
}
