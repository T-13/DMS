#pragma once

#include "DmsFieldScope.h"
#include "DmsSerializable.h"

class DmsObject: public DmsSerializable {
public:
    DmsFieldScope field_scope;

    DmsObject();
    DmsObject(const DmsObject &object);
    DmsObject(DmsFieldScope* enclosing_scope);
    virtual ~DmsObject();

    virtual std::string serialize() { return field_scope.serialize(); };
    virtual bool verify() { return true; };
};
