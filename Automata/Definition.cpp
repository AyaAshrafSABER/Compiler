//
// Created by sohayla on 22/03/19.
//

#include "Definition.h"
Definition::Definition(void* def, bool is_string) {
    definition = def;
    this->is_string = is_string;
}

bool Definition::setDef(void *def) {
    this->definition = def;
}

void* Definition::getDef() {
    return definition;
}
bool Definition::contains(string input) {
    if(is_string){
        //check string
    } else {
        //traverse automata
    }
}
