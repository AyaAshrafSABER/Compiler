//
// Created by sohayla on 20/03/19.
//

#include <cstring>
#include <sstream>
#include <algorithm>
#include "Tokenizing.h"
#include "../Automata/Helpers.h"
#include <bits/stdc++.h>
#include <bits/stdc++.h>


Tokenizing::Tokenizing() {
    Helpers * h  = Helpers::getInstance();
    helpers = h->getHelpers();

}


vector<string> Tokenizing::getTokens(string line, char del) {
    std::istringstream ss(line);
    std::string token;
  //  regex re("(<[=>]?|==|>=?|\\&\\&|\\|\\||!?=)");
    //smatch match;


    while(std::getline(ss, token, del)) {
   //     if (regex_search(token, match, re) == true) {
      //      tokens.push_back(token);
        //} else {
        if(token.find("-") != string::npos && token.length() == 1) {
            token = "\\-";
        } else  if(token.find("+") != string::npos && token.length() == 1) {
            token = "\\+";
        }
            this->parseString(token);
    }
      //  }

    return  tokens;
}
std::string to_hex(char ch) {
    std::ostringstream b;
    b << "\\x" << std::setfill('0') << std::setw(2) << std::setprecision(2)
      << std::hex << static_cast<unsigned int>(ch & 0xff);
    return b.str();
}


void Tokenizing::parseString(string str) {
    string temp;
    string build = "";
    for (int i = 0; i < str.length() ; ++i) {
        char c = static_cast<char>(str.at(i));
        if(!((c > 32) && (c < 127)))
            continue;
        if(iscntrl(c))
            continue;
        if(c == '+') {
            if(build == "\\"){
                build.clear();
            }
              temp = "\\+";
        } else if(c == '-'){
            if(build == "\\"){
                build.clear();
            }
                temp = "\\-";
        } else {
            temp = string(1, c);
        }
        if(build == "\\"){
            if(temp == "=") {
                tokens.push_back(temp);
            } else {
                tokens.push_back(build + temp);
            }
            build.clear();

        } else if (std::find(helpers.begin(), helpers.end(), temp) != helpers.end()) {
            if(build.length() > 0)
                tokens.push_back(build);
            tokens.push_back(temp);
            build.clear();
        } else if(temp == "\\"){
            if(build.length() > 0)
                tokens.push_back(build);
            build = temp;
        } else {
            build += temp;
        }
    }
    if(build.length() > 0) {
        tokens.push_back(build);
    }
}

void Tokenizing::splitByspaces(string line) {
    string s = "\\";
    string result = "";
    for (int i= 0; i < line.length(); i++) {
        char c = line.at(i);



    }

}
