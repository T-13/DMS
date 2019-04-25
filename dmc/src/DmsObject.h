#pragma once

#include "DmsFieldScope.h"

class DmsObject {
public:
    DmsObject();
    ~DmsObject();

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    std::string serialize() { return field_scope.serialize(); };
    std::string compile() { return field_scope.compile(); };
    DmsFieldScope field_scope;
};

