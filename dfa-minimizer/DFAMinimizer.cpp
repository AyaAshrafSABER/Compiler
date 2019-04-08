//
// Created by AyaOsman on 3/23/2019.
//

#include "DFAMinimizer.h"
/* Null, because instance will be initialized on demand. */

DFAMinimizer* DFAMinimizer::instance;
//constructor
DFAMinimizer::DFAMinimizer()
{
    this->dfa = DFA::getInstance();
    this->setFirstPartition(&this->Accepted,&this->NotAccepted,&this->previousPartition);
    this->partitioning(this->dfa, &this->previousPartition, &this->nextPartition);
    this->buildMinimumeDFA(this->dfa,&this->minimizedTransitionStateTable, &this->previousPartition);
    this->printMinimizedDFA();
}

DFAMinimizer* DFAMinimizer::getInstance()
{
    if (instance == NULL)
    {
        instance = new DFAMinimizer();
    }
    return instance;
}


void DFAMinimizer:: setFirstPartition(set<Node*> *Acc, set<Node*> *Not_Acc, vector<set<Node*>> *partitions){ //p0
    vector<pair<Node*, map<Definition*,Node*>>> transitionStateTable = this->dfa->getDFA();
    vector<pair<Node*, map<Definition*,Node*>>>::iterator ptr ;
    for(auto ptr=transitionStateTable.begin(); ptr!=transitionStateTable.end(); ++ptr) {
        Node* temp = ptr->first;
        set<Node*>ptrNode;
        if (temp->getStatus().compare(N_ACC) == 0) {
           Not_Acc->insert(temp);
        } else {
              Acc->insert(temp);
        }

    }
    cout<<"Accept "<<Acc->size()<<endl;
    cout<<"NotAccept "<<Not_Acc->size()<<endl;
    partitions->push_back(*Acc);
    partitions->push_back(*Not_Acc);
}
void DFAMinimizer::partitioning(DFA* dfa, vector<set<Node*>> *pre, vector<set<Node*>> *next ){

     this->partitioningHelper(dfa, pre,next);
     while (!(this->isEqualPartition(pre, next))) {
        cout<<"size of next partition "<< next->size() <<endl;
        pre->clear();
        vector<set<Node*>>::iterator ptr;
        for(auto ptr = next->begin(); ptr != next->end(); ++ptr) {
             pre->push_back(*ptr);
        }
        partitioningHelper(dfa,pre,next);
    }

}
void DFAMinimizer::partitioningHelper(DFA* dfa , vector<set<Node*>> *pre ,vector<set<Node*>> *next ){
    vector<set<Node*>> temp;
    vector<set<Node*>>::iterator ptr ; // loop on every partition in the vector
    for(auto ptr = pre->begin(); ptr != pre->end(); ++ptr) { //loop on each set on the partition
        this->distinguishStates(dfa,pre,&temp,*ptr);
    }
    next->clear();
    for(auto ptr = temp.begin(); ptr != temp.end(); ++ptr) { //add new sets to next
        next->push_back(*ptr);
    }

}
void DFAMinimizer::distinguishStates(DFA* dfa,vector<set<Node*>>* P,vector<set<Node*>> *n ,set<Node*> curr){
    Node* A  = *curr.begin();
    set<Node*>::iterator ptr ; // loop on every state
    set<Node*> set1;
    set<Node*> set2;
    for (auto ptr = curr.begin(); ptr != curr.end(); ++ptr)
    {
        Node* B  = *ptr;
        if (!areEquivalentStates(dfa,P,A,B)) {
            cout<<" Not Eq "<<endl;
            set2.insert(B);
        }else {
            cout<<" Eq  "<<endl;
            set1.insert(B);
        }
    }
    if (set2.size() == 0) {
        n->push_back(set1);
    }else {
        n->push_back(set1);
        n->push_back(set2);
    }
}


