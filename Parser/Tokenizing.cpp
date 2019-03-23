//
// Created by sohayla on 20/03/19.
//

#include <cstring>
#include <sstream>
#include <algorithm>
#include "Tokenizing.h"
#include "../Automata/Helpers.h"

Tokenizing::Tokenizing() {
    Helpers * h  = Helpers::getInstance();
    helpers = h->getHelpers();

}

vector<string> Tokenizing::getTokens(string line, char del) {
    std::istringstream ss(line);
    std::string token;

    while(std::getline(ss, token, del)) {
        this->parseString(token);
    }
    return  tokens;
}

void Tokenizing::parseString(string str) {
    string temp;
    string build = "";
    for (int i = 0; i < str.length() ; ++i) {
        char c = str.at(i);
        if(c == '+') {
            temp = "\\+";
        } else {
            temp = string(1, c);
        }
        if (std::find(helpers.begin(), helpers.end(), temp) != helpers.end()) {
            if(build.length() > 0)
                tokens.push_back(build);
            tokens.push_back(temp);
            build.clear();
        } else {
            build += temp;
        }
    }
    if(build.length() > 0) {
        tokens.push_back(build);
    }
}
