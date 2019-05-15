#pragma once

#include "DmsFieldScope.h"

class DmsObject {
public:
    DmsFieldScope field_scope;

    DmsObject();
    DmsObject(DmsFieldScope* enclosing_scope);
    ~DmsObject();

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    std::string serialize() { return field_scope.serialize(); };
    std::string compile() { return field_scope.compile(); };

    bool verify() { return true; };
};
