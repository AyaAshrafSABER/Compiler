//
// Created by Rowan on 20-Apr-19.
//

#ifndef COMPILER_OUTPUT_H
#define COMPILER_OUTPUT_H
#include <map>
#include <vector>
#include <stack>
#include <fstream>
#include "ParsingTable.h"
#include "CFG.h"
#include "Read_Input.h"

using namespace std;
class Output {
private:
    string startSymbol;
    vector<string> tokens;
    map<string, vector<vector<string>>> productions;
    map<string,map<string,int>> parsingTable;
    //set<string> nonTerminal;
    set<string> terminal;
    stack<string> parsingStack;
    ofstream outfile;
public:
    Output();
    void initialization();
    void tracing();
    void printStack();
    void error(string top, string token, int errorNum);
    bool isTerminal(string symbol);
    void readFile(string fileName);
    //bool inNonTerminal(string stackTop);
};


#endif //COMPILER_OUTPUT_H
