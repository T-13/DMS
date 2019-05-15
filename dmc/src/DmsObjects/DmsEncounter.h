#pragma once

#include "../DmsObject.h"

class DmsEncounter: public DmsObject {
public:
    DmsEncounter(DmsFieldScope *enclosing_scope);

    bool verify();
};

