#pragma once

#include "../DmsObject.h"

class DmsCharacter: public DmsObject {
public:
    DmsCharacter();
    DmsCharacter(const DmsCharacter &character);
    DmsCharacter(DmsFieldScope *enclosing_scope);

    virtual bool verify();
};

