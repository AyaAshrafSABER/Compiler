//
// Created by sohayla on 22/03/19.
//

#include "Definition.h"
#include "Definitions_Table.h"
#include <stack>
Definition::Definition(Graph* def) {
    definition = def;
}

bool Definition::setDef(Graph *def) {
    this->definition = def;
}

Graph* Definition::getDef() {

    return definition;
}
bool Definition::contains(string input) {
    if(definition->getAllstates().size() == 1){
       string check = definition->getEndState()->getStatus();
       if(check.find("-") != string::npos && check != "\\-") {
           if(check.at(0) == 'a') {
               return islower(input.at(0));
           } else if(check.at(0) == 'A') {
               return isupper(input.at(0));
           } else if(check.at(0) == '0') {
               return isdigit(input.at(0));
           }

       } else if(check== "eps"){//ask about it
            return true;
       } else if(check == input) {
           return true;
       }
        return false;
    } else {
        Node* dest = DFS(this->getDef()->getStartState(), this->getDef()->getAllstates().size(), input);
        if(dest->getStatus() == N_ACC)
            return false;
        return true;
    }
}
Node* Definition::DFS(Node* start, int numberOfStates, string input) {

    bool *visited = new bool[numberOfStates];
    for(int i = 0; i < numberOfStates; i++)
        visited[i] = false;

    stack<Node*> stack;

    visited[start->getId()] = true;
    stack.push(start);

    while(!stack.empty())
    {
        start = stack.top();
        stack.pop();

        vector<Edge*> edges = start->getOutwardEdges();
        for (vector<Edge*>::iterator it = edges.begin() ; it != edges.end(); ++it) {
            if ((*it)->getWeight()->contains(input))
                return (*it)->getDestination();
            if (!visited[(*it)->getDestination()->getId()]) {
                visited[(*it)->getDestination()->getId()] = true;
                stack.push((*it)->getDestination());
            }
        }
    }
}
