//
// Created by sohayla on 20/03/19.
//

#include <algorithm>
#include <iostream>
#include <regex>
#include "Construct_Automata.h"
#include "../Automata/Helpers.h"

Construct_Automata::Construct_Automata() {
    def_t = Definitions_Table::getInstance();

}
bool Construct_Automata::constructAutomata(string line) {
    Tokenizing tokeniser;
    vector<string> tokens = tokeniser.getTokens(line, ' ');
    if(tokens.size() < 1)
        return false;
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
        // testGraph(sub_g);
        nfa_id = sub_g->getEndState()->getId()+1;
        sub_g->getEndState()->setStatus(id);
        sub_g->getEndState()->setPriority(priority++);
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
    Graph* d_g = recurseBuild(tokens, &nfa_id);
    //insertDef(d_g->getEdges());

    return d_g;
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
        d_g = createGraph(&tokens, temp, i,h);
    }

    if(h == "*" || h == "\\+") {
        if(!(temp.length() == 1 ||temp.find("-") != string::npos|| temp.at(0) == '\\' ) && !this->complexDefinitions.count(temp)) {
            h = helperValue(&tokens);
        } else {
            d_g = merge->mergeGraphs(d_g, NULL, h, i);
        }
        h = helperValue(&tokens);
    }
    while (h == "." && !tokens.empty()) {
        d_g = getCont(d_g, &tokens, i);
        //   testGraph(d_g);
        h = helperValue(&tokens);
    }
    return merge->mergeGraphs(d_g, recurseBuild(tokens, i),h, i);

}
bool Construct_Automata::constructDefinition(string id, vector<string> definition) {
    // if(check_complex(definition)) {
    complexDefinitions.insert(pair<string, vector<string>>(id, definition));
    defVisited.insert(pair<string, bool >(id, false));

    //   return false;
    //} else {
    //  string de = mergeString(definition);
    //Node* n = new Node(def_id++);
    //n->setStatus(de);
    //Graph* g = new Graph();
    //g->setStart(n);
    //g->setEnd(n);
    //def_t->insertInMap(id, new Definition(g));
    //testGraph(g);
    //}
    /* Graph* g = recurseBuild(definition, &def_id);
     g->getEndState()->setStatus(id);*/
    return true;
}

bool Construct_Automata::constructNFA() {
    Graph* nfa = new Graph();
    Definition* eps = def_t->getDefinitions(EPS);

    Node* new_start = new Node(nfa_id);
    nfa->setStart(new_start);
    for (int i = 0; i <sub_Automatas.size() ; ++i) {
        // cout<<"Graph #" << i << endl << "-----------------------" << endl;

        testGraph(sub_Automatas[i]);
        nfa->mergeGraph(sub_Automatas[i]->getEdges(), sub_Automatas[i]->getAllstates());
        nfa->addEdge(new_start, sub_Automatas[i]->getStartState(), eps);
    }
    NFA* n = NFA::getInstance();
    n->setAutomata(nfa);
    // testGraph(nfa);
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

        if(pVector->front() != "\\-" && pVector->front() != "\\L" && pVector->front() != "=") {
            if (helper->isAhelper(pVector->front()) && pVector->front() != "(") {
                h = pVector->front();
                pVector->erase(pVector->begin());
            }
        }
    }

    return h;
}

Graph *Construct_Automata::createGraph(string temp, int *i) {

    Definition *w = def_t->getDefinitions(temp);
    if(w == NULL) {
        Graph* g = new Graph();
        Node *n3 = new Node(1);
        g->setStart(n3);
        g->setEnd(n3);
        g->getStartState()->setStatus(temp);
        w = new Definition(g);
        def_t->insertInMap(temp, w);

    }
    Graph* d_g = new Graph();
    Node *n1 = new Node((*i)++);
    Node *n2 = new Node((*i)++);
    n2->setStatus(temp);

    d_g->addEdge(n1, n2, w);
    d_g->setStart(n1);
    d_g->setEnd(n2);

    return d_g;
}

