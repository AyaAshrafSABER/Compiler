//
// Created by Rowan on 20-Apr-19.
//

#include "Output.h"
#include "TestFirstFollow.h"
#include <iostream>
#include <ReadProgram.h>

Output::Output() {
    CFG* cfg = CFG::getInstance();
    // TestFirstFollow* cfg = TestFirstFollow::getInstance();
    this->productions = cfg->getProduction();
    this->terminal = cfg->getTerminal();
    //this->nonTerminal = cfg->getNonTerminal();
    this->startSymbol = cfg->getStartSymbol();
    ParsingTable* table = ParsingTable::getInstance();
    this->parsingTable = table->getParsingTable();
    //ReadProgram *prog = ReadProgram::getInstance("C:\\Users\\Adel\\CLionProjects\\Compiler\\Test\\Program");
    //prog->getInstance("C:\\Users\\Adel\\CLionProjects\\Compiler\\Test\\Program");
    //this->tokens = prog->getTokens();
    //this->tokens = table->getTokens();
    outfile.open("ParserOutput.txt");
    initialization();
    readFile("/home/sohayla/CLionProjects/Compiler/Test/Program");
}

void Output::initialization() {
    parsingStack.push("$");
    parsingStack.push(startSymbol);
    tokens.push_back("$");
    printStack();
    // tracing();
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
                        if (production.back() != EPSILON) {
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

void Output::readFile(string filename) {
    ifstream infile(filename);
    ReadProgram * lexical = new ReadProgram();
    string line;
    vector <string> lineTokens;
    ofstream outfile;
    outfile.open("tokens.txt");
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if(parsingStack.top() == "$") {
                parsingStack.push(startSymbol);
            }
            if (line.length() == 0 || line == " ")
                continue;

            lineTokens = lexical->splitBySpaces(line);
            ReadProgram::state token;
            ReadProgram::state prev_token;

            while (token.vec_ind < lineTokens.size()){
                //get token
                token = lexical->getNextToken(lineTokens, token.vec_ind, token.ch_ind);
                //last pushed in stack
                string top = parsingStack.top();
                //token is not terminal, or dollar sign, error
                if(!isTerminal(token.token) && token.token != "$"){
                    error(top, token.token,1);
                    continue;
                }
                //terminal or dollar
                if(isTerminal(top) || top == "$"){
                    //if equal terminal = token
                    if(top == token.token){
                        //check if done parsing
                        if (top != "$"){
                            cout << "Match " << top << endl;
                            outfile << "Match " << top << endl;
                            parsingStack.pop();
                            printStack();
                            prev_token = token;
                            continue;
                        }//done parsing
                        else{
                            cout << "End of Parsing " << endl;
                            outfile << "End of Parsing " << endl;
                            parsingStack.pop();
                            printStack();
                            break;
                        }
                    }else {
                        if (top == "$"){//check if top is dollar
                            if(token.token != "$"){ // error, discard input
                                error(top, token.token,1);
                                prev_token = token;
                                continue;
                            }
                        }
                        else{ //missing input
                            error(top, token.token,2);
                            parsingStack.pop();
                            printStack();
                            token = prev_token;
                            prev_token = token;
                            continue;
                        }
                    }
                } else { //if top is non-terminal
                    int index = parsingTable[top][token.token];//production
                    if (index == ERROR) { //error
                        error(top, token.token,3);
                        prev_token = token;
                        continue;
                    }
                    else if (index == SYNCH) {//done with non-terminal
                        parsingStack.pop();
                        printStack();
                        token = prev_token;
                        prev_token = token;
                        continue;
                    }
                    else{
                        vector<string> production = productions[top][index];
                        parsingStack.pop();
                        while (!production.empty()){
                            if (production.back() != EPSILON) {
                                parsingStack.push(production.back());
                            }
                            production.pop_back();
                        }
                        printStack();
                        token = prev_token;
                        prev_token = token;
                        continue;
                    }
                }
                outfile << token.token << endl;
            }
            /*for (int i = 0; i < lineTokens.size(); i++) {
                Node *nextState = dfa->getStartState();
                Node *lastAcc = NULL;
                int lastInd = -1;
                int startInd = 0;
                for (int j = 0; j < lineTokens[i].length(); j++) {
                    if(lineTokens[i] == " ") {
                        continue;
                    }
                    //get nextState
                    nextState = getNextState(nextState, lineTokens[i].at(j));
                    //If there exist next state and it's acceptance
                    if (nextState != NULL && nextState->getStatus() != N_ACC){
                        lastAcc = nextState;
                        lastInd = j;
                    }
                    //If no next state or, last token and not accepted yet
                    if ((nextState == NULL)
                        || (j == lineTokens[i].length() - 1 && nextState->getStatus() == N_ACC)) {
                        //push last accepted, start from last index again
                        if (lastInd > -1 && lastAcc != nullptr){
                            tokens.push_back(lastAcc->getStatus());
                            cout<<lastAcc->getStatus()<<endl;
                            lastAcc = NULL;
                            startInd = lastInd;
                            j = lastInd;
                            lastInd = -1;
                        }
                        else {
                            //didn't match anything
                            tokens.push_back("Not Matched");
                            cout<<"Not Matched"<<endl;
                            //ignore and go to next
                            if (startInd != 0) {
                                j = startInd + 1;
                                lastInd = j;
                            }
                        }
                        //continue from next state
                        nextState = dfa->getStartState();
                    }
                    //if last index and it's accepted
                    else if (j == lineTokens[i].length() - 1 && nextState->getStatus() != N_ACC){
                        tokens.push_back(nextState->getStatus());
                        cout<<lastAcc->getStatus()<<endl;
                    }
                }
            }*/
        }
        outfile.close();

    }
    infile.close();
    // writeOutputFile();


}

//bool Output::inNonTerminal(string stackTop) {
//    return nonTerminal.find(stackTop) != nonTerminal.end();
//}