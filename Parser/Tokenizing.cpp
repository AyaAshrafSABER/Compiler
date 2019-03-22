//
// Created by sohayla on 20/03/19.
//

#include <cstring>
#include <sstream>
#include "Tokenizing.h"


vector<string> Tokenizing::getTokens(string line, string del) {
    vector<string> tokens;
    std::size_t prev = 0, pos;
    while ((pos = line.find_first_of(del, prev)) != std::string::npos)
    {
        if (pos > prev)
            tokens.push_back(line.substr(prev, pos-prev));
        prev = pos+1;
    }
    if (prev < line.length())
        tokens.push_back(line.substr(prev, std::string::npos));
    return  tokens;
}
