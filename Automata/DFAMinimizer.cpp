//
// Created by TARGET on 3/23/2019.
//

#include "DFAMinimizer.h"
/* Null, because instance will be initialized on demand. */
DFAMinimizer* DFAMinimizer::instance = 0;
//constructor
DFAMinimizer::DFAMinimizer()
{
    this->dfa = DFA::getInstance();
    this->setFirstPartition(this->Accepted,this->NotAccepted,this->previousPartition);
    this->partitioning(this->dfa, this->previousPartition, this->nextPartition);
}

DFAMinimizer* DFAMinimizer::getInstance()
{
    if (instance == 0)
    {
        instance = new DFAMinimizer();
    }
    return instance;
}


void DFAMinimizer:: setFirstPartition(set<Node*> Acc, set<Node*> Not_Acc, vector<set<Node*>> partitions){ //p0
    vector<pair<Node*, map<Definition*,set<Node*>>>> transitionStateTable = this->dfa->getDFA();
    vector<pair<Node*, map<Definition*,set<Node*>>>>::iterator ptr ;
    for(auto ptr=transitionStateTable.begin(); ptr!=transitionStateTable.end(); ++ptr) {
        Node temp = *ptr->first;
        if (temp.getStatus().compare(N_ACC) == 0) {
            Not_Acc.insert(&temp);
        } else {
            Acc.insert(&temp);
        }
    }
    partitions.push_back(Acc);
    partitions.push_back(Not_Acc);
}
void DFAMinimizer::partitioning(DFA* dfa, vector<set<Node*>>pre, vector<set<Node*>>next ){
    this->nextPartition = this->partitioningHelper(dfa, pre);
    while (!(this->isEqualPartition(pre, next))) {
        pre = next;
        next = partitioningHelper(dfa,pre);
    }
}
vector<set<Node*>> DFAMinimizer::partitioningHelper(DFA* dfa , vector<set<Node*>>pre){
    vector<set<Node*>> next;
    vector<set<Node*>>::iterator ptr ; // loop on every partition in the vector
    for(auto ptr = pre.begin(); ptr != pre.end(); ++ptr) { //loop on each set on the partition
        this->distinguishStates(dfa,pre,next,*ptr);
    }
    return next;

}
void DFAMinimizer::distinguishStates(DFA* dfa,vector<set<Node*>> P,vector<set<Node*>> n ,set<Node*> curr){
    Node* A  = *curr.begin();
    set<Node*>::iterator ptr ; // loop on every state
    set<Node*> set1;
    set<Node*> set2;
    for (auto ptr = curr.begin(); ptr != curr.end(); ++ptr)
    {
        Node* B  = *ptr;
        if (!areEquivalentStates(dfa,P,A,B)) {
            set2.insert(B);
        }else {
            set1.insert(B);
        }
    }
    if (set2.size() == 0) {
        n.push_back(set1);
    }else {
        n.push_back(set1);
        n.push_back(set2);
    }
}


bool DFAMinimizer::areEquivalentStates(DFA* dfa , vector<set<Node*>> P, Node* A, Node *B){
    vector<pair<Node*, map<Definition*,set<Node*>>>> TT = this->dfa->getDFA();
    vector<pair<Node*, map<Definition*,set<Node*>>>>::iterator ptr ;
    map<Definition*,set<Node*>> Amap;
    map<Definition*,set<Node*>> Bmap;
    for(auto ptr = TT.begin(); ptr != TT.end(); ++ptr) {
        if (ptr->first = A) {
            Amap = ptr->second;
        } else if (ptr->first = B) {
            Bmap = ptr->second;
        }
    }
    return  Bmap.size() == Amap.size()
                  && std::equal(Amap.begin(), Amap.end(),Bmap.begin());
}
void DFAMinimizer::printMinimizedDFA(){


}
bool DFAMinimizer::isEqualPartition(vector<set<Node*>> P,vector<set<Node*>> N){

    if (P.size() != N.size()){
        return false;
    }
    return true;
}

std::vector<std::pair<Node*, std::map<Definition*,set<Node*>>>>  DFAMinimizer::getMinimizedDFA(){
    return this->minimizedTransitionStateTable;
}