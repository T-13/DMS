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

class DmsStringField: public DmsField {
public:
    DmsStringField();
    DmsStringField(const DmsStringField &field);
    DmsStringField(std::string name_, std::string value_, DmsObject *parent_);
    ~DmsStringField();

    void set_value(std::string value_);
    std::string get_value();

    std::string serialize() { return name + " -> " + value + "\n"; };
    std::string compile() { return ""; };

private:
    std::string value;
};

