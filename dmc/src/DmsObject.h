#pragma once

#include "DmsFieldScope.h"
#include "DmsSerializable.h"

class DmsObject: public DmsSerializable {
public:
    DmsFieldScope field_scope;
    bool split_serialization = false;

    DmsObject();
    DmsObject(const DmsObject &object);
    DmsObject(DmsFieldScope* enclosing_scope);
    virtual ~DmsObject();

    virtual bool verify();

    virtual void print(std::ostream &os, bool split = false) const;
};