Graph *Construct_Automata::splitToken(string temp, int *i, string h) {
    vector<string> rec;
    for (int j = 0; j < temp.length(); ++j) {
        rec.push_back(string(1, temp.at(j)));
    }
    if(h == "*" || h == "+")
        rec.push_back(h);
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

Graph *Construct_Automata::createGraph(vector<string> *tokens, string temp, int *i,string h) {
    if(complexDefinitions.count(temp)) {
        Graph* g = recurseBuild(complexDefinitions[temp], i);
        g->getEndState()->setStatus(temp);
        //defVisited[temp] = true;
        return g;
    }
    if (temp.length() == 1 ||temp.find("-") != string::npos|| temp.at(0) == '\\' ) {
        if (!tokens->empty() || temp.find("-") != string::npos) {
            vector<string> expanded;
            if ((tokens->front() == "\\-" && temp.length() == 1)) {
                temp += tokens->front();
                tokens->erase(tokens->begin());
                temp += tokens->front();
                tokens->erase(tokens->begin());
            }
        }
    }
    Definition *d;
    if(temp == "\\L") {
        d = def_t->getDefinitions(EPS);
    } else {
        d = def_t->getDefinitions(temp);
    }

    if (d != NULL) {
        return createGraphFromExistingDefintition(d,i, temp);
    } else if (temp.length() == 1 ||temp.find("-") != string::npos|| temp.at(0) == '\\' ) {
        if(!tokens->empty() || temp.find("-") != string::npos) {
            vector<string> expanded;
            if((tokens->front() == "\\-" && temp.length() ==  1 )) {
                temp += tokens->front();
                tokens->erase(tokens->begin());
                temp += tokens->front();
                tokens->erase(tokens->begin());
                return expandedGraph( temp, i);
            } else if( temp.find("-") != string::npos && temp.length() == 4) {
                return expandedGraph(temp, i);
            }
        }
        return createGraph(temp, i);
    } else if (temp.length() > 1) {
        return splitToken(temp, i,h);
    }
}

void Construct_Automata::testGraph(Graph *g) {
    vector<Node*> states = g->getAllstates();
    vector<Edge*> edges = g->getEdges();
    Node* start = g->getStartState();

    cout << "States : "<<endl;
    for (int i = 0; i < states.size(); ++i) {
        cout<<"States# " <<states[i]->getId() << " status " << states[i]->getStatus() <<endl;
        if(states[i]->getStatus() != N_ACC)
            cout << "Accept state : " << states[i]->getId() << " status " << states[i]->getStatus() << " with Priority "<< states[i]->getPriority() <<endl;

    }
    cout << "start state : " << start->getId() << " status " << start->getStatus() <<endl;


    cout << "Egdes : "<<endl;

    for (int j = 0; j < edges.size(); ++j) {


        cout << "Edge Weight type " << edges[j]->getWeight()->getDef()->getEndState()->getStatus() << " from" << edges[j]->getSource()->getId() << " to " << edges[j]->getDestination()->getId() << endl;



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
        g = createGraph(tokens, temp, i, h);
    }

    if(h == "*" || h == "\\+") {
        g = merge->mergeGraphs(g, NULL, h, i);
        h = helperValue(tokens);
    } else {
        if(h != ".")
            tokens->insert(tokens->begin(), h);
    }

    return merge->mergeGraphs(d_g, g, ".", i);

}
/*bool Construct_Automata::check_complex(vector<string> tokens) {
    for (int i = 0; i < tokens.size() ; ++i) {
        if(def_t->getDefinitions(tokens[i]) != NULL)
            return true;
    }
    string de = mergeString(tokens);

    regex e ("[0aA]\\\-[9zZ]");
    if(regex_match(de, e))
        return false;
    if(tokens.size() == 1) {
        if(tokens[0].length() == 1)
            return false;
    }
   // Helpers* h = Helpers::getInstance();
    //vector<string> graphH = h->getGraphHelpers();
    //for (int j = 0; j < graphH.size() ; ++j) {
      //  for (int i = 0; i < tokens.size(); ++i) {
        //    if(tokens[i].find(graphH[j]) != string::npos)
          //      return true;
        //}
    //}
    return true;
}*/


void Construct_Automata::constructKeyWords(vector<string> tokens) {
    while (!tokens.empty()) {
        Helpers* merge = Helpers::getInstance();
        Graph* d_g = splitToken(tokens.front(), &nfa_id, ".");
        d_g->getEndState()->setStatus(tokens.front());
        d_g->getEndState()->setPriority(0);
        tokens.erase(tokens.begin());
        sub_Automatas.push_back(d_g);
        //insertDef(d_g->getEdges());
    }

    return;

}

void Construct_Automata::constructPunct(vector<string> tokens) {
    while (!tokens.empty()) {
        Helpers* merge = Helpers::getInstance();
        Graph* d_g = createGraph(tokens.front(), &nfa_id);
        d_g->getEndState()->setStatus(tokens.front());
        d_g->getEndState()->setPriority(priority);

        tokens.erase(tokens.begin());
        sub_Automatas.push_back(d_g);
        //insertDef(d_g->getEdges());

    }

    priority++;
    return;
}

void Construct_Automata::insertDef(vector<Edge *> edges) {
    for (int i = 0; i < edges.size(); ++i) {
        Definition* d = edges[i]->getWeight();
        if(def_t->getDefinitions(d->getDef()->getEndState()->getStatus()) == NULL) {
            def_t->insertInMap(d->getDef()->getEndState()->getStatus(), d);
        }
    }

}

vector<string> Construct_Automata::expandDef(string def) {
    vector<string> seglist;
    std::stringstream test(def);
    string segment;
    while(std::getline(test, segment, '-'))
    {
        seglist.push_back(segment);
    }

    char start = seglist[0].at(0);
    char end = seglist[1].at(0);
    vector<string> result;
    while (start <= end) {
        result.push_back(string(1,start++));
    }
    return result;
}

Graph *Construct_Automata::expandedGraph(string temp, int *i) {
    vector<string> tokens =  expandDef(temp);
    vector<Graph*> subGraphs;
    Graph* result;
    while (!tokens.empty()) {
        Graph* d_g = createGraph(tokens.front(), i);
        d_g->getEndState()->setStatus(tokens.front());
        tokens.erase(tokens.begin());
        subGraphs.push_back(d_g);
    }
    Node* new_start = new Node((*i)++);
    Node* new_end = new Node((*i)++);
    new_end->setStatus(temp);
    result = new Graph();
    result->setStart(new_start);
    result->setEnd(new_end);
    for (int j = 0; j <subGraphs.size() ; ++j) {
        cout<<"Graph #" << i << endl << "-----------------------" << endl;

        //  testGraph(sub_Automatas[j]);
        result->mergeGraph(subGraphs[j]->getEdges(), subGraphs[j]->getAllstates());
        result->addEdge(new_start, subGraphs[j]->getStartState(), def_t->getDefinitions(EPS));
        subGraphs[j]->getEndState()->setStatus(N_ACC);
        result->addEdge(subGraphs[j]->getEndState(), new_end, def_t->getDefinitions(EPS));
    }
    // testGraph(result);
    return result;
}

/*string Construct_Automata::mergeString(vector<string> tokens) {
    string result = tokens[0];
    for (int i = 1; i < tokens.size(); ++i) {
        result += tokens[i];
    }
    return result;
}*/
