//
// Created by sohayla on 20/03/19.
//

#include <algorithm>
#include <iostream>
#include "Construct_Automata.h"
#include "../Automata/Helpers.h"

Construct_Automata::Construct_Automata() {
    def_t = Definitions_Table::getInstance();

}
bool Construct_Automata::constructAutomata(string line) {
    Tokenizing tokeniser;
    vector<string> tokens = tokeniser.getTokens(line, ' ');
    char* type = const_cast<char *>(tokens[1].c_str());
    if (tokens[1] == "=")  {// definition
        string id = tokens[0];
        tokens.erase(tokens.begin());
        tokens.erase(tokens.begin());
        return constructDefinition(id, tokens);
    }
     if(tokens[1] == ":") {
            // part of the automata
         string id = tokens[0];
         tokens.erase(tokens.begin());
         tokens.erase(tokens.begin());
         Graph *sub_g = constructNFASubGraph(tokens);
         testGraph(sub_g);
         nfa_id = sub_g->getEndState()->getId()+1;
         sub_g->getEndState()->setStatus(id);
         sub_Automatas.push_back(sub_g);
            //construct new subgraph
            //add subgraph to map
            //return
     } else {
            //switch check if valid input

            if (tokens[0] == "{") {
                tokens.erase(tokens.begin());
                tokens.erase(tokens.end());
                constructKeyWords(tokens);
                //keywords
                //data types
            } else if (line.at(0) == '[') {
                tokens.erase(tokens.begin());
                tokens.erase(tokens.end());
                constructPunct(tokens);
            } else {
                return false;
            }
     }
     return true;


}
Graph* Construct_Automata::constructNFASubGraph(vector<string> tokens) {
    return recurseBuild(tokens, &nfa_id);
}

Graph* Construct_Automata::recurseBuild(vector<string> tokens, int* i) {
    Helpers* merge = Helpers::getInstance();
    if(tokens.empty())
        return NULL;
    string temp = tokens.front();
    tokens.erase(tokens.begin());
    bool brackets = false;
    Graph* d_g = new Graph();

    if(temp == "(") {
        brackets = true;
        d_g = recurseBrackets(&tokens, i);
    }
    string h = helperValue(&tokens);

    if(!brackets) {
        d_g = createGraph(&tokens, temp, i);
    }

    if(h == "*" || h == "\\+") {
        d_g = merge->mergeGraphs(d_g, NULL, h);
        h = helperValue(&tokens);
    }
    while (h == "." && !tokens.empty()) {
        d_g = getCont(d_g, &tokens, i);
        h = helperValue(&tokens);
    }
    return merge->mergeGraphs(d_g, recurseBuild(tokens, i),h);

}
bool Construct_Automata::constructDefinition(string id, vector<string> definition) {
    Tokenizing tokenizer;
    int node_id = 1;
    Graph* g = recurseBuild(definition, &def_id);
    g->getEndState()->setStatus(id);
    def_id = g->getEndState()->getId()+1;
    testGraph(g);
    def_t->insertInMap(id, new Definition(g));
}

bool Construct_Automata::constructNFA() {
    Graph* nfa = new Graph();
    Definition* eps = def_t->getDefinitions("EPS");

    Node* new_start = new Node(nfa_id);
    for (int i = 0; i <sub_Automatas.size() ; ++i) {
        nfa->mergeGraph(sub_Automatas[i]->getEdges(), sub_Automatas[i]->getAllstates());
        nfa->addEdge(new_start, sub_Automatas[i]->getStartState(), eps);
    }
    NFA* n = NFA::getInstance();
    n->setAutomata(nfa);
    testGraph(n->getAutomata());
    return true;
}

Graph *Construct_Automata::recurseBrackets(vector<string> *pVector, int *pInt) {
    vector<string> p_t;
    string t = "";
    while(t != ")") {
        t = pVector->front();
        pVector->erase(pVector->begin());
        p_t.push_back(t);
    }
    p_t.pop_back();
    Graph* g = recurseBuild(p_t, pInt);
    string st = "(" + g->getEndState()->getStatus() + ")";
    g->getEndState()->setStatus(st);
    return g;
}


string Construct_Automata::helperValue(vector<string> *pVector) {

    Helpers* helper = Helpers::getInstance();
    string h = ".";
    if(!pVector->empty()) {
        if(pVector->front() == "."){
            return h;
        }

        if(pVector->front() != "\\-" && pVector->front() != "\\L") {
            if (helper->isAhelper(pVector->front()) && pVector->front() != "(") {
                h = pVector->front();
                pVector->erase(pVector->begin());
            }
        }
    }

    return h;
}

