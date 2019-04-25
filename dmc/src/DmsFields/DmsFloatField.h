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

class DmsFloatField: public DmsField {
public:
    DmsFloatField();
    DmsFloatField(const DmsFloatField &field);
    DmsFloatField(std::string name_, float value_, DmsObject *parent_);
    ~DmsFloatField();

    void set_value(float value_);
    float get_value();

    std::string serialize() { return name + " -> " + std::to_string(value) + "\n"; };
    std::string compile() { return ""; };

private:
    int value;
};

