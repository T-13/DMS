#pragma once

#include "../DmsObject.h"

class DmsConstants: public DmsObject {
public:
    DmsConstants();
    DmsConstants(DmsFieldScope *enclosing_scope);

    bool verify();
};

