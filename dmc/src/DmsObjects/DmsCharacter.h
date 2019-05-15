#pragma once

#include "../DmsObject.h"

class DmsCharacter: public DmsObject {
public:
    DmsCharacter();
    DmsCharacter(DmsFieldScope *enclosing_scope);

    virtual bool verify();
};