bool DFAMinimizer::areEquivalentStates(DFA* dfa , vector<set<Node*>> *P, Node* A, Node *B){
    cout<<"Node "<<A->getId();
    cout<<" Node "<<B->getId();
    if (A == B) {
        return true;
    }
    if (A->getStatus().compare(B->getStatus()) != 0) {
        return false;
    }
    vector<pair<Node*, map<Definition*,Node*>>> TT = dfa->getDFA();
    vector<pair<Node*, map<Definition*, Node*>>>::iterator ptr ;
    map<Definition*,Node*> a_map;
    map<Definition*,Node*> b_map;
    for(auto ptr = TT.begin(); ptr != TT.end(); ++ptr) {
        if (ptr->first == A) {
            a_map = ptr->second;
        }
         if (ptr->first == B) {
            b_map = ptr->second;
        }
    }
    map<string,Definition*> DT = Definitions_Table::getInstance()->getTable();
    map<string,Definition*> ::iterator ptr2;
    int counter = 0;
    for (auto ptr2 = DT.begin(); ptr2 != DT.end() && counter < DT.size() - 1; ++ptr2) {
        Definition *j = ptr2->second;
        Node* stateA = a_map[j];
        Node*stateB = b_map[j];
        vector<set<Node*>>::iterator s;
        for(auto s = P->begin(); s != P->end(); ++s) {
            set<Node*> temp = *s;
            set<Node*>::iterator it1 = temp.find(stateA);
            set<Node*>::iterator it2 = temp.find(stateB);
            if ((it1 != temp.end() && it2 == temp.end())||(it1 == temp.end() && it2 != temp.end())) {
                return false;
            }
        }
        counter++;
    }
    return  true;
}
void DFAMinimizer::printMinimizedDFA(){
    vector<pair<Node*, map<Definition*, Node*>>>* min = this->getMinimizedDFA();
    cout << "Def  " << " 1   " << "2   " << "..." <<endl;
    for (vector<pair <Node*,  map<Definition*,Node*>>>::iterator it = min->begin() ; it != min->end(); ++it) {
        map<Definition*, Node*> map = (*it).second;
        cout<<(*it).first->getId()<<":";
        for (std::map<Definition*, Node*>::iterator itDef = map.begin(); itDef != map.end(); ++itDef) {
            cout<<" "<<(*itDef).second->getId()<<" ";
        }
        cout<<(*it).first->getStatus()<<endl;
    }


}
bool DFAMinimizer::isEqualPartition(vector<set<Node*>> *P,vector<set<Node*>> *N){

    if (P->size() != N->size()){
        return false;
    }
    return true;
}

std::vector<std::pair<Node*, std::map<Definition*,Node*>>>*  DFAMinimizer::getMinimizedDFA(){
    return &this->minimizedTransitionStateTable;
}
void DFAMinimizer::buildMinimumeDFA(DFA* dfa,vector<pair<Node*, map<Definition*, Node*>>>*ret, vector<set<Node*>> *partition){
    vector<pair<Node*, map<Definition*,Node*>>> transitionStateTable = this->dfa->getDFA();
    vector<pair<Node*, map<Definition*,Node*>>>::iterator ptrTT = transitionStateTable.begin();
    map<set<Node*>, Node*> minDFA;
    vector<set<Node*>>::iterator ptrP ;
    set<Node*>::iterator ptrS;
    Node* s = ptrTT->first;
    int counter = 0;
    for (auto ptrP = partition->begin(); ptrP != partition->end(); ++ptrP) {
        Node *node = new Node(counter);
        set<Node *>::iterator it = ptrP->find(s);
        if (it != ptrP->end()) {
            this->setStartState(node);
            cout<< "Start state "<< this->getStartState()->getId()<<endl;

        }

        auto ptrS = *ptrP->begin();
        node->setStatus(ptrS->getStatus());
        minDFA[*ptrP] = node;
        counter++;
    }
    map<set<Node*>, Node*>::iterator itMap;
    for(auto itMap = minDFA.begin(); itMap != minDFA.end(); ++itMap){
        auto ptrS = *itMap->first.begin(); //node
        map<Definition*, Node*> values;
        for(auto ptrTT = transitionStateTable.begin();ptrTT != transitionStateTable.end();++ptrTT) {
            Node* temp = ptrTT->first;
            if (temp == ptrS) {
                values = ptrTT->second;
                break;
            }
        }
        map<Definition*, Node*>::iterator itDef;
        map<Definition*, Node*> tAfterMin;
        for(auto itDef = values.begin();itDef != values.end();++itDef) {
            for(auto itMap = minDFA.begin(); itMap != minDFA.end(); ++itMap){
                set<Node*>::iterator it1 = itMap->first.find(itDef->second);
                if (it1 != itMap->first.end()){
                    tAfterMin[itDef->first]=itMap->second;
                    break;
                }
            }
        }
        pair<Node*,map<Definition*, Node*>> pair1;
        pair1.first =  itMap->second;
        pair1.second = tAfterMin;
        ret->push_back(pair1);
    }

}

Node *DFAMinimizer::getStartState() const {
    return startState;
}

void DFAMinimizer::setStartState(Node *startState) {
    DFAMinimizer::startState = startState;
}