Graph *Construct_Automata::createGraph(string temp, int *i) {
    Graph* d_g = new Graph();
    Node *n1 = new Node((*i)++);
    Node *n2 = new Node((*i)++);
    n2->setStatus(temp);
    Graph* g = new Graph();
    Node *n3 = new Node((*i)++);
    g->setStart(n3);
    g->setEnd(n3);
    g->getStartState()->setStatus(temp);
    Definition *w = new Definition(g);
    d_g->addEdge(n1, n2, w);
    d_g->setStart(n1);
    d_g->setEnd(n2);
    return d_g;
}

Graph *Construct_Automata::splitToken(string temp, int *i) {
    vector<string> rec;
    for (int j = 0; j < temp.length(); ++j) {
        rec.push_back(string(1, temp.at(j)));
    }
    return recurseBuild(rec, i);
}
Graph* Construct_Automata::createGraphFromExistingDefintition(Definition* def, int* i, string temp) {
        Graph* d_g = new Graph();
        Node *n1 = new Node((*i)++);
        Node *n2 = new Node((*i)++);
        n2->setStatus(temp);
        d_g->addEdge(n1, n2, def);
        d_g->setStart(n1);
        d_g->setEnd(n2);

    return d_g;
}

Graph *Construct_Automata::createGraph(vector<string> *tokens, string temp, int *i) {
    Definition* d = def_t->getDefinitions(temp);
    if (d != NULL) {
        return createGraphFromExistingDefintition(d,i, temp);
    } else if (temp.length() == 1 ||temp.find("-") != string::npos|| temp.at(0) == '\\' ) {
        if(!tokens->empty()) {
            if(tokens->front() == "\\-" && temp.length() ==  1) {
                temp += tokens->front();
                tokens->erase(tokens->begin());
                temp += tokens->front();
                tokens->erase(tokens->begin());
            }
        }
        return createGraph(temp, i);
    } else if (temp.length() > 1) {
        return splitToken(temp, i);
    }
}

void Construct_Automata::testGraph(Graph *g) {
    vector<Node*> states = g->getAllstates();
    vector<Edge*> edges = g->getEdges();
    Node* start = g->getStartState();

    cout << "States : "<<endl;
    for (int i = 0; i < states.size(); ++i) {
        cout<<"States# " <<states[i]->getId() << " status " << states[i]->getStatus() <<endl;
    }
    cout << "start state : " << start->getId() << " status " << start->getStatus() <<endl;

    cout << "Egdes : "<<endl;

    for (int j = 0; j < edges.size(); ++j) {


                cout << "Edge Weight type " << edges[j]->getWeight()->getDef()->getEndState()->getStatus() <<
                     " from" << edges[j]->getSource()->getId() << " to " << edges[j]->getDestination()->getId() << endl;



    }



}

Graph* Construct_Automata::getCont(Graph *d_g, vector<string> *tokens, int *i) {
    Helpers* merge = Helpers::getInstance();
    string temp = tokens->front();
    tokens->erase(tokens->begin());
    bool brackets = false;
    Graph* g = new Graph();
    if(temp == "(") {
        brackets = true;
        g = recurseBrackets(tokens, i);
    }
    string h = helperValue(tokens);

    if(!brackets) {
        g = createGraph(tokens, temp, i);
    }

    if(h == "*" || h == "\\+") {
        g = merge->mergeGraphs(g, NULL, h);
        h = helperValue(tokens);
    } else {
        if(h != ".")
            tokens->insert(tokens->begin(), h);
    }

    return merge->mergeGraphs(d_g, g, ".");

}

void Construct_Automata::constructKeyWords(vector<string> tokens) {
    for (int i = 0; i < tokens.size(); ++i) {
        Helpers* merge = Helpers::getInstance();
        Graph* d_g = splitToken(tokens[i], &nfa_id);
        tokens.erase(tokens.begin());
        sub_Automatas.push_back(d_g);
    }

    return;

}

void Construct_Automata::constructPunct(vector<string> tokens) {
    for (int i = 0; i < tokens.size(); ++i) {
        Helpers* merge = Helpers::getInstance();
        Graph* d_g = createGraph(tokens.front(), &nfa_id);
        tokens.erase(tokens.begin());
        sub_Automatas.push_back(d_g);
    }


    return;
}
