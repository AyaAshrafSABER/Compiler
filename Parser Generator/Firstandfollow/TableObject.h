//
// Created by sohayla on 19/04/19.
//

#ifndef COMPILER_TABLEOBJECT_H
#define COMPILER_TABLEOBJECT_H

#include <string>

using namespace std;

class TableObject {
private:
    int index;
    string value;
public:
    TableObject(int index, string value);
    void setIndex(int index);
    void setValue(string val);
    int getIndex();
    string getValue();
};


#endif //COMPILER_TABLEOBJECT_H
