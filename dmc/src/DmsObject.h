#pragma once

#include "DmsFieldScope.h"
#include "DmsSerializable.h"

class DmsObject: public DmsSerializable{
public:
    DmsFieldScope field_scope;

    DmsObject();
    DmsObject(const DmsObject &/*object*/);
    DmsObject(DmsFieldScope* enclosing_scope);
    virtual ~DmsObject();

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    virtual std::string serialize() { return field_scope.serialize(); };
    std::string compile() { return field_scope.compile(); };

    virtual bool verify() { return true; };
};
