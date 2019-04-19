//
// Created by sohayla on 19/04/19.
//

#include "TableObject.h"


TableObject::TableObject(int index, string value) {
    this->index = index;
    this->value = value;
}

void TableObject::setIndex(int index) {
    this->index = index;
}

void TableObject::setValue(string val) {
    this->value = val;
}

int TableObject::getIndex() {
    return index;
}

string TableObject::getValue() {
    return value;
}