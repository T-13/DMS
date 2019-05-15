#pragma once

#include "../DmsObject.h"

class DmsConstant: public DmsObject {
public:
    DmsConstant();
    DmsConstant(DmsFieldScope *enclosing_scope);

    bool verify();
};

