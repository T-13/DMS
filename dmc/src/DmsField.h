#pragma once

#include <string>
#include <vector>

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
class DmsObject;

class DmsField {
public:
    DmsField();
    DmsField(std::string name_, DmsObject *parent_);
    virtual ~DmsField();

    std::string get_name() const;

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    virtual std::string serialize() = 0;
    virtual std::string compile() = 0;

protected:
    DmsObject *parent;
    std::string name;
};

