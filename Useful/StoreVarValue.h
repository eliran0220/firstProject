//
// Created by afik on 12/20/18.
//

#ifndef FIRSTPROJECT_STOREVARVALUE_H
#define FIRSTPROJECT_STOREVARVALUE_H

template <class T>
class StoreVarValue {
    T value;
    bool initialize;
public:
    StoreVarValue() {
        this->initialize = false;
    }

    T getValue() { return this->value;}
    bool checkIfInitialize() { return this->initialize;}
    void setValue(T value) {this->value = value;}
    void setInitialize(bool initialize){this->initialize = initialize;}
};

#endif //FIRSTPROJECT_STOREVARVALUE_H
