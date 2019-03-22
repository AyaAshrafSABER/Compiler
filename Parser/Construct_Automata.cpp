//
// Created by sohayla on 20/03/19.
//

#include <algorithm>
#include "Construct_Automata.h"
#include "../Automata/Helpers.h"

Construct_Automata::Construct_Automata() {

}
bool Construct_Automata::constructAutomata(string line) {
    Tokenizing tokeniser;
    vector<string> tokens = tokeniser.getTokens(line, " ");
    char* type = const_cast<char *>(tokens[1].c_str());
    switch (type[1])  {
        case '=': { // definition
            return constructDefinition(tokens[0], line.substr(2));
        }
        case ':': {
            // part of the automata
            Graph *sub_g = constructGraph(tokens);
            sub_Automatas.push_back(sub_g);
            //construct new subgraph
            //add subgraph to map
            //return

            break;
        }
        default: {
            //switch check if valid input

            if (line.at(0) == '{') {
                //keywords
                //data types
            } else if (line.at(0) == '[') {
                //puncuation


            } else {
                return false;
            }


        }

    }

    return true;


}
Graph* Construct_Automata::constructGraph(vector<string> tokens) {

}

Graph* Construct_Automata::recurseBuild(vector<string> tokens, int i) {
    Helpers* merge;
    if(tokens.empty())
        return NULL;
    string temp = tokens.front();
    tokens.erase(tokens.begin());
    bool brackets = false;

    Graph* d_g = new Graph();
    if(temp == "(") {
        brackets = true;
        vector<string> p_t;
        string t = "";
        while(t != ")") {
            t = tokens.front();
            tokens.erase(tokens.begin());
            p_t.push_back(t);
        }
        p_t.pop_back();
        d_g = recurseBuild(p_t, i);
    }
    string h = "";
    if(!tokens.empty()) {
        if (std::find(helpers.begin(), helpers.end(), tokens.front()) != helpers.end()) {
            h = tokens.front();
            tokens.erase(tokens.begin());
        }
    }
    if(h == "(") {
        h = "";
    }
    if(!brackets) {
        if (definitions.count(temp)) {
            d_g = static_cast<Graph *>(definitions[temp]->getDef());
        } else if (temp.length() == 1 || temp.find("-") != string::npos) {
            Node *n1 = new Node(i++);
            Node *n2 = new Node(i++);
            n2->setStatus(temp);
            Definition *w = new Definition(&temp, true);
            d_g->addEdge(n1, n2, w);
        } else if (!tokens.empty()) {
            if (tokens.front() == "-") {
                string tmp = temp + tokens.front();
                tokens.erase(tokens.begin());
                tmp += tokens.front();
                tokens.erase(tokens.begin());
                d_g = new Graph();
                Node *n1 = new Node(i++);
                Node *n2 = new Node(i++);
                n2->setStatus(tmp);
                Definition *w = new Definition(&tmp, true);
                d_g->addEdge(n1, n2, w);
            } else {
                vector<string> rec;
                for (int j = 0; j < temp.length(); ++j) {
                    rec.push_back(string(1, temp.at(j)));
                }
                d_g = recurseBuild(rec, i);
            }

        } else {
            vector<string> rec;
            for (int j = 0; j < temp.length(); ++j) {
                rec.push_back(string(1, temp.at(j)));
            }
            d_g = recurseBuild(rec, i);
        }
    }
    if(h == "*" || h == "+") {
        merge->mergeGraphs(d_g, NULL, h);
        h = "";
        if(!tokens.empty()) {
            if (std::find(helpers.begin(), helpers.end(), tokens.front()) != helpers.end()) {
                h = tokens.front();
                tokens.erase(tokens.begin());
            }
        }
    }
    return merge->mergeGraphs(d_g, recurseBuild(tokens, i),h);

}
bool Construct_Automata::constructDefinition(string id, string definition) {
    Tokenizing tokenizer;
    int node_id = 1;
    vector<string> tokens = tokenizer.getTokens(definition," ");
    Graph* g = recurseBuild(tokens, node_id);


}

bool Construct_Automata::constructNFA() {}