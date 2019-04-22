//
// Created by Rowan on 20-Apr-19.
//

#include "Output.h"
#include "TestFirstFollow.h"
#include <iostream>
#include <ReadProgram.h>

Output::Output() {
    TestFirstFollow* cfg = TestFirstFollow::getInstance();
    this->productions = cfg->getProduction();
    this->terminal = cfg->getTerminal();
    //this->nonTerminal = cfg->getNonTerminal();
    this->startSymbol = cfg->getStartSymbol();
    ParsingTable* table = ParsingTable::getInstance();
    this->parsingTable = table->getParsingTable();
    //ReadProgram *prog;
    //prog->getInstance("C:\\Users\\Adel\\CLionProjects\\Compiler\\Test\\Program");
    //this->tokens = prog->getTokens();
    this->tokens = table->getTokens();
    outfile.open("ParserOutput.txt");
    initialization();
}

void Output::initialization() {
    parsingStack.push("$");
    parsingStack.push(startSymbol);
    tokens.push_back("$");
    printStack();
    tracing();
}

void Output::tracing() {
    while(!parsingStack.empty()){
        for(int i = 0; i < tokens.size(); i++){
            string top = parsingStack.top();
            if(!isTerminal(tokens[i]) && tokens[i] != "$"){
                error(top, tokens[i],1);
                continue;
            }
            if(isTerminal(top) || top == "$"){
                if(top == tokens[i]){
                    if (top != "$"){
                        cout << "Match " << top << endl;
                        outfile << "Match " << top << endl;
                        parsingStack.pop();
                        printStack();
                        continue;
                    }
                    else{
                        cout << "End of Parsing " << endl;
                        outfile << "End of Parsing " << endl;
                        parsingStack.pop();
                        printStack();
                    }
                }else {
                    if (top == "$"){
                        if(tokens[i] != "$"){
                            error(top, tokens[i],1);
                            i++;
                        }
                        i--;
                    }
                    else{
                        error(top, tokens[i],2);
                        parsingStack.pop();
                        printStack();
                        i--;
                        continue;
                    }
                }
            } else {
                int index = parsingTable[top][tokens[i]];
                if (index == ERROR) {
                    error(top, tokens[i],3);
                    continue;
                }
                else if (index == SYNCH) {
                    parsingStack.pop();
                    printStack();
                    i--;
                    continue;
                }
                else{
                    vector<string> production = productions[top][index];
                    parsingStack.pop();
                    while (!production.empty()){
                        if (production.back() != EPS) {
                            parsingStack.push(production.back());
                        }
                            production.pop_back();
                    }
                    printStack();
                    i--;
                    continue;
                }
            }
        }
    }
}

void Output::printStack() {
    stack<string> temp = parsingStack;
    stack<string> temp2;
    while (!temp.empty()){
        temp2.push(temp.top());
        temp.pop();
    }
    while (!temp2.empty()){
        cout << temp2.top() << " ";
        outfile << temp2.top() << " ";
        temp2.pop();
    }
    cout<<endl;
    outfile<<endl;
}

void Output::error(string top, string token, int errorNum) {
    switch (errorNum) {
        case 1: cout << "ERROR : Discard " << token << endl;
            outfile << "ERROR : Discard " << token << endl;
            break;
        case 2: cout << "ERROR : Missing " << top << endl;
            outfile << "ERROR : Missing " << top << endl;
            break;
        case 3: cout << "ERROR : Illegal " << top << " discard " << token << endl;
            outfile << "ERROR : Illegal " << top << " discard " << token << endl;
            break;
    }
}

bool Output::isTerminal(string symbol) {
    return terminal.find(symbol) != terminal.end();
}

//bool Output::inNonTerminal(string stackTop) {
//    return nonTerminal.find(stackTop) != nonTerminal.end();
//}