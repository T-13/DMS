#pragma once

#include <string>
#include <vector>

#include "DmsField.h"

/**
 *
 *  DmsField is used to store atributes of DmsObjects
 *  Standardised and objectified field makes compilation/serialization easier
 *
 *  Parent points to the parent object of this field - In case of global variable it is a GlobalVariableHolder
 *  Name is the name of the variable/property
 *  Value is the value of the field
 *
 **/

class DmsIntField: public DmsField {
public:
    DmsIntField();
    DmsIntField(const DmsIntField &field);
    DmsIntField(std::string name_, int value_, DmsObject *parent_);
    ~DmsIntField();

    void set_value(int value_);
    int get_value();

    std::string serialize() { return name + " -> " + std::to_string(value) + "\n"; };
    std::string compile() { return ""; };

private:
    int value;
};

